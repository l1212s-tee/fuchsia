// Copyright 2019 The Fuchsia Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "src/developer/feedback/feedback_agent/inspect_ptr.h"

#include <fuchsia/mem/cpp/fidl.h>
#include <lib/async/cpp/executor.h>
#include <lib/fit/result.h>
#include <lib/sys/cpp/testing/test_with_environment.h>
#include <lib/zx/time.h>

#include "src/lib/fsl/vmo/strings.h"
#include "src/lib/fxl/test/test_settings.h"
#include "src/lib/syslog/cpp/logger.h"
#include "third_party/googletest/googlemock/include/gmock/gmock.h"
#include "third_party/googletest/googletest/include/gtest/gtest.h"
#include "third_party/rapidjson/include/rapidjson/document.h"
#include "third_party/rapidjson/include/rapidjson/schema.h"

namespace feedback {
namespace {

class CollectInspectDataTest : public sys::testing::TestWithEnvironment {
 public:
  CollectInspectDataTest() : executor_(dispatcher()) {}

  void TearDown() override {
    if (!controller_) {
      return;
    }
    controller_->Kill();
    bool done = false;
    controller_.events().OnTerminated = [&done](int64_t code,
                                                fuchsia::sys::TerminationReason reason) {
      FXL_CHECK(reason == fuchsia::sys::TerminationReason::EXITED);
      done = true;
    };
    RunLoopUntil([&done] { return done; });
  }

 protected:
  // Injects a test app that exposes some Inspect data in the test environment.
  //
  // Useful to guarantee there is a component within the environment that exposes Inspect data as
  // we are excluding system_objects paths from the Inspect discovery and the test component itself
  // only has a system_objects Inspect node.
  void InjectInspectTestApp(const zx::duration timeout = zx::sec(1)) {
    fuchsia::sys::LaunchInfo launch_info;
    launch_info.url = "fuchsia-pkg://fuchsia.com/feedback_agent_tests#meta/inspect_test_app.cmx";
    environment_ = CreateNewEnclosingEnvironment("inspect_test_app_environment", CreateServices());
    environment_->CreateComponent(std::move(launch_info), controller_.NewRequest());
    bool ready = false;
    controller_.events().OnDirectoryReady = [&ready] { ready = true; };
    RunLoopUntil([&ready] { return ready; });
  }

  fit::result<fuchsia::mem::Buffer> CollectInspectData(const zx::duration timeout = zx::sec(1)) {
    fit::result<fuchsia::mem::Buffer> result;
    bool has_result = false;
    executor_.schedule_task(
        feedback::CollectInspectData(dispatcher(), timeout)
            .then([&result, &has_result](fit::result<fuchsia::mem::Buffer>& res) {
              result = std::move(res);
              has_result = true;
            }));
    RunLoopUntil([&has_result] { return has_result; });
    return result;
  }

  async::Executor executor_;

 private:
  std::unique_ptr<sys::testing::EnclosingEnvironment> environment_;
  fuchsia::sys::ComponentControllerPtr controller_;
};

constexpr char kInspectJsonSchema[] = R"({
  "type": "array",
  "items": {
    "type": "object",
    "properties": {
      "path": {
        "type": "string"
      },
      "contents": {
        "type": "object"
      }
    },
    "required": [
      "path",
      "contents"
    ],
    "additionalProperties": false
  },
  "uniqueItems": true
})";

TEST_F(CollectInspectDataTest, Succeed_OneComponentExposesInspectData) {
  InjectInspectTestApp();

  fit::result<fuchsia::mem::Buffer> result = CollectInspectData();

  ASSERT_TRUE(result.is_ok());

  const fuchsia::mem::Buffer& inspect = result.value();

  std::string inspect_json;
  ASSERT_TRUE(fsl::StringFromVmo(inspect, &inspect_json));
  ASSERT_FALSE(inspect_json.empty());

  // JSON verification.
  // We check that the output is a valid JSON and that it matches the schema.
  rapidjson::Document json;
  ASSERT_FALSE(json.Parse(inspect_json.c_str()).HasParseError());
  rapidjson::Document schema_json;
  ASSERT_FALSE(schema_json.Parse(kInspectJsonSchema).HasParseError());
  rapidjson::SchemaDocument schema(schema_json);
  rapidjson::SchemaValidator validator(schema);
  EXPECT_TRUE(json.Accept(validator));

  // We then check that we get the expected Inspect data for the injected test app.
  bool has_entry_for_test_app = false;
  for (const auto& obj : json.GetArray()) {
    const std::string path = obj["path"].GetString();
    if (path.find("inspect_test_app.cmx") != std::string::npos) {
      has_entry_for_test_app = true;
      const auto contents = obj["contents"].GetObject();
      ASSERT_TRUE(contents.HasMember("root"));
      const auto root = contents["root"].GetObject();
      ASSERT_TRUE(root.HasMember("obj1"));
      ASSERT_TRUE(root.HasMember("obj2"));
      const auto obj1 = root["obj1"].GetObject();
      const auto obj2 = root["obj2"].GetObject();
      ASSERT_TRUE(obj1.HasMember("version"));
      ASSERT_TRUE(obj2.HasMember("version"));
      EXPECT_STREQ(obj1["version"].GetString(), "1.0");
      EXPECT_STREQ(obj2["version"].GetString(), "1.0");
      ASSERT_TRUE(obj1.HasMember("value"));
      ASSERT_TRUE(obj2.HasMember("value"));
      EXPECT_EQ(obj1["value"].GetUint(), 100u);
      EXPECT_EQ(obj2["value"].GetUint(), 200u);
    }
  }
  EXPECT_TRUE(has_entry_for_test_app);
}

TEST_F(CollectInspectDataTest, Fail_NoComponentExposesInspectData) {
  fit::result<fuchsia::mem::Buffer> result = CollectInspectData();

  ASSERT_TRUE(result.is_error());
}

TEST_F(CollectInspectDataTest, Fail_CallCollectTwice) {
  const zx::duration unused_timeout = zx::sec(1);
  Inspect inspect(dispatcher());
  executor_.schedule_task(inspect.Collect(unused_timeout));
  ASSERT_DEATH(inspect.Collect(unused_timeout),
               testing::HasSubstr("Collect() is not intended to be called twice"));
}

}  // namespace
}  // namespace feedback

int main(int argc, char** argv) {
  if (!fxl::SetTestSettings(argc, argv)) {
    return EXIT_FAILURE;
  }

  testing::InitGoogleTest(&argc, argv);
  syslog::InitLogger({"feedback", "test"});
  return RUN_ALL_TESTS();
}