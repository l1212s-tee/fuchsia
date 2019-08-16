// WARNING: This file is machine generated by fidlgen.

#include <fuchsia/process/llcpp/fidl.h>
#include <memory>

namespace llcpp {

namespace fuchsia {
namespace process {

namespace {

[[maybe_unused]]
constexpr uint64_t kResolver_Resolve_GenOrdinal = 0x20980a8100000000lu;
extern "C" const fidl_type_t fuchsia_process_ResolverResolveRequestTable;
extern "C" const fidl_type_t fuchsia_process_ResolverResolveResponseTable;

}  // namespace
template <>
Resolver::ResultOf::Resolve_Impl<Resolver::ResolveResponse>::Resolve_Impl(zx::unowned_channel _client_end, ::fidl::StringView name) {
  constexpr uint32_t _kWriteAllocSize = ::fidl::internal::ClampedMessageSize<ResolveRequest, ::fidl::MessageDirection::kSending>();
  std::unique_ptr _write_bytes_boxed = std::make_unique<::fidl::internal::AlignedBuffer<_kWriteAllocSize>>();
  auto& _write_bytes_array = *_write_bytes_boxed;
  ResolveRequest _request = {};
  _request.name = std::move(name);
  auto _linearize_result = ::fidl::Linearize(&_request, _write_bytes_array.view());
  if (_linearize_result.status != ZX_OK) {
    Super::SetFailure(std::move(_linearize_result));
    return;
  }
  ::fidl::DecodedMessage<ResolveRequest> _decoded_request = std::move(_linearize_result.message);
  Super::SetResult(
      Resolver::InPlace::Resolve(std::move(_client_end), std::move(_decoded_request), Super::response_buffer()));
}

Resolver::ResultOf::Resolve Resolver::SyncClient::Resolve(::fidl::StringView name) {
  return ResultOf::Resolve(zx::unowned_channel(this->channel_), std::move(name));
}

Resolver::ResultOf::Resolve Resolver::Call::Resolve(zx::unowned_channel _client_end, ::fidl::StringView name) {
  return ResultOf::Resolve(std::move(_client_end), std::move(name));
}

template <>
Resolver::UnownedResultOf::Resolve_Impl<Resolver::ResolveResponse>::Resolve_Impl(zx::unowned_channel _client_end, ::fidl::BytePart _request_buffer, ::fidl::StringView name, ::fidl::BytePart _response_buffer) {
  if (_request_buffer.capacity() < ResolveRequest::PrimarySize) {
    Super::SetFailure(::fidl::DecodeResult<ResolveResponse>(ZX_ERR_BUFFER_TOO_SMALL, ::fidl::internal::kErrorRequestBufferTooSmall));
    return;
  }
  ResolveRequest _request = {};
  _request.name = std::move(name);
  auto _linearize_result = ::fidl::Linearize(&_request, std::move(_request_buffer));
  if (_linearize_result.status != ZX_OK) {
    Super::SetFailure(std::move(_linearize_result));
    return;
  }
  ::fidl::DecodedMessage<ResolveRequest> _decoded_request = std::move(_linearize_result.message);
  Super::SetResult(
      Resolver::InPlace::Resolve(std::move(_client_end), std::move(_decoded_request), std::move(_response_buffer)));
}

Resolver::UnownedResultOf::Resolve Resolver::SyncClient::Resolve(::fidl::BytePart _request_buffer, ::fidl::StringView name, ::fidl::BytePart _response_buffer) {
  return UnownedResultOf::Resolve(zx::unowned_channel(this->channel_), std::move(_request_buffer), std::move(name), std::move(_response_buffer));
}

Resolver::UnownedResultOf::Resolve Resolver::Call::Resolve(zx::unowned_channel _client_end, ::fidl::BytePart _request_buffer, ::fidl::StringView name, ::fidl::BytePart _response_buffer) {
  return UnownedResultOf::Resolve(std::move(_client_end), std::move(_request_buffer), std::move(name), std::move(_response_buffer));
}

::fidl::DecodeResult<Resolver::ResolveResponse> Resolver::InPlace::Resolve(zx::unowned_channel _client_end, ::fidl::DecodedMessage<ResolveRequest> params, ::fidl::BytePart response_buffer) {
  params.message()->_hdr = {};
  params.message()->_hdr.ordinal = kResolver_Resolve_GenOrdinal;
  auto _encode_request_result = ::fidl::Encode(std::move(params));
  if (_encode_request_result.status != ZX_OK) {
    return ::fidl::DecodeResult<Resolver::ResolveResponse>::FromFailure(
        std::move(_encode_request_result));
  }
  auto _call_result = ::fidl::Call<ResolveRequest, ResolveResponse>(
    std::move(_client_end), std::move(_encode_request_result.message), std::move(response_buffer));
  if (_call_result.status != ZX_OK) {
    return ::fidl::DecodeResult<Resolver::ResolveResponse>::FromFailure(
        std::move(_call_result));
  }
  return ::fidl::Decode(std::move(_call_result.message));
}


bool Resolver::TryDispatch(Interface* impl, fidl_msg_t* msg, ::fidl::Transaction* txn) {
  if (msg->num_bytes < sizeof(fidl_message_header_t)) {
    zx_handle_close_many(msg->handles, msg->num_handles);
    txn->Close(ZX_ERR_INVALID_ARGS);
    return true;
  }
  fidl_message_header_t* hdr = reinterpret_cast<fidl_message_header_t*>(msg->bytes);
  switch (hdr->ordinal) {
    case kResolver_Resolve_GenOrdinal:
    {
      auto result = ::fidl::DecodeAs<ResolveRequest>(msg);
      if (result.status != ZX_OK) {
        txn->Close(ZX_ERR_INVALID_ARGS);
        return true;
      }
      auto message = result.message.message();
      impl->Resolve(std::move(message->name),
        Interface::ResolveCompleter::Sync(txn));
      return true;
    }
    default: {
      return false;
    }
  }
}

bool Resolver::Dispatch(Interface* impl, fidl_msg_t* msg, ::fidl::Transaction* txn) {
  bool found = TryDispatch(impl, msg, txn);
  if (!found) {
    zx_handle_close_many(msg->handles, msg->num_handles);
    txn->Close(ZX_ERR_NOT_SUPPORTED);
  }
  return found;
}


void Resolver::Interface::ResolveCompleterBase::Reply(int32_t status, ::zx::vmo executable, ::zx::channel ldsvc) {
  constexpr uint32_t _kWriteAllocSize = ::fidl::internal::ClampedMessageSize<ResolveResponse, ::fidl::MessageDirection::kSending>();
  FIDL_ALIGNDECL uint8_t _write_bytes[_kWriteAllocSize] = {};
  auto& _response = *reinterpret_cast<ResolveResponse*>(_write_bytes);
  _response._hdr.ordinal = kResolver_Resolve_GenOrdinal;
  _response.status = std::move(status);
  _response.executable = std::move(executable);
  _response.ldsvc = std::move(ldsvc);
  ::fidl::BytePart _response_bytes(_write_bytes, _kWriteAllocSize, sizeof(ResolveResponse));
  CompleterBase::SendReply(::fidl::DecodedMessage<ResolveResponse>(std::move(_response_bytes)));
}

void Resolver::Interface::ResolveCompleterBase::Reply(::fidl::BytePart _buffer, int32_t status, ::zx::vmo executable, ::zx::channel ldsvc) {
  if (_buffer.capacity() < ResolveResponse::PrimarySize) {
    CompleterBase::Close(ZX_ERR_INTERNAL);
    return;
  }
  auto& _response = *reinterpret_cast<ResolveResponse*>(_buffer.data());
  _response._hdr.ordinal = kResolver_Resolve_GenOrdinal;
  _response.status = std::move(status);
  _response.executable = std::move(executable);
  _response.ldsvc = std::move(ldsvc);
  _buffer.set_actual(sizeof(ResolveResponse));
  CompleterBase::SendReply(::fidl::DecodedMessage<ResolveResponse>(std::move(_buffer)));
}

void Resolver::Interface::ResolveCompleterBase::Reply(::fidl::DecodedMessage<ResolveResponse> params) {
  params.message()->_hdr = {};
  params.message()->_hdr.ordinal = kResolver_Resolve_GenOrdinal;
  CompleterBase::SendReply(std::move(params));
}


namespace {

[[maybe_unused]]
constexpr uint64_t kLauncher_Launch_GenOrdinal = 0x26884d9d00000000lu;
extern "C" const fidl_type_t fuchsia_process_LauncherLaunchRequestTable;
extern "C" const fidl_type_t fuchsia_process_LauncherLaunchResponseTable;
[[maybe_unused]]
constexpr uint64_t kLauncher_CreateWithoutStarting_GenOrdinal = 0x4fcfbc1100000000lu;
extern "C" const fidl_type_t fuchsia_process_LauncherCreateWithoutStartingRequestTable;
extern "C" const fidl_type_t fuchsia_process_LauncherCreateWithoutStartingResponseTable;
[[maybe_unused]]
constexpr uint64_t kLauncher_AddArgs_GenOrdinal = 0x1480f9a000000000lu;
extern "C" const fidl_type_t fuchsia_process_LauncherAddArgsRequestTable;
[[maybe_unused]]
constexpr uint64_t kLauncher_AddEnvirons_GenOrdinal = 0x48c62c9900000000lu;
extern "C" const fidl_type_t fuchsia_process_LauncherAddEnvironsRequestTable;
[[maybe_unused]]
constexpr uint64_t kLauncher_AddNames_GenOrdinal = 0x53fcef0c00000000lu;
extern "C" const fidl_type_t fuchsia_process_LauncherAddNamesRequestTable;
[[maybe_unused]]
constexpr uint64_t kLauncher_AddHandles_GenOrdinal = 0x5cd6900b00000000lu;
extern "C" const fidl_type_t fuchsia_process_LauncherAddHandlesRequestTable;

}  // namespace
template <>
Launcher::ResultOf::Launch_Impl<Launcher::LaunchResponse>::Launch_Impl(zx::unowned_channel _client_end, LaunchInfo info) {
  constexpr uint32_t _kWriteAllocSize = ::fidl::internal::ClampedMessageSize<LaunchRequest, ::fidl::MessageDirection::kSending>();
  std::unique_ptr _write_bytes_boxed = std::make_unique<::fidl::internal::AlignedBuffer<_kWriteAllocSize>>();
  auto& _write_bytes_array = *_write_bytes_boxed;
  LaunchRequest _request = {};
  _request.info = std::move(info);
  auto _linearize_result = ::fidl::Linearize(&_request, _write_bytes_array.view());
  if (_linearize_result.status != ZX_OK) {
    Super::SetFailure(std::move(_linearize_result));
    return;
  }
  ::fidl::DecodedMessage<LaunchRequest> _decoded_request = std::move(_linearize_result.message);
  Super::SetResult(
      Launcher::InPlace::Launch(std::move(_client_end), std::move(_decoded_request), Super::response_buffer()));
}

Launcher::ResultOf::Launch Launcher::SyncClient::Launch(LaunchInfo info) {
  return ResultOf::Launch(zx::unowned_channel(this->channel_), std::move(info));
}

Launcher::ResultOf::Launch Launcher::Call::Launch(zx::unowned_channel _client_end, LaunchInfo info) {
  return ResultOf::Launch(std::move(_client_end), std::move(info));
}

template <>
Launcher::UnownedResultOf::Launch_Impl<Launcher::LaunchResponse>::Launch_Impl(zx::unowned_channel _client_end, ::fidl::BytePart _request_buffer, LaunchInfo info, ::fidl::BytePart _response_buffer) {
  if (_request_buffer.capacity() < LaunchRequest::PrimarySize) {
    Super::SetFailure(::fidl::DecodeResult<LaunchResponse>(ZX_ERR_BUFFER_TOO_SMALL, ::fidl::internal::kErrorRequestBufferTooSmall));
    return;
  }
  LaunchRequest _request = {};
  _request.info = std::move(info);
  auto _linearize_result = ::fidl::Linearize(&_request, std::move(_request_buffer));
  if (_linearize_result.status != ZX_OK) {
    Super::SetFailure(std::move(_linearize_result));
    return;
  }
  ::fidl::DecodedMessage<LaunchRequest> _decoded_request = std::move(_linearize_result.message);
  Super::SetResult(
      Launcher::InPlace::Launch(std::move(_client_end), std::move(_decoded_request), std::move(_response_buffer)));
}

Launcher::UnownedResultOf::Launch Launcher::SyncClient::Launch(::fidl::BytePart _request_buffer, LaunchInfo info, ::fidl::BytePart _response_buffer) {
  return UnownedResultOf::Launch(zx::unowned_channel(this->channel_), std::move(_request_buffer), std::move(info), std::move(_response_buffer));
}

Launcher::UnownedResultOf::Launch Launcher::Call::Launch(zx::unowned_channel _client_end, ::fidl::BytePart _request_buffer, LaunchInfo info, ::fidl::BytePart _response_buffer) {
  return UnownedResultOf::Launch(std::move(_client_end), std::move(_request_buffer), std::move(info), std::move(_response_buffer));
}

::fidl::DecodeResult<Launcher::LaunchResponse> Launcher::InPlace::Launch(zx::unowned_channel _client_end, ::fidl::DecodedMessage<LaunchRequest> params, ::fidl::BytePart response_buffer) {
  params.message()->_hdr = {};
  params.message()->_hdr.ordinal = kLauncher_Launch_GenOrdinal;
  auto _encode_request_result = ::fidl::Encode(std::move(params));
  if (_encode_request_result.status != ZX_OK) {
    return ::fidl::DecodeResult<Launcher::LaunchResponse>::FromFailure(
        std::move(_encode_request_result));
  }
  auto _call_result = ::fidl::Call<LaunchRequest, LaunchResponse>(
    std::move(_client_end), std::move(_encode_request_result.message), std::move(response_buffer));
  if (_call_result.status != ZX_OK) {
    return ::fidl::DecodeResult<Launcher::LaunchResponse>::FromFailure(
        std::move(_call_result));
  }
  return ::fidl::Decode(std::move(_call_result.message));
}

template <>
Launcher::ResultOf::CreateWithoutStarting_Impl<Launcher::CreateWithoutStartingResponse>::CreateWithoutStarting_Impl(zx::unowned_channel _client_end, LaunchInfo info) {
  constexpr uint32_t _kWriteAllocSize = ::fidl::internal::ClampedMessageSize<CreateWithoutStartingRequest, ::fidl::MessageDirection::kSending>();
  std::unique_ptr _write_bytes_boxed = std::make_unique<::fidl::internal::AlignedBuffer<_kWriteAllocSize>>();
  auto& _write_bytes_array = *_write_bytes_boxed;
  CreateWithoutStartingRequest _request = {};
  _request.info = std::move(info);
  auto _linearize_result = ::fidl::Linearize(&_request, _write_bytes_array.view());
  if (_linearize_result.status != ZX_OK) {
    Super::SetFailure(std::move(_linearize_result));
    return;
  }
  ::fidl::DecodedMessage<CreateWithoutStartingRequest> _decoded_request = std::move(_linearize_result.message);
  Super::SetResult(
      Launcher::InPlace::CreateWithoutStarting(std::move(_client_end), std::move(_decoded_request), Super::response_buffer()));
}

Launcher::ResultOf::CreateWithoutStarting Launcher::SyncClient::CreateWithoutStarting(LaunchInfo info) {
  return ResultOf::CreateWithoutStarting(zx::unowned_channel(this->channel_), std::move(info));
}

Launcher::ResultOf::CreateWithoutStarting Launcher::Call::CreateWithoutStarting(zx::unowned_channel _client_end, LaunchInfo info) {
  return ResultOf::CreateWithoutStarting(std::move(_client_end), std::move(info));
}

template <>
Launcher::UnownedResultOf::CreateWithoutStarting_Impl<Launcher::CreateWithoutStartingResponse>::CreateWithoutStarting_Impl(zx::unowned_channel _client_end, ::fidl::BytePart _request_buffer, LaunchInfo info, ::fidl::BytePart _response_buffer) {
  if (_request_buffer.capacity() < CreateWithoutStartingRequest::PrimarySize) {
    Super::SetFailure(::fidl::DecodeResult<CreateWithoutStartingResponse>(ZX_ERR_BUFFER_TOO_SMALL, ::fidl::internal::kErrorRequestBufferTooSmall));
    return;
  }
  CreateWithoutStartingRequest _request = {};
  _request.info = std::move(info);
  auto _linearize_result = ::fidl::Linearize(&_request, std::move(_request_buffer));
  if (_linearize_result.status != ZX_OK) {
    Super::SetFailure(std::move(_linearize_result));
    return;
  }
  ::fidl::DecodedMessage<CreateWithoutStartingRequest> _decoded_request = std::move(_linearize_result.message);
  Super::SetResult(
      Launcher::InPlace::CreateWithoutStarting(std::move(_client_end), std::move(_decoded_request), std::move(_response_buffer)));
}

Launcher::UnownedResultOf::CreateWithoutStarting Launcher::SyncClient::CreateWithoutStarting(::fidl::BytePart _request_buffer, LaunchInfo info, ::fidl::BytePart _response_buffer) {
  return UnownedResultOf::CreateWithoutStarting(zx::unowned_channel(this->channel_), std::move(_request_buffer), std::move(info), std::move(_response_buffer));
}

Launcher::UnownedResultOf::CreateWithoutStarting Launcher::Call::CreateWithoutStarting(zx::unowned_channel _client_end, ::fidl::BytePart _request_buffer, LaunchInfo info, ::fidl::BytePart _response_buffer) {
  return UnownedResultOf::CreateWithoutStarting(std::move(_client_end), std::move(_request_buffer), std::move(info), std::move(_response_buffer));
}

::fidl::DecodeResult<Launcher::CreateWithoutStartingResponse> Launcher::InPlace::CreateWithoutStarting(zx::unowned_channel _client_end, ::fidl::DecodedMessage<CreateWithoutStartingRequest> params, ::fidl::BytePart response_buffer) {
  params.message()->_hdr = {};
  params.message()->_hdr.ordinal = kLauncher_CreateWithoutStarting_GenOrdinal;
  auto _encode_request_result = ::fidl::Encode(std::move(params));
  if (_encode_request_result.status != ZX_OK) {
    return ::fidl::DecodeResult<Launcher::CreateWithoutStartingResponse>::FromFailure(
        std::move(_encode_request_result));
  }
  auto _call_result = ::fidl::Call<CreateWithoutStartingRequest, CreateWithoutStartingResponse>(
    std::move(_client_end), std::move(_encode_request_result.message), std::move(response_buffer));
  if (_call_result.status != ZX_OK) {
    return ::fidl::DecodeResult<Launcher::CreateWithoutStartingResponse>::FromFailure(
        std::move(_call_result));
  }
  return ::fidl::Decode(std::move(_call_result.message));
}


Launcher::ResultOf::AddArgs_Impl::AddArgs_Impl(zx::unowned_channel _client_end, ::fidl::VectorView<::fidl::VectorView<uint8_t>> args) {
  constexpr uint32_t _kWriteAllocSize = ::fidl::internal::ClampedMessageSize<AddArgsRequest, ::fidl::MessageDirection::kSending>();
  std::unique_ptr _write_bytes_boxed = std::make_unique<::fidl::internal::AlignedBuffer<_kWriteAllocSize>>();
  auto& _write_bytes_array = *_write_bytes_boxed;
  AddArgsRequest _request = {};
  _request.args = std::move(args);
  auto _linearize_result = ::fidl::Linearize(&_request, _write_bytes_array.view());
  if (_linearize_result.status != ZX_OK) {
    Super::SetFailure(std::move(_linearize_result));
    return;
  }
  ::fidl::DecodedMessage<AddArgsRequest> _decoded_request = std::move(_linearize_result.message);
  Super::operator=(
      Launcher::InPlace::AddArgs(std::move(_client_end), std::move(_decoded_request)));
}

Launcher::ResultOf::AddArgs Launcher::SyncClient::AddArgs(::fidl::VectorView<::fidl::VectorView<uint8_t>> args) {
  return ResultOf::AddArgs(zx::unowned_channel(this->channel_), std::move(args));
}

Launcher::ResultOf::AddArgs Launcher::Call::AddArgs(zx::unowned_channel _client_end, ::fidl::VectorView<::fidl::VectorView<uint8_t>> args) {
  return ResultOf::AddArgs(std::move(_client_end), std::move(args));
}


Launcher::UnownedResultOf::AddArgs_Impl::AddArgs_Impl(zx::unowned_channel _client_end, ::fidl::BytePart _request_buffer, ::fidl::VectorView<::fidl::VectorView<uint8_t>> args) {
  if (_request_buffer.capacity() < AddArgsRequest::PrimarySize) {
    Super::status_ = ZX_ERR_BUFFER_TOO_SMALL;
    Super::error_ = ::fidl::internal::kErrorRequestBufferTooSmall;
    return;
  }
  AddArgsRequest _request = {};
  _request.args = std::move(args);
  auto _linearize_result = ::fidl::Linearize(&_request, std::move(_request_buffer));
  if (_linearize_result.status != ZX_OK) {
    Super::SetFailure(std::move(_linearize_result));
    return;
  }
  ::fidl::DecodedMessage<AddArgsRequest> _decoded_request = std::move(_linearize_result.message);
  Super::operator=(
      Launcher::InPlace::AddArgs(std::move(_client_end), std::move(_decoded_request)));
}

Launcher::UnownedResultOf::AddArgs Launcher::SyncClient::AddArgs(::fidl::BytePart _request_buffer, ::fidl::VectorView<::fidl::VectorView<uint8_t>> args) {
  return UnownedResultOf::AddArgs(zx::unowned_channel(this->channel_), std::move(_request_buffer), std::move(args));
}

Launcher::UnownedResultOf::AddArgs Launcher::Call::AddArgs(zx::unowned_channel _client_end, ::fidl::BytePart _request_buffer, ::fidl::VectorView<::fidl::VectorView<uint8_t>> args) {
  return UnownedResultOf::AddArgs(std::move(_client_end), std::move(_request_buffer), std::move(args));
}

::fidl::internal::StatusAndError Launcher::InPlace::AddArgs(zx::unowned_channel _client_end, ::fidl::DecodedMessage<AddArgsRequest> params) {
  params.message()->_hdr = {};
  params.message()->_hdr.ordinal = kLauncher_AddArgs_GenOrdinal;
  auto _encode_request_result = ::fidl::Encode(std::move(params));
  if (_encode_request_result.status != ZX_OK) {
    return ::fidl::internal::StatusAndError::FromFailure(
        std::move(_encode_request_result));
  }
  zx_status_t _write_status =
      ::fidl::Write(std::move(_client_end), std::move(_encode_request_result.message));
  if (_write_status != ZX_OK) {
    return ::fidl::internal::StatusAndError(_write_status, ::fidl::internal::kErrorWriteFailed);
  } else {
    return ::fidl::internal::StatusAndError(ZX_OK, nullptr);
  }
}


Launcher::ResultOf::AddEnvirons_Impl::AddEnvirons_Impl(zx::unowned_channel _client_end, ::fidl::VectorView<::fidl::VectorView<uint8_t>> environ) {
  constexpr uint32_t _kWriteAllocSize = ::fidl::internal::ClampedMessageSize<AddEnvironsRequest, ::fidl::MessageDirection::kSending>();
  std::unique_ptr _write_bytes_boxed = std::make_unique<::fidl::internal::AlignedBuffer<_kWriteAllocSize>>();
  auto& _write_bytes_array = *_write_bytes_boxed;
  AddEnvironsRequest _request = {};
  _request.environ = std::move(environ);
  auto _linearize_result = ::fidl::Linearize(&_request, _write_bytes_array.view());
  if (_linearize_result.status != ZX_OK) {
    Super::SetFailure(std::move(_linearize_result));
    return;
  }
  ::fidl::DecodedMessage<AddEnvironsRequest> _decoded_request = std::move(_linearize_result.message);
  Super::operator=(
      Launcher::InPlace::AddEnvirons(std::move(_client_end), std::move(_decoded_request)));
}

Launcher::ResultOf::AddEnvirons Launcher::SyncClient::AddEnvirons(::fidl::VectorView<::fidl::VectorView<uint8_t>> environ) {
  return ResultOf::AddEnvirons(zx::unowned_channel(this->channel_), std::move(environ));
}

Launcher::ResultOf::AddEnvirons Launcher::Call::AddEnvirons(zx::unowned_channel _client_end, ::fidl::VectorView<::fidl::VectorView<uint8_t>> environ) {
  return ResultOf::AddEnvirons(std::move(_client_end), std::move(environ));
}


Launcher::UnownedResultOf::AddEnvirons_Impl::AddEnvirons_Impl(zx::unowned_channel _client_end, ::fidl::BytePart _request_buffer, ::fidl::VectorView<::fidl::VectorView<uint8_t>> environ) {
  if (_request_buffer.capacity() < AddEnvironsRequest::PrimarySize) {
    Super::status_ = ZX_ERR_BUFFER_TOO_SMALL;
    Super::error_ = ::fidl::internal::kErrorRequestBufferTooSmall;
    return;
  }
  AddEnvironsRequest _request = {};
  _request.environ = std::move(environ);
  auto _linearize_result = ::fidl::Linearize(&_request, std::move(_request_buffer));
  if (_linearize_result.status != ZX_OK) {
    Super::SetFailure(std::move(_linearize_result));
    return;
  }
  ::fidl::DecodedMessage<AddEnvironsRequest> _decoded_request = std::move(_linearize_result.message);
  Super::operator=(
      Launcher::InPlace::AddEnvirons(std::move(_client_end), std::move(_decoded_request)));
}

Launcher::UnownedResultOf::AddEnvirons Launcher::SyncClient::AddEnvirons(::fidl::BytePart _request_buffer, ::fidl::VectorView<::fidl::VectorView<uint8_t>> environ) {
  return UnownedResultOf::AddEnvirons(zx::unowned_channel(this->channel_), std::move(_request_buffer), std::move(environ));
}

Launcher::UnownedResultOf::AddEnvirons Launcher::Call::AddEnvirons(zx::unowned_channel _client_end, ::fidl::BytePart _request_buffer, ::fidl::VectorView<::fidl::VectorView<uint8_t>> environ) {
  return UnownedResultOf::AddEnvirons(std::move(_client_end), std::move(_request_buffer), std::move(environ));
}

::fidl::internal::StatusAndError Launcher::InPlace::AddEnvirons(zx::unowned_channel _client_end, ::fidl::DecodedMessage<AddEnvironsRequest> params) {
  params.message()->_hdr = {};
  params.message()->_hdr.ordinal = kLauncher_AddEnvirons_GenOrdinal;
  auto _encode_request_result = ::fidl::Encode(std::move(params));
  if (_encode_request_result.status != ZX_OK) {
    return ::fidl::internal::StatusAndError::FromFailure(
        std::move(_encode_request_result));
  }
  zx_status_t _write_status =
      ::fidl::Write(std::move(_client_end), std::move(_encode_request_result.message));
  if (_write_status != ZX_OK) {
    return ::fidl::internal::StatusAndError(_write_status, ::fidl::internal::kErrorWriteFailed);
  } else {
    return ::fidl::internal::StatusAndError(ZX_OK, nullptr);
  }
}


Launcher::ResultOf::AddNames_Impl::AddNames_Impl(zx::unowned_channel _client_end, ::fidl::VectorView<NameInfo> names) {
  constexpr uint32_t _kWriteAllocSize = ::fidl::internal::ClampedMessageSize<AddNamesRequest, ::fidl::MessageDirection::kSending>();
  std::unique_ptr _write_bytes_boxed = std::make_unique<::fidl::internal::AlignedBuffer<_kWriteAllocSize>>();
  auto& _write_bytes_array = *_write_bytes_boxed;
  AddNamesRequest _request = {};
  _request.names = std::move(names);
  auto _linearize_result = ::fidl::Linearize(&_request, _write_bytes_array.view());
  if (_linearize_result.status != ZX_OK) {
    Super::SetFailure(std::move(_linearize_result));
    return;
  }
  ::fidl::DecodedMessage<AddNamesRequest> _decoded_request = std::move(_linearize_result.message);
  Super::operator=(
      Launcher::InPlace::AddNames(std::move(_client_end), std::move(_decoded_request)));
}

Launcher::ResultOf::AddNames Launcher::SyncClient::AddNames(::fidl::VectorView<NameInfo> names) {
  return ResultOf::AddNames(zx::unowned_channel(this->channel_), std::move(names));
}

Launcher::ResultOf::AddNames Launcher::Call::AddNames(zx::unowned_channel _client_end, ::fidl::VectorView<NameInfo> names) {
  return ResultOf::AddNames(std::move(_client_end), std::move(names));
}


Launcher::UnownedResultOf::AddNames_Impl::AddNames_Impl(zx::unowned_channel _client_end, ::fidl::BytePart _request_buffer, ::fidl::VectorView<NameInfo> names) {
  if (_request_buffer.capacity() < AddNamesRequest::PrimarySize) {
    Super::status_ = ZX_ERR_BUFFER_TOO_SMALL;
    Super::error_ = ::fidl::internal::kErrorRequestBufferTooSmall;
    return;
  }
  AddNamesRequest _request = {};
  _request.names = std::move(names);
  auto _linearize_result = ::fidl::Linearize(&_request, std::move(_request_buffer));
  if (_linearize_result.status != ZX_OK) {
    Super::SetFailure(std::move(_linearize_result));
    return;
  }
  ::fidl::DecodedMessage<AddNamesRequest> _decoded_request = std::move(_linearize_result.message);
  Super::operator=(
      Launcher::InPlace::AddNames(std::move(_client_end), std::move(_decoded_request)));
}

Launcher::UnownedResultOf::AddNames Launcher::SyncClient::AddNames(::fidl::BytePart _request_buffer, ::fidl::VectorView<NameInfo> names) {
  return UnownedResultOf::AddNames(zx::unowned_channel(this->channel_), std::move(_request_buffer), std::move(names));
}

Launcher::UnownedResultOf::AddNames Launcher::Call::AddNames(zx::unowned_channel _client_end, ::fidl::BytePart _request_buffer, ::fidl::VectorView<NameInfo> names) {
  return UnownedResultOf::AddNames(std::move(_client_end), std::move(_request_buffer), std::move(names));
}

::fidl::internal::StatusAndError Launcher::InPlace::AddNames(zx::unowned_channel _client_end, ::fidl::DecodedMessage<AddNamesRequest> params) {
  params.message()->_hdr = {};
  params.message()->_hdr.ordinal = kLauncher_AddNames_GenOrdinal;
  auto _encode_request_result = ::fidl::Encode(std::move(params));
  if (_encode_request_result.status != ZX_OK) {
    return ::fidl::internal::StatusAndError::FromFailure(
        std::move(_encode_request_result));
  }
  zx_status_t _write_status =
      ::fidl::Write(std::move(_client_end), std::move(_encode_request_result.message));
  if (_write_status != ZX_OK) {
    return ::fidl::internal::StatusAndError(_write_status, ::fidl::internal::kErrorWriteFailed);
  } else {
    return ::fidl::internal::StatusAndError(ZX_OK, nullptr);
  }
}


Launcher::ResultOf::AddHandles_Impl::AddHandles_Impl(zx::unowned_channel _client_end, ::fidl::VectorView<HandleInfo> handles) {
  constexpr uint32_t _kWriteAllocSize = ::fidl::internal::ClampedMessageSize<AddHandlesRequest, ::fidl::MessageDirection::kSending>();
  std::unique_ptr _write_bytes_boxed = std::make_unique<::fidl::internal::AlignedBuffer<_kWriteAllocSize>>();
  auto& _write_bytes_array = *_write_bytes_boxed;
  AddHandlesRequest _request = {};
  _request.handles = std::move(handles);
  auto _linearize_result = ::fidl::Linearize(&_request, _write_bytes_array.view());
  if (_linearize_result.status != ZX_OK) {
    Super::SetFailure(std::move(_linearize_result));
    return;
  }
  ::fidl::DecodedMessage<AddHandlesRequest> _decoded_request = std::move(_linearize_result.message);
  Super::operator=(
      Launcher::InPlace::AddHandles(std::move(_client_end), std::move(_decoded_request)));
}

Launcher::ResultOf::AddHandles Launcher::SyncClient::AddHandles(::fidl::VectorView<HandleInfo> handles) {
  return ResultOf::AddHandles(zx::unowned_channel(this->channel_), std::move(handles));
}

Launcher::ResultOf::AddHandles Launcher::Call::AddHandles(zx::unowned_channel _client_end, ::fidl::VectorView<HandleInfo> handles) {
  return ResultOf::AddHandles(std::move(_client_end), std::move(handles));
}


Launcher::UnownedResultOf::AddHandles_Impl::AddHandles_Impl(zx::unowned_channel _client_end, ::fidl::BytePart _request_buffer, ::fidl::VectorView<HandleInfo> handles) {
  if (_request_buffer.capacity() < AddHandlesRequest::PrimarySize) {
    Super::status_ = ZX_ERR_BUFFER_TOO_SMALL;
    Super::error_ = ::fidl::internal::kErrorRequestBufferTooSmall;
    return;
  }
  AddHandlesRequest _request = {};
  _request.handles = std::move(handles);
  auto _linearize_result = ::fidl::Linearize(&_request, std::move(_request_buffer));
  if (_linearize_result.status != ZX_OK) {
    Super::SetFailure(std::move(_linearize_result));
    return;
  }
  ::fidl::DecodedMessage<AddHandlesRequest> _decoded_request = std::move(_linearize_result.message);
  Super::operator=(
      Launcher::InPlace::AddHandles(std::move(_client_end), std::move(_decoded_request)));
}

Launcher::UnownedResultOf::AddHandles Launcher::SyncClient::AddHandles(::fidl::BytePart _request_buffer, ::fidl::VectorView<HandleInfo> handles) {
  return UnownedResultOf::AddHandles(zx::unowned_channel(this->channel_), std::move(_request_buffer), std::move(handles));
}

Launcher::UnownedResultOf::AddHandles Launcher::Call::AddHandles(zx::unowned_channel _client_end, ::fidl::BytePart _request_buffer, ::fidl::VectorView<HandleInfo> handles) {
  return UnownedResultOf::AddHandles(std::move(_client_end), std::move(_request_buffer), std::move(handles));
}

::fidl::internal::StatusAndError Launcher::InPlace::AddHandles(zx::unowned_channel _client_end, ::fidl::DecodedMessage<AddHandlesRequest> params) {
  params.message()->_hdr = {};
  params.message()->_hdr.ordinal = kLauncher_AddHandles_GenOrdinal;
  auto _encode_request_result = ::fidl::Encode(std::move(params));
  if (_encode_request_result.status != ZX_OK) {
    return ::fidl::internal::StatusAndError::FromFailure(
        std::move(_encode_request_result));
  }
  zx_status_t _write_status =
      ::fidl::Write(std::move(_client_end), std::move(_encode_request_result.message));
  if (_write_status != ZX_OK) {
    return ::fidl::internal::StatusAndError(_write_status, ::fidl::internal::kErrorWriteFailed);
  } else {
    return ::fidl::internal::StatusAndError(ZX_OK, nullptr);
  }
}


bool Launcher::TryDispatch(Interface* impl, fidl_msg_t* msg, ::fidl::Transaction* txn) {
  if (msg->num_bytes < sizeof(fidl_message_header_t)) {
    zx_handle_close_many(msg->handles, msg->num_handles);
    txn->Close(ZX_ERR_INVALID_ARGS);
    return true;
  }
  fidl_message_header_t* hdr = reinterpret_cast<fidl_message_header_t*>(msg->bytes);
  switch (hdr->ordinal) {
    case kLauncher_Launch_GenOrdinal:
    {
      auto result = ::fidl::DecodeAs<LaunchRequest>(msg);
      if (result.status != ZX_OK) {
        txn->Close(ZX_ERR_INVALID_ARGS);
        return true;
      }
      auto message = result.message.message();
      impl->Launch(std::move(message->info),
        Interface::LaunchCompleter::Sync(txn));
      return true;
    }
    case kLauncher_CreateWithoutStarting_GenOrdinal:
    {
      auto result = ::fidl::DecodeAs<CreateWithoutStartingRequest>(msg);
      if (result.status != ZX_OK) {
        txn->Close(ZX_ERR_INVALID_ARGS);
        return true;
      }
      auto message = result.message.message();
      impl->CreateWithoutStarting(std::move(message->info),
        Interface::CreateWithoutStartingCompleter::Sync(txn));
      return true;
    }
    case kLauncher_AddArgs_GenOrdinal:
    {
      auto result = ::fidl::DecodeAs<AddArgsRequest>(msg);
      if (result.status != ZX_OK) {
        txn->Close(ZX_ERR_INVALID_ARGS);
        return true;
      }
      auto message = result.message.message();
      impl->AddArgs(std::move(message->args),
        Interface::AddArgsCompleter::Sync(txn));
      return true;
    }
    case kLauncher_AddEnvirons_GenOrdinal:
    {
      auto result = ::fidl::DecodeAs<AddEnvironsRequest>(msg);
      if (result.status != ZX_OK) {
        txn->Close(ZX_ERR_INVALID_ARGS);
        return true;
      }
      auto message = result.message.message();
      impl->AddEnvirons(std::move(message->environ),
        Interface::AddEnvironsCompleter::Sync(txn));
      return true;
    }
    case kLauncher_AddNames_GenOrdinal:
    {
      auto result = ::fidl::DecodeAs<AddNamesRequest>(msg);
      if (result.status != ZX_OK) {
        txn->Close(ZX_ERR_INVALID_ARGS);
        return true;
      }
      auto message = result.message.message();
      impl->AddNames(std::move(message->names),
        Interface::AddNamesCompleter::Sync(txn));
      return true;
    }
    case kLauncher_AddHandles_GenOrdinal:
    {
      auto result = ::fidl::DecodeAs<AddHandlesRequest>(msg);
      if (result.status != ZX_OK) {
        txn->Close(ZX_ERR_INVALID_ARGS);
        return true;
      }
      auto message = result.message.message();
      impl->AddHandles(std::move(message->handles),
        Interface::AddHandlesCompleter::Sync(txn));
      return true;
    }
    default: {
      return false;
    }
  }
}

bool Launcher::Dispatch(Interface* impl, fidl_msg_t* msg, ::fidl::Transaction* txn) {
  bool found = TryDispatch(impl, msg, txn);
  if (!found) {
    zx_handle_close_many(msg->handles, msg->num_handles);
    txn->Close(ZX_ERR_NOT_SUPPORTED);
  }
  return found;
}


void Launcher::Interface::LaunchCompleterBase::Reply(int32_t status, ::zx::process process) {
  constexpr uint32_t _kWriteAllocSize = ::fidl::internal::ClampedMessageSize<LaunchResponse, ::fidl::MessageDirection::kSending>();
  FIDL_ALIGNDECL uint8_t _write_bytes[_kWriteAllocSize] = {};
  auto& _response = *reinterpret_cast<LaunchResponse*>(_write_bytes);
  _response._hdr.ordinal = kLauncher_Launch_GenOrdinal;
  _response.status = std::move(status);
  _response.process = std::move(process);
  ::fidl::BytePart _response_bytes(_write_bytes, _kWriteAllocSize, sizeof(LaunchResponse));
  CompleterBase::SendReply(::fidl::DecodedMessage<LaunchResponse>(std::move(_response_bytes)));
}

void Launcher::Interface::LaunchCompleterBase::Reply(::fidl::BytePart _buffer, int32_t status, ::zx::process process) {
  if (_buffer.capacity() < LaunchResponse::PrimarySize) {
    CompleterBase::Close(ZX_ERR_INTERNAL);
    return;
  }
  auto& _response = *reinterpret_cast<LaunchResponse*>(_buffer.data());
  _response._hdr.ordinal = kLauncher_Launch_GenOrdinal;
  _response.status = std::move(status);
  _response.process = std::move(process);
  _buffer.set_actual(sizeof(LaunchResponse));
  CompleterBase::SendReply(::fidl::DecodedMessage<LaunchResponse>(std::move(_buffer)));
}

void Launcher::Interface::LaunchCompleterBase::Reply(::fidl::DecodedMessage<LaunchResponse> params) {
  params.message()->_hdr = {};
  params.message()->_hdr.ordinal = kLauncher_Launch_GenOrdinal;
  CompleterBase::SendReply(std::move(params));
}


void Launcher::Interface::CreateWithoutStartingCompleterBase::Reply(int32_t status, ProcessStartData* data) {
  constexpr uint32_t _kWriteAllocSize = ::fidl::internal::ClampedMessageSize<CreateWithoutStartingResponse, ::fidl::MessageDirection::kSending>();
  FIDL_ALIGNDECL uint8_t _write_bytes[_kWriteAllocSize];
  CreateWithoutStartingResponse _response = {};
  _response._hdr.ordinal = kLauncher_CreateWithoutStarting_GenOrdinal;
  _response.status = std::move(status);
  _response.data = std::move(data);
  auto _linearize_result = ::fidl::Linearize(&_response, ::fidl::BytePart(_write_bytes,
                                                                          _kWriteAllocSize));
  if (_linearize_result.status != ZX_OK) {
    CompleterBase::Close(ZX_ERR_INTERNAL);
    return;
  }
  CompleterBase::SendReply(std::move(_linearize_result.message));
}

void Launcher::Interface::CreateWithoutStartingCompleterBase::Reply(::fidl::BytePart _buffer, int32_t status, ProcessStartData* data) {
  if (_buffer.capacity() < CreateWithoutStartingResponse::PrimarySize) {
    CompleterBase::Close(ZX_ERR_INTERNAL);
    return;
  }
  CreateWithoutStartingResponse _response = {};
  _response._hdr.ordinal = kLauncher_CreateWithoutStarting_GenOrdinal;
  _response.status = std::move(status);
  _response.data = std::move(data);
  auto _linearize_result = ::fidl::Linearize(&_response, std::move(_buffer));
  if (_linearize_result.status != ZX_OK) {
    CompleterBase::Close(ZX_ERR_INTERNAL);
    return;
  }
  CompleterBase::SendReply(std::move(_linearize_result.message));
}

void Launcher::Interface::CreateWithoutStartingCompleterBase::Reply(::fidl::DecodedMessage<CreateWithoutStartingResponse> params) {
  params.message()->_hdr = {};
  params.message()->_hdr.ordinal = kLauncher_CreateWithoutStarting_GenOrdinal;
  CompleterBase::SendReply(std::move(params));
}


}  // namespace process
}  // namespace fuchsia
}  // namespace llcpp
