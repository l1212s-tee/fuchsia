// Copyright 2019 The Fuchsia Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "src/developer/feedback/utils/cobalt.h"

#include <lib/zx/time.h>

#include <limits>
#include <memory>
#include <vector>

#include "src/developer/feedback/testing/gpretty_printers.h"
#include "src/developer/feedback/testing/stubs/stub_cobalt_logger.h"
#include "src/developer/feedback/testing/stubs/stub_cobalt_logger_factory.h"
#include "src/developer/feedback/testing/unit_test_fixture.h"
#include "src/developer/feedback/utils/cobalt_event.h"
#include "src/lib/fxl/logging.h"
#include "src/lib/testing/loop_fixture/test_loop_fixture.h"
#include "third_party/googletest/googlemock/include/gmock/gmock.h"
#include "third_party/googletest/googletest/include/gtest/gtest.h"

namespace feedback {
namespace {

constexpr uint32_t kMaxQueueSize = 500u;
constexpr uint32_t kMetricId = 1u;
constexpr uint32_t kEventCode = std::numeric_limits<uint32_t>::max();
constexpr uint64_t kCount = 2u;
constexpr zx::duration kLoggerBackoffInitialDelay = zx::msec(100);

using fuchsia::cobalt::Status;
using testing::UnorderedElementsAreArray;

class CobaltTest : public UnitTestFixture {
 public:
  void SetUp() override { cobalt_ = std::make_unique<Cobalt>(dispatcher(), services()); }

 protected:
  void SetUpCobaltLoggerFactory(std::unique_ptr<StubCobaltLoggerFactoryBase> logger_factory) {
    logger_factory_ = std::move(logger_factory);
    if (logger_factory_) {
      InjectServiceProvider(logger_factory_.get());
    }
  }

  void LogOccurrence() {
    cobalt_->LogOccurrence(kMetricId, kEventCode);
    events_.emplace_back(kMetricId, kEventCode);
  }

  void LogCount() {
    cobalt_->LogCount(kMetricId, kEventCode, kCount);
    events_.emplace_back(kMetricId, kEventCode, kCount);
  }

  const std::vector<CobaltEvent>& SentEvents() const { return events_; }
  const std::vector<CobaltEvent>& ReceivedEvents() const { return logger_factory_->Events(); }

  bool WasLogEventCalled() { return logger_factory_->WasLogEventCalled(); }
  bool WasLogEventCountCalled() { return logger_factory_->WasLogEventCountCalled(); }

  void CloseAllConnections() {
    logger_factory_->CloseAllConnections();
    RunLoopUntilIdle();
  }

  void CloseFactoryConnection() {
    logger_factory_->CloseFactoryConnection();
    RunLoopUntilIdle();
  }

  void CloseLoggerConnection() {
    logger_factory_->CloseLoggerConnection();
    RunLoopUntilIdle();
  }

  std::unique_ptr<Cobalt> cobalt_;

 private:
  std::vector<CobaltEvent> events_;
  std::unique_ptr<StubCobaltLoggerFactoryBase> logger_factory_;
};

TEST_F(CobaltTest, Check_Log) {
  SetUpCobaltLoggerFactory(std::make_unique<StubCobaltLoggerFactory>());

  for (size_t i = 0; i < 5; ++i) {
    LogCount();
    LogOccurrence();
    RunLoopUntilIdle();
  }

  EXPECT_THAT(ReceivedEvents(), UnorderedElementsAreArray(SentEvents()));
}

TEST_F(CobaltTest, Check_LoggerLosesConnection_BeforeLoggingEvents) {
  SetUpCobaltLoggerFactory(std::make_unique<StubCobaltLoggerFactory>());

  CloseLoggerConnection();

  for (size_t i = 0; i < 5; ++i) {
    LogOccurrence();
    EXPECT_FALSE(WasLogEventCalled());
  }
  RunLoopUntilIdle();

  EXPECT_THAT(ReceivedEvents(), UnorderedElementsAreArray(SentEvents()));
}

TEST_F(CobaltTest, Check_LoggerLosesConnection_WhileLoggingEvents) {
  SetUpCobaltLoggerFactory(std::make_unique<StubCobaltLoggerFactory>());

  for (size_t i = 0; i < 5; ++i) {
    LogOccurrence();
  }
  RunLoopUntilIdle();

  EXPECT_THAT(ReceivedEvents(), UnorderedElementsAreArray(SentEvents()));

  CloseLoggerConnection();

  for (size_t i = 0; i < 5; ++i) {
    LogCount();
  }

  // Run the loop for twice the delay to account for the nondeterminism of
  // backoff::ExponentialBackoff.
  RunLoopFor(kLoggerBackoffInitialDelay * 2);

  EXPECT_THAT(ReceivedEvents(), UnorderedElementsAreArray(SentEvents()));
}

TEST_F(CobaltTest, Check_CallbackExecutes) {
  SetUpCobaltLoggerFactory(
      std::make_unique<StubCobaltLoggerFactory>(std::make_unique<StubCobaltLoggerFailsLogEvent>()));

  Status log_event_status = Status::OK;
  cobalt_->LogOccurrence(kMetricId, kEventCode,
                         [&log_event_status](Status status) { log_event_status = status; });
  RunLoopUntilIdle();
  EXPECT_EQ(log_event_status, Status::INVALID_ARGUMENTS);
}

TEST_F(CobaltTest, Check_LoggerDoesNotRespond_ClosesConnection) {
  auto stub_logger = std::make_unique<StubCobaltLoggerIgnoresFirstEvents>(5u);
  SetUpCobaltLoggerFactory(std::make_unique<StubCobaltLoggerFactory>(std::move(stub_logger)));

  for (size_t i = 0; i < 5; ++i) {
    LogOccurrence();
    RunLoopUntilIdle();
  }

  CloseLoggerConnection();

  LogOccurrence();

  // Run the loop for twice the delay to account for the nondeterminism of
  // backoff::ExponentialBackoff.
  RunLoopFor(kLoggerBackoffInitialDelay * 2);

  EXPECT_THAT(ReceivedEvents(), UnorderedElementsAreArray(SentEvents()));
}

TEST_F(CobaltTest, Check_QueueReachesMaxSize) {
  SetUpCobaltLoggerFactory(std::make_unique<StubCobaltLoggerFactory>());

  CloseLoggerConnection();

  std::vector<CobaltEvent> events;
  for (size_t i = 0; i < kMaxQueueSize; ++i) {
    cobalt_->LogOccurrence(kMetricId, kEventCode);
    events.emplace_back(kMetricId, kEventCode);
  }

  for (size_t i = 0; i < kMaxQueueSize; ++i) {
    cobalt_->LogOccurrence(kMetricId, kEventCode);
  }
  RunLoopUntilIdle();

  EXPECT_THAT(ReceivedEvents(), UnorderedElementsAreArray(events));
}

TEST_F(CobaltTest, Check_ExponentialBackoff) {
  constexpr uint64_t num_attempts = 10u;
  SetUpCobaltLoggerFactory(std::make_unique<StubCobaltLoggerFactoryCreatesOnRetry>(num_attempts));
  CloseLoggerConnection();

  // We need to conservatively approximate the exponential backoff used by |logger_| so we don't
  // unintentionally run the loop for too long.
  zx::duration delay = kLoggerBackoffInitialDelay;
  uint32_t retry_factor = 2u;

  LogOccurrence();
  RunLoopUntilIdle();

  for (size_t i = 0; i < num_attempts - 1; ++i) {
    RunLoopFor(delay);
    EXPECT_FALSE(WasLogEventCalled());
    delay *= retry_factor;
  }
  RunLoopFor(delay);

  EXPECT_THAT(ReceivedEvents(), UnorderedElementsAreArray(SentEvents()));
}

TEST_F(CobaltTest, SmokeTest_NoLoggerFactoryServer) {
  RunLoopUntilIdle();
  for (size_t i = 0; i < 5u; ++i) {
    LogOccurrence();
    RunLoopUntilIdle();
  }
}

}  // namespace
}  // namespace feedback
