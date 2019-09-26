// WARNING: This file is machine generated by fidlgen.

#pragma once

#include <lib/fidl/internal.h>
#include <lib/fidl/llcpp/array.h>
#include <lib/fidl/llcpp/coding.h>
#include <lib/fidl/llcpp/string_view.h>
#include <lib/fidl/llcpp/sync_call.h>
#include <lib/fidl/llcpp/traits.h>
#include <lib/fidl/llcpp/transaction.h>
#include <lib/fidl/llcpp/vector_view.h>
#include <lib/fit/function.h>
#include <lib/zx/channel.h>
#include <lib/zx/event.h>
#include <zircon/fidl.h>

namespace llcpp {

namespace fuchsia {
namespace input {
namespace report {

enum class Unit : uint32_t {
  NONE = 0u,
  OTHER = 1u,
  DISTANCE = 2u,
  WEIGHT = 3u,
  ROTATION = 4u,
  ANGULAR_VELOCITY = 5u,
  LINEAR_VELOCITY = 6u,
  ACCELERATION = 7u,
  MAGNETIC_FLUX = 8u,
  LUMINOUS_FLUX = 9u,
  PRESSURE = 10u,
};


struct Range;
struct Axis;
struct MouseDescriptor;
struct MouseReport;
struct InputReport;
struct DeviceInfo;
struct DeviceDescriptor;
class InputDevice;

extern "C" const fidl_type_t fuchsia_input_report_MouseDescriptorTable;

// |MouseDescriptor| describes the capabilities of a mouse.
struct MouseDescriptor final : private ::fidl::VectorView<fidl_envelope_t> {
  using EnvelopesView = ::fidl::VectorView<fidl_envelope_t>;
 public:
  // Returns whether no field is set.
  bool IsEmpty() const { return EnvelopesView::empty(); }

  // The range of relative X movement.
  const Axis& movement_x() const {
    ZX_ASSERT(has_movement_x());
    return *reinterpret_cast<const Axis*>(EnvelopesView::at(1 - 1).data);
  }
  Axis& movement_x() {
    ZX_ASSERT(has_movement_x());
    return *reinterpret_cast<Axis*>(EnvelopesView::at(1 - 1).data);
  }
  bool has_movement_x() const {
    return EnvelopesView::count() >= 1 && EnvelopesView::at(1 - 1).data != nullptr;
  }

  // The range of relative Y movement.
  const Axis& movement_y() const {
    ZX_ASSERT(has_movement_y());
    return *reinterpret_cast<const Axis*>(EnvelopesView::at(2 - 1).data);
  }
  Axis& movement_y() {
    ZX_ASSERT(has_movement_y());
    return *reinterpret_cast<Axis*>(EnvelopesView::at(2 - 1).data);
  }
  bool has_movement_y() const {
    return EnvelopesView::count() >= 2 && EnvelopesView::at(2 - 1).data != nullptr;
  }

  // The range of relative vertical scroll.
  const Axis& scroll_v() const {
    ZX_ASSERT(has_scroll_v());
    return *reinterpret_cast<const Axis*>(EnvelopesView::at(3 - 1).data);
  }
  Axis& scroll_v() {
    ZX_ASSERT(has_scroll_v());
    return *reinterpret_cast<Axis*>(EnvelopesView::at(3 - 1).data);
  }
  bool has_scroll_v() const {
    return EnvelopesView::count() >= 3 && EnvelopesView::at(3 - 1).data != nullptr;
  }

  // The range of relative horizontal scroll.
  const Axis& scroll_h() const {
    ZX_ASSERT(has_scroll_h());
    return *reinterpret_cast<const Axis*>(EnvelopesView::at(4 - 1).data);
  }
  Axis& scroll_h() {
    ZX_ASSERT(has_scroll_h());
    return *reinterpret_cast<Axis*>(EnvelopesView::at(4 - 1).data);
  }
  bool has_scroll_h() const {
    return EnvelopesView::count() >= 4 && EnvelopesView::at(4 - 1).data != nullptr;
  }

  // This is a vector of id's for the mouse buttons.
  const ::fidl::VectorView<uint8_t>& buttons() const {
    ZX_ASSERT(has_buttons());
    return *reinterpret_cast<const ::fidl::VectorView<uint8_t>*>(EnvelopesView::at(5 - 1).data);
  }
  ::fidl::VectorView<uint8_t>& buttons() {
    ZX_ASSERT(has_buttons());
    return *reinterpret_cast<::fidl::VectorView<uint8_t>*>(EnvelopesView::at(5 - 1).data);
  }
  bool has_buttons() const {
    return EnvelopesView::count() >= 5 && EnvelopesView::at(5 - 1).data != nullptr;
  }

  MouseDescriptor() = default;
  ~MouseDescriptor() = default;
  MouseDescriptor(MouseDescriptor&& other) noexcept = default;
  MouseDescriptor& operator=(MouseDescriptor&& other) noexcept = default;

  class Builder;
  friend class Builder;
  static Builder Build();
  static constexpr const fidl_type_t* Type = &fuchsia_input_report_MouseDescriptorTable;
  static constexpr uint32_t MaxNumHandles = 0;
  static constexpr uint32_t PrimarySize = 16;
  [[maybe_unused]]
  static constexpr uint32_t MaxOutOfLine = 224;

 private:
  MouseDescriptor(uint64_t max_ordinal, fidl_envelope_t* data) : EnvelopesView(data, max_ordinal) {}
};

class MouseDescriptor::Builder {
 public:
  MouseDescriptor view() { return MouseDescriptor(max_ordinal_, envelopes_.data_); }
  ~Builder() = default;
  Builder(Builder&& other) noexcept = default;
  Builder& operator=(Builder&& other) noexcept = default;

  // The range of relative X movement.
  Builder&& set_movement_x(Axis* elem);

  // The range of relative Y movement.
  Builder&& set_movement_y(Axis* elem);

  // The range of relative vertical scroll.
  Builder&& set_scroll_v(Axis* elem);

  // The range of relative horizontal scroll.
  Builder&& set_scroll_h(Axis* elem);

  // This is a vector of id's for the mouse buttons.
  Builder&& set_buttons(::fidl::VectorView<uint8_t>* elem);

 private:
  Builder() = default;
  friend Builder MouseDescriptor::Build();

  uint64_t max_ordinal_ = 0;
  ::fidl::Array<fidl_envelope_t, 5> envelopes_ = {};
};

extern "C" const fidl_type_t fuchsia_input_report_MouseReportTable;

// |MouseReport| gives the relative movement of the mouse and currently
// pressed buttons. Relative means the movement seen between the previous
// report and this report. The client is responsble for tracking this and
// converting it to absolute movement.
struct MouseReport final : private ::fidl::VectorView<fidl_envelope_t> {
  using EnvelopesView = ::fidl::VectorView<fidl_envelope_t>;
 public:
  // Returns whether no field is set.
  bool IsEmpty() const { return EnvelopesView::empty(); }

  // Relative X positional displacement.
  const int64_t& movement_x() const {
    ZX_ASSERT(has_movement_x());
    return *reinterpret_cast<const int64_t*>(EnvelopesView::at(1 - 1).data);
  }
  int64_t& movement_x() {
    ZX_ASSERT(has_movement_x());
    return *reinterpret_cast<int64_t*>(EnvelopesView::at(1 - 1).data);
  }
  bool has_movement_x() const {
    return EnvelopesView::count() >= 1 && EnvelopesView::at(1 - 1).data != nullptr;
  }

  // Relative Y positional displacement.
  const int64_t& movement_y() const {
    ZX_ASSERT(has_movement_y());
    return *reinterpret_cast<const int64_t*>(EnvelopesView::at(2 - 1).data);
  }
  int64_t& movement_y() {
    ZX_ASSERT(has_movement_y());
    return *reinterpret_cast<int64_t*>(EnvelopesView::at(2 - 1).data);
  }
  bool has_movement_y() const {
    return EnvelopesView::count() >= 2 && EnvelopesView::at(2 - 1).data != nullptr;
  }

  // Relative vertical scrolling displacement.
  const int64_t& scroll_v() const {
    ZX_ASSERT(has_scroll_v());
    return *reinterpret_cast<const int64_t*>(EnvelopesView::at(3 - 1).data);
  }
  int64_t& scroll_v() {
    ZX_ASSERT(has_scroll_v());
    return *reinterpret_cast<int64_t*>(EnvelopesView::at(3 - 1).data);
  }
  bool has_scroll_v() const {
    return EnvelopesView::count() >= 3 && EnvelopesView::at(3 - 1).data != nullptr;
  }

  // Relative horizontal scrolling displacement.
  const int64_t& scroll_h() const {
    ZX_ASSERT(has_scroll_h());
    return *reinterpret_cast<const int64_t*>(EnvelopesView::at(4 - 1).data);
  }
  int64_t& scroll_h() {
    ZX_ASSERT(has_scroll_h());
    return *reinterpret_cast<int64_t*>(EnvelopesView::at(4 - 1).data);
  }
  bool has_scroll_h() const {
    return EnvelopesView::count() >= 4 && EnvelopesView::at(4 - 1).data != nullptr;
  }

  // A list of currently pressed buttons.
  const ::fidl::VectorView<uint8_t>& pressed_buttons() const {
    ZX_ASSERT(has_pressed_buttons());
    return *reinterpret_cast<const ::fidl::VectorView<uint8_t>*>(EnvelopesView::at(5 - 1).data);
  }
  ::fidl::VectorView<uint8_t>& pressed_buttons() {
    ZX_ASSERT(has_pressed_buttons());
    return *reinterpret_cast<::fidl::VectorView<uint8_t>*>(EnvelopesView::at(5 - 1).data);
  }
  bool has_pressed_buttons() const {
    return EnvelopesView::count() >= 5 && EnvelopesView::at(5 - 1).data != nullptr;
  }

  MouseReport() = default;
  ~MouseReport() = default;
  MouseReport(MouseReport&& other) noexcept = default;
  MouseReport& operator=(MouseReport&& other) noexcept = default;

  class Builder;
  friend class Builder;
  static Builder Build();
  static constexpr const fidl_type_t* Type = &fuchsia_input_report_MouseReportTable;
  static constexpr uint32_t MaxNumHandles = 0;
  static constexpr uint32_t PrimarySize = 16;
  [[maybe_unused]]
  static constexpr uint32_t MaxOutOfLine = 160;

 private:
  MouseReport(uint64_t max_ordinal, fidl_envelope_t* data) : EnvelopesView(data, max_ordinal) {}
};

class MouseReport::Builder {
 public:
  MouseReport view() { return MouseReport(max_ordinal_, envelopes_.data_); }
  ~Builder() = default;
  Builder(Builder&& other) noexcept = default;
  Builder& operator=(Builder&& other) noexcept = default;

  // Relative X positional displacement.
  Builder&& set_movement_x(int64_t* elem);

  // Relative Y positional displacement.
  Builder&& set_movement_y(int64_t* elem);

  // Relative vertical scrolling displacement.
  Builder&& set_scroll_v(int64_t* elem);

  // Relative horizontal scrolling displacement.
  Builder&& set_scroll_h(int64_t* elem);

  // A list of currently pressed buttons.
  Builder&& set_pressed_buttons(::fidl::VectorView<uint8_t>* elem);

 private:
  Builder() = default;
  friend Builder MouseReport::Build();

  uint64_t max_ordinal_ = 0;
  ::fidl::Array<fidl_envelope_t, 5> envelopes_ = {};
};

extern "C" const fidl_type_t fuchsia_input_report_InputReportTable;

// |InputReport| is a single report that is created by an input device.
struct InputReport final : private ::fidl::VectorView<fidl_envelope_t> {
  using EnvelopesView = ::fidl::VectorView<fidl_envelope_t>;
 public:
  // Returns whether no field is set.
  bool IsEmpty() const { return EnvelopesView::empty(); }

  // |event_time| is in nanoseconds when the event was recorded.
  const int64_t& event_time() const {
    ZX_ASSERT(has_event_time());
    return *reinterpret_cast<const int64_t*>(EnvelopesView::at(1 - 1).data);
  }
  int64_t& event_time() {
    ZX_ASSERT(has_event_time());
    return *reinterpret_cast<int64_t*>(EnvelopesView::at(1 - 1).data);
  }
  bool has_event_time() const {
    return EnvelopesView::count() >= 1 && EnvelopesView::at(1 - 1).data != nullptr;
  }

  const MouseReport& mouse() const {
    ZX_ASSERT(has_mouse());
    return *reinterpret_cast<const MouseReport*>(EnvelopesView::at(2 - 1).data);
  }
  MouseReport& mouse() {
    ZX_ASSERT(has_mouse());
    return *reinterpret_cast<MouseReport*>(EnvelopesView::at(2 - 1).data);
  }
  bool has_mouse() const {
    return EnvelopesView::count() >= 2 && EnvelopesView::at(2 - 1).data != nullptr;
  }

  // Unique ID to connect trace async begin/end events.
  const uint64_t& trace_id() const {
    ZX_ASSERT(has_trace_id());
    return *reinterpret_cast<const uint64_t*>(EnvelopesView::at(3 - 1).data);
  }
  uint64_t& trace_id() {
    ZX_ASSERT(has_trace_id());
    return *reinterpret_cast<uint64_t*>(EnvelopesView::at(3 - 1).data);
  }
  bool has_trace_id() const {
    return EnvelopesView::count() >= 3 && EnvelopesView::at(3 - 1).data != nullptr;
  }

  InputReport() = default;
  ~InputReport() = default;
  InputReport(InputReport&& other) noexcept = default;
  InputReport& operator=(InputReport&& other) noexcept = default;

  class Builder;
  friend class Builder;
  static Builder Build();
  static constexpr const fidl_type_t* Type = &fuchsia_input_report_InputReportTable;
  static constexpr uint32_t MaxNumHandles = 0;
  static constexpr uint32_t PrimarySize = 16;
  [[maybe_unused]]
  static constexpr uint32_t MaxOutOfLine = 240;

 private:
  InputReport(uint64_t max_ordinal, fidl_envelope_t* data) : EnvelopesView(data, max_ordinal) {}
};

class InputReport::Builder {
 public:
  InputReport view() { return InputReport(max_ordinal_, envelopes_.data_); }
  ~Builder() = default;
  Builder(Builder&& other) noexcept = default;
  Builder& operator=(Builder&& other) noexcept = default;

  // |event_time| is in nanoseconds when the event was recorded.
  Builder&& set_event_time(int64_t* elem);

  Builder&& set_mouse(MouseReport* elem);

  // Unique ID to connect trace async begin/end events.
  Builder&& set_trace_id(uint64_t* elem);

 private:
  Builder() = default;
  friend Builder InputReport::Build();

  uint64_t max_ordinal_ = 0;
  ::fidl::Array<fidl_envelope_t, 3> envelopes_ = {};
};

extern "C" const fidl_type_t fuchsia_input_report_DeviceDescriptorTable;

// |DeviceDescriptor| describes a physical input device. Some physical devices may
// send multiple types of reports (E.g: a physical touchscreen can send touch and
// stylus reports, so it will have both a TouchDescriptor and a StylusDescriptor).
struct DeviceDescriptor final : private ::fidl::VectorView<fidl_envelope_t> {
  using EnvelopesView = ::fidl::VectorView<fidl_envelope_t>;
 public:
  // Returns whether no field is set.
  bool IsEmpty() const { return EnvelopesView::empty(); }

  // |device_info| should always be present to help distinguish between physical devices.
  const DeviceInfo& device_info() const {
    ZX_ASSERT(has_device_info());
    return *reinterpret_cast<const DeviceInfo*>(EnvelopesView::at(1 - 1).data);
  }
  DeviceInfo& device_info() {
    ZX_ASSERT(has_device_info());
    return *reinterpret_cast<DeviceInfo*>(EnvelopesView::at(1 - 1).data);
  }
  bool has_device_info() const {
    return EnvelopesView::count() >= 1 && EnvelopesView::at(1 - 1).data != nullptr;
  }

  // When |mouse| is present the device has a mouse.
  const MouseDescriptor& mouse() const {
    ZX_ASSERT(has_mouse());
    return *reinterpret_cast<const MouseDescriptor*>(EnvelopesView::at(2 - 1).data);
  }
  MouseDescriptor& mouse() {
    ZX_ASSERT(has_mouse());
    return *reinterpret_cast<MouseDescriptor*>(EnvelopesView::at(2 - 1).data);
  }
  bool has_mouse() const {
    return EnvelopesView::count() >= 2 && EnvelopesView::at(2 - 1).data != nullptr;
  }

  DeviceDescriptor() = default;
  ~DeviceDescriptor() = default;
  DeviceDescriptor(DeviceDescriptor&& other) noexcept = default;
  DeviceDescriptor& operator=(DeviceDescriptor&& other) noexcept = default;

  class Builder;
  friend class Builder;
  static Builder Build();
  static constexpr const fidl_type_t* Type = &fuchsia_input_report_DeviceDescriptorTable;
  static constexpr uint32_t MaxNumHandles = 0;
  static constexpr uint32_t PrimarySize = 16;
  [[maybe_unused]]
  static constexpr uint32_t MaxOutOfLine = 560;

 private:
  DeviceDescriptor(uint64_t max_ordinal, fidl_envelope_t* data) : EnvelopesView(data, max_ordinal) {}
};

class DeviceDescriptor::Builder {
 public:
  DeviceDescriptor view() { return DeviceDescriptor(max_ordinal_, envelopes_.data_); }
  ~Builder() = default;
  Builder(Builder&& other) noexcept = default;
  Builder& operator=(Builder&& other) noexcept = default;

  // |device_info| should always be present to help distinguish between physical devices.
  Builder&& set_device_info(DeviceInfo* elem);

  // When |mouse| is present the device has a mouse.
  Builder&& set_mouse(MouseDescriptor* elem);

 private:
  Builder() = default;
  friend Builder DeviceDescriptor::Build();

  uint64_t max_ordinal_ = 0;
  ::fidl::Array<fidl_envelope_t, 2> envelopes_ = {};
};



// Describe a |Range| of values.
struct Range {
  static constexpr const fidl_type_t* Type = nullptr;
  static constexpr uint32_t MaxNumHandles = 0;
  static constexpr uint32_t PrimarySize = 16;
  [[maybe_unused]]
  static constexpr uint32_t MaxOutOfLine = 0;

  int64_t min = {};

  int64_t max = {};
};

extern "C" const fidl_type_t fuchsia_input_report_AxisTable;

// An |Axis| is defined as a |range| and a |unit|.
struct Axis {
  static constexpr const fidl_type_t* Type = &fuchsia_input_report_AxisTable;
  static constexpr uint32_t MaxNumHandles = 0;
  static constexpr uint32_t PrimarySize = 24;
  [[maybe_unused]]
  static constexpr uint32_t MaxOutOfLine = 0;

  Range range = {};

  Unit unit = {};
};

// A hardcoded number of max mouse buttons. This should be increased in the future
// if we ever see mice with more buttons.
constexpr uint32_t MOUSE_MAX_NUM_BUTTONS = 32u;

constexpr uint32_t MAX_DEVICE_REPORT_COUNT = 128u;

constexpr uint32_t MAX_DEVICE_NAME_LENGTH = 256u;

extern "C" const fidl_type_t fuchsia_input_report_DeviceInfoTable;

// DeviceInfo provides more information about the device and lets a client
// distinguish between devices (e.g between two touchscreens that come from
// different vendors). If the device is a HID device, then the id information
// will come from the device itself. Other, non-HID devices may assign the
// ids in the driver, so it will be the driver author's responsibility to
// assign sensible ids.
struct DeviceInfo {
  static constexpr const fidl_type_t* Type = &fuchsia_input_report_DeviceInfoTable;
  static constexpr uint32_t MaxNumHandles = 0;
  static constexpr uint32_t PrimarySize = 32;
  [[maybe_unused]]
  static constexpr uint32_t MaxOutOfLine = 256;

  uint32_t vendor_id = {};

  uint32_t product_id = {};

  uint32_t version = {};

  ::fidl::StringView name = {};
};

extern "C" const fidl_type_t fuchsia_input_report_InputDeviceGetReportsEventResponseTable;
extern "C" const fidl_type_t fuchsia_input_report_InputDeviceGetReportsResponseTable;
extern "C" const fidl_type_t fuchsia_input_report_InputDeviceGetDescriptorResponseTable;

// An |InputDevice| driver represents a single physical input device.
// The InputDevice maintains an internal FIFO of |MAX_DEVICE_REPORT_COUNT|
// reports for each client that connects. Reports are removed from the FIFO
// once they are read by the client. If the FIFO is full, it will drop the
// oldest report to make room for an incoming report.
class InputDevice final {
  InputDevice() = delete;
 public:

  struct GetReportsEventResponse final {
    FIDL_ALIGNDECL
    fidl_message_header_t _hdr;
    int32_t status;
    ::zx::event event;

    static constexpr const fidl_type_t* Type = &fuchsia_input_report_InputDeviceGetReportsEventResponseTable;
    static constexpr uint32_t MaxNumHandles = 1;
    static constexpr uint32_t PrimarySize = 24;
    static constexpr uint32_t MaxOutOfLine = 0;
    static constexpr bool HasFlexibleEnvelope = false;
    static constexpr ::fidl::internal::TransactionalMessageKind MessageKind =
        ::fidl::internal::TransactionalMessageKind::kResponse;
  };
  using GetReportsEventRequest = ::fidl::AnyZeroArgMessage;

  struct GetReportsResponse final {
    FIDL_ALIGNDECL
    fidl_message_header_t _hdr;
    ::fidl::VectorView<InputReport> reports;

    static constexpr const fidl_type_t* Type = &fuchsia_input_report_InputDeviceGetReportsResponseTable;
    static constexpr uint32_t MaxNumHandles = 0;
    static constexpr uint32_t PrimarySize = 32;
    static constexpr uint32_t MaxOutOfLine = 32768;
    static constexpr bool HasFlexibleEnvelope = true;
    static constexpr ::fidl::internal::TransactionalMessageKind MessageKind =
        ::fidl::internal::TransactionalMessageKind::kResponse;
  };
  using GetReportsRequest = ::fidl::AnyZeroArgMessage;

  struct GetDescriptorResponse final {
    FIDL_ALIGNDECL
    fidl_message_header_t _hdr;
    DeviceDescriptor descriptor;

    static constexpr const fidl_type_t* Type = &fuchsia_input_report_InputDeviceGetDescriptorResponseTable;
    static constexpr uint32_t MaxNumHandles = 0;
    static constexpr uint32_t PrimarySize = 32;
    static constexpr uint32_t MaxOutOfLine = 560;
    static constexpr bool HasFlexibleEnvelope = true;
    static constexpr ::fidl::internal::TransactionalMessageKind MessageKind =
        ::fidl::internal::TransactionalMessageKind::kResponse;
  };
  using GetDescriptorRequest = ::fidl::AnyZeroArgMessage;


  // Collection of return types of FIDL calls in this interface.
  class ResultOf final {
    ResultOf() = delete;
   private:
    template <typename ResponseType>
    class GetReportsEvent_Impl final : private ::fidl::internal::OwnedSyncCallBase<ResponseType> {
      using Super = ::fidl::internal::OwnedSyncCallBase<ResponseType>;
     public:
      GetReportsEvent_Impl(zx::unowned_channel _client_end);
      ~GetReportsEvent_Impl() = default;
      GetReportsEvent_Impl(GetReportsEvent_Impl&& other) = default;
      GetReportsEvent_Impl& operator=(GetReportsEvent_Impl&& other) = default;
      using Super::status;
      using Super::error;
      using Super::ok;
      using Super::Unwrap;
      using Super::value;
      using Super::operator->;
      using Super::operator*;
    };
    template <typename ResponseType>
    class GetReports_Impl final : private ::fidl::internal::OwnedSyncCallBase<ResponseType> {
      using Super = ::fidl::internal::OwnedSyncCallBase<ResponseType>;
     public:
      GetReports_Impl(zx::unowned_channel _client_end);
      ~GetReports_Impl() = default;
      GetReports_Impl(GetReports_Impl&& other) = default;
      GetReports_Impl& operator=(GetReports_Impl&& other) = default;
      using Super::status;
      using Super::error;
      using Super::ok;
      using Super::Unwrap;
      using Super::value;
      using Super::operator->;
      using Super::operator*;
    };
    template <typename ResponseType>
    class GetDescriptor_Impl final : private ::fidl::internal::OwnedSyncCallBase<ResponseType> {
      using Super = ::fidl::internal::OwnedSyncCallBase<ResponseType>;
     public:
      GetDescriptor_Impl(zx::unowned_channel _client_end);
      ~GetDescriptor_Impl() = default;
      GetDescriptor_Impl(GetDescriptor_Impl&& other) = default;
      GetDescriptor_Impl& operator=(GetDescriptor_Impl&& other) = default;
      using Super::status;
      using Super::error;
      using Super::ok;
      using Super::Unwrap;
      using Super::value;
      using Super::operator->;
      using Super::operator*;
    };

   public:
    using GetReportsEvent = GetReportsEvent_Impl<GetReportsEventResponse>;
    using GetReports = GetReports_Impl<GetReportsResponse>;
    using GetDescriptor = GetDescriptor_Impl<GetDescriptorResponse>;
  };

  // Collection of return types of FIDL calls in this interface,
  // when the caller-allocate flavor or in-place call is used.
  class UnownedResultOf final {
    UnownedResultOf() = delete;
   private:
    template <typename ResponseType>
    class GetReportsEvent_Impl final : private ::fidl::internal::UnownedSyncCallBase<ResponseType> {
      using Super = ::fidl::internal::UnownedSyncCallBase<ResponseType>;
     public:
      GetReportsEvent_Impl(zx::unowned_channel _client_end, ::fidl::BytePart _response_buffer);
      ~GetReportsEvent_Impl() = default;
      GetReportsEvent_Impl(GetReportsEvent_Impl&& other) = default;
      GetReportsEvent_Impl& operator=(GetReportsEvent_Impl&& other) = default;
      using Super::status;
      using Super::error;
      using Super::ok;
      using Super::Unwrap;
      using Super::value;
      using Super::operator->;
      using Super::operator*;
    };
    template <typename ResponseType>
    class GetReports_Impl final : private ::fidl::internal::UnownedSyncCallBase<ResponseType> {
      using Super = ::fidl::internal::UnownedSyncCallBase<ResponseType>;
     public:
      GetReports_Impl(zx::unowned_channel _client_end, ::fidl::BytePart _response_buffer);
      ~GetReports_Impl() = default;
      GetReports_Impl(GetReports_Impl&& other) = default;
      GetReports_Impl& operator=(GetReports_Impl&& other) = default;
      using Super::status;
      using Super::error;
      using Super::ok;
      using Super::Unwrap;
      using Super::value;
      using Super::operator->;
      using Super::operator*;
    };
    template <typename ResponseType>
    class GetDescriptor_Impl final : private ::fidl::internal::UnownedSyncCallBase<ResponseType> {
      using Super = ::fidl::internal::UnownedSyncCallBase<ResponseType>;
     public:
      GetDescriptor_Impl(zx::unowned_channel _client_end, ::fidl::BytePart _response_buffer);
      ~GetDescriptor_Impl() = default;
      GetDescriptor_Impl(GetDescriptor_Impl&& other) = default;
      GetDescriptor_Impl& operator=(GetDescriptor_Impl&& other) = default;
      using Super::status;
      using Super::error;
      using Super::ok;
      using Super::Unwrap;
      using Super::value;
      using Super::operator->;
      using Super::operator*;
    };

   public:
    using GetReportsEvent = GetReportsEvent_Impl<GetReportsEventResponse>;
    using GetReports = GetReports_Impl<GetReportsResponse>;
    using GetDescriptor = GetDescriptor_Impl<GetDescriptorResponse>;
  };

  class SyncClient final {
   public:
    explicit SyncClient(::zx::channel channel) : channel_(std::move(channel)) {}
    ~SyncClient() = default;
    SyncClient(SyncClient&&) = default;
    SyncClient& operator=(SyncClient&&) = default;

    const ::zx::channel& channel() const { return channel_; }

    ::zx::channel* mutable_channel() { return &channel_; }

    // Receive an event that will be signalled when there are reports in the
    // Device's report FIFO. When there are events in the FIFO, |event| will have
    // |DEV_STATE_READABLE| triggered. When the client has read all of the events,
    // |DEV_STATE_READABLE| will be  cleared.
    // Allocates 40 bytes of message buffer on the stack. No heap allocation necessary.
    ResultOf::GetReportsEvent GetReportsEvent();

    // Receive an event that will be signalled when there are reports in the
    // Device's report FIFO. When there are events in the FIFO, |event| will have
    // |DEV_STATE_READABLE| triggered. When the client has read all of the events,
    // |DEV_STATE_READABLE| will be  cleared.
    // Caller provides the backing storage for FIDL message via request and response buffers.
    UnownedResultOf::GetReportsEvent GetReportsEvent(::fidl::BytePart _response_buffer);

    // Get all of the reports that have been seen since the last time this method was called.
    // If this returns 0 reports, please wait on the report event.
    // Allocates 16 bytes of request buffer on the stack. Response is heap-allocated.
    ResultOf::GetReports GetReports();

    // Get all of the reports that have been seen since the last time this method was called.
    // If this returns 0 reports, please wait on the report event.
    // Caller provides the backing storage for FIDL message via request and response buffers.
    UnownedResultOf::GetReports GetReports(::fidl::BytePart _response_buffer);

    // Gets the device descriptor for this device.
    // Allocates 16 bytes of request buffer on the stack. Response is heap-allocated.
    ResultOf::GetDescriptor GetDescriptor();

    // Gets the device descriptor for this device.
    // Caller provides the backing storage for FIDL message via request and response buffers.
    UnownedResultOf::GetDescriptor GetDescriptor(::fidl::BytePart _response_buffer);

   private:
    ::zx::channel channel_;
  };

  // Methods to make a sync FIDL call directly on an unowned channel, avoiding setting up a client.
  class Call final {
    Call() = delete;
   public:

    // Receive an event that will be signalled when there are reports in the
    // Device's report FIFO. When there are events in the FIFO, |event| will have
    // |DEV_STATE_READABLE| triggered. When the client has read all of the events,
    // |DEV_STATE_READABLE| will be  cleared.
    // Allocates 40 bytes of message buffer on the stack. No heap allocation necessary.
    static ResultOf::GetReportsEvent GetReportsEvent(zx::unowned_channel _client_end);

    // Receive an event that will be signalled when there are reports in the
    // Device's report FIFO. When there are events in the FIFO, |event| will have
    // |DEV_STATE_READABLE| triggered. When the client has read all of the events,
    // |DEV_STATE_READABLE| will be  cleared.
    // Caller provides the backing storage for FIDL message via request and response buffers.
    static UnownedResultOf::GetReportsEvent GetReportsEvent(zx::unowned_channel _client_end, ::fidl::BytePart _response_buffer);

    // Get all of the reports that have been seen since the last time this method was called.
    // If this returns 0 reports, please wait on the report event.
    // Allocates 16 bytes of request buffer on the stack. Response is heap-allocated.
    static ResultOf::GetReports GetReports(zx::unowned_channel _client_end);

    // Get all of the reports that have been seen since the last time this method was called.
    // If this returns 0 reports, please wait on the report event.
    // Caller provides the backing storage for FIDL message via request and response buffers.
    static UnownedResultOf::GetReports GetReports(zx::unowned_channel _client_end, ::fidl::BytePart _response_buffer);

    // Gets the device descriptor for this device.
    // Allocates 16 bytes of request buffer on the stack. Response is heap-allocated.
    static ResultOf::GetDescriptor GetDescriptor(zx::unowned_channel _client_end);

    // Gets the device descriptor for this device.
    // Caller provides the backing storage for FIDL message via request and response buffers.
    static UnownedResultOf::GetDescriptor GetDescriptor(zx::unowned_channel _client_end, ::fidl::BytePart _response_buffer);

  };

  // Messages are encoded and decoded in-place when these methods are used.
  // Additionally, requests must be already laid-out according to the FIDL wire-format.
  class InPlace final {
    InPlace() = delete;
   public:

    // Receive an event that will be signalled when there are reports in the
    // Device's report FIFO. When there are events in the FIFO, |event| will have
    // |DEV_STATE_READABLE| triggered. When the client has read all of the events,
    // |DEV_STATE_READABLE| will be  cleared.
    static ::fidl::DecodeResult<GetReportsEventResponse> GetReportsEvent(zx::unowned_channel _client_end, ::fidl::BytePart response_buffer);

    // Get all of the reports that have been seen since the last time this method was called.
    // If this returns 0 reports, please wait on the report event.
    static ::fidl::DecodeResult<GetReportsResponse> GetReports(zx::unowned_channel _client_end, ::fidl::BytePart response_buffer);

    // Gets the device descriptor for this device.
    static ::fidl::DecodeResult<GetDescriptorResponse> GetDescriptor(zx::unowned_channel _client_end, ::fidl::BytePart response_buffer);

  };

  // Pure-virtual interface to be implemented by a server.
  class Interface {
   public:
    Interface() = default;
    virtual ~Interface() = default;
    using _Outer = InputDevice;
    using _Base = ::fidl::CompleterBase;

    class GetReportsEventCompleterBase : public _Base {
     public:
      void Reply(int32_t status, ::zx::event event);
      void Reply(::fidl::BytePart _buffer, int32_t status, ::zx::event event);
      void Reply(::fidl::DecodedMessage<GetReportsEventResponse> params);

     protected:
      using ::fidl::CompleterBase::CompleterBase;
    };

    using GetReportsEventCompleter = ::fidl::Completer<GetReportsEventCompleterBase>;

    virtual void GetReportsEvent(GetReportsEventCompleter::Sync _completer) = 0;

    class GetReportsCompleterBase : public _Base {
     public:
      void Reply(::fidl::VectorView<InputReport> reports);
      void Reply(::fidl::BytePart _buffer, ::fidl::VectorView<InputReport> reports);
      void Reply(::fidl::DecodedMessage<GetReportsResponse> params);

     protected:
      using ::fidl::CompleterBase::CompleterBase;
    };

    using GetReportsCompleter = ::fidl::Completer<GetReportsCompleterBase>;

    virtual void GetReports(GetReportsCompleter::Sync _completer) = 0;

    class GetDescriptorCompleterBase : public _Base {
     public:
      void Reply(DeviceDescriptor descriptor);
      void Reply(::fidl::BytePart _buffer, DeviceDescriptor descriptor);
      void Reply(::fidl::DecodedMessage<GetDescriptorResponse> params);

     protected:
      using ::fidl::CompleterBase::CompleterBase;
    };

    using GetDescriptorCompleter = ::fidl::Completer<GetDescriptorCompleterBase>;

    virtual void GetDescriptor(GetDescriptorCompleter::Sync _completer) = 0;

  };

  // Attempts to dispatch the incoming message to a handler function in the server implementation.
  // If there is no matching handler, it returns false, leaving the message and transaction intact.
  // In all other cases, it consumes the message and returns true.
  // It is possible to chain multiple TryDispatch functions in this manner.
  static bool TryDispatch(Interface* impl, fidl_msg_t* msg, ::fidl::Transaction* txn);

  // Dispatches the incoming message to one of the handlers functions in the interface.
  // If there is no matching handler, it closes all the handles in |msg| and closes the channel with
  // a |ZX_ERR_NOT_SUPPORTED| epitaph, before returning false. The message should then be discarded.
  static bool Dispatch(Interface* impl, fidl_msg_t* msg, ::fidl::Transaction* txn);

  // Same as |Dispatch|, but takes a |void*| instead of |Interface*|. Only used with |fidl::Bind|
  // to reduce template expansion.
  // Do not call this method manually. Use |Dispatch| instead.
  static bool TypeErasedDispatch(void* impl, fidl_msg_t* msg, ::fidl::Transaction* txn) {
    return Dispatch(static_cast<Interface*>(impl), msg, txn);
  }

};

}  // namespace report
}  // namespace input
}  // namespace fuchsia
}  // namespace llcpp

namespace fidl {

template <>
struct IsFidlType<::llcpp::fuchsia::input::report::Range> : public std::true_type {};
static_assert(std::is_standard_layout_v<::llcpp::fuchsia::input::report::Range>);
static_assert(offsetof(::llcpp::fuchsia::input::report::Range, min) == 0);
static_assert(offsetof(::llcpp::fuchsia::input::report::Range, max) == 8);
static_assert(sizeof(::llcpp::fuchsia::input::report::Range) == ::llcpp::fuchsia::input::report::Range::PrimarySize);

template <>
struct IsFidlType<::llcpp::fuchsia::input::report::Axis> : public std::true_type {};
static_assert(std::is_standard_layout_v<::llcpp::fuchsia::input::report::Axis>);
static_assert(offsetof(::llcpp::fuchsia::input::report::Axis, range) == 0);
static_assert(offsetof(::llcpp::fuchsia::input::report::Axis, unit) == 16);
static_assert(sizeof(::llcpp::fuchsia::input::report::Axis) == ::llcpp::fuchsia::input::report::Axis::PrimarySize);

template <>
struct IsFidlType<::llcpp::fuchsia::input::report::MouseDescriptor> : public std::true_type {};
static_assert(std::is_standard_layout_v<::llcpp::fuchsia::input::report::MouseDescriptor>);

template <>
struct IsFidlType<::llcpp::fuchsia::input::report::MouseReport> : public std::true_type {};
static_assert(std::is_standard_layout_v<::llcpp::fuchsia::input::report::MouseReport>);

template <>
struct IsFidlType<::llcpp::fuchsia::input::report::InputReport> : public std::true_type {};
static_assert(std::is_standard_layout_v<::llcpp::fuchsia::input::report::InputReport>);

template <>
struct IsFidlType<::llcpp::fuchsia::input::report::DeviceInfo> : public std::true_type {};
static_assert(std::is_standard_layout_v<::llcpp::fuchsia::input::report::DeviceInfo>);
static_assert(offsetof(::llcpp::fuchsia::input::report::DeviceInfo, vendor_id) == 0);
static_assert(offsetof(::llcpp::fuchsia::input::report::DeviceInfo, product_id) == 4);
static_assert(offsetof(::llcpp::fuchsia::input::report::DeviceInfo, version) == 8);
static_assert(offsetof(::llcpp::fuchsia::input::report::DeviceInfo, name) == 16);
static_assert(sizeof(::llcpp::fuchsia::input::report::DeviceInfo) == ::llcpp::fuchsia::input::report::DeviceInfo::PrimarySize);

template <>
struct IsFidlType<::llcpp::fuchsia::input::report::DeviceDescriptor> : public std::true_type {};
static_assert(std::is_standard_layout_v<::llcpp::fuchsia::input::report::DeviceDescriptor>);

template <>
struct IsFidlType<::llcpp::fuchsia::input::report::InputDevice::GetReportsEventResponse> : public std::true_type {};
template <>
struct IsFidlMessage<::llcpp::fuchsia::input::report::InputDevice::GetReportsEventResponse> : public std::true_type {};
static_assert(sizeof(::llcpp::fuchsia::input::report::InputDevice::GetReportsEventResponse)
    == ::llcpp::fuchsia::input::report::InputDevice::GetReportsEventResponse::PrimarySize);
static_assert(offsetof(::llcpp::fuchsia::input::report::InputDevice::GetReportsEventResponse, status) == 16);
static_assert(offsetof(::llcpp::fuchsia::input::report::InputDevice::GetReportsEventResponse, event) == 20);

template <>
struct IsFidlType<::llcpp::fuchsia::input::report::InputDevice::GetReportsResponse> : public std::true_type {};
template <>
struct IsFidlMessage<::llcpp::fuchsia::input::report::InputDevice::GetReportsResponse> : public std::true_type {};
static_assert(sizeof(::llcpp::fuchsia::input::report::InputDevice::GetReportsResponse)
    == ::llcpp::fuchsia::input::report::InputDevice::GetReportsResponse::PrimarySize);
static_assert(offsetof(::llcpp::fuchsia::input::report::InputDevice::GetReportsResponse, reports) == 16);

template <>
struct IsFidlType<::llcpp::fuchsia::input::report::InputDevice::GetDescriptorResponse> : public std::true_type {};
template <>
struct IsFidlMessage<::llcpp::fuchsia::input::report::InputDevice::GetDescriptorResponse> : public std::true_type {};
static_assert(sizeof(::llcpp::fuchsia::input::report::InputDevice::GetDescriptorResponse)
    == ::llcpp::fuchsia::input::report::InputDevice::GetDescriptorResponse::PrimarySize);
static_assert(offsetof(::llcpp::fuchsia::input::report::InputDevice::GetDescriptorResponse, descriptor) == 16);

}  // namespace fidl