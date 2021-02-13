//
// Created by flipback on 30.12.20.
//

#include "ntio/mqtt/async_connect.h"

#include <ntio/core/buffer.h>

#include <utility>

#include "ntio/mqtt/internal/fixed_header.h"
#include "ntio/mqtt/internal/utf_string.h"

namespace ntio::mqtt {

using core::Error;
using internal::Buffer;
using internal::ControlPacketType;
using internal::FixedHeader;
using internal::UtfString;
using internal::VariableByteInteger;
using sockets::EndPoint;
using sockets::TcpSocket;

const UtfString kProtocolName("MQTT");
const std::uint8_t kProtocolVersion = 5;

AsyncConnect::Awaiter::Awaiter(AsyncConnect *owner) : owner(owner) {}
bool AsyncConnect::Awaiter::await_ready() noexcept { return true; }

void AsyncConnect::Awaiter::await_suspend(std::coroutine_handle<> handle) noexcept {}

core::Task<core::Error> AsyncConnect::Awaiter::await_resume() const noexcept {
  auto [conn_task, socket, client_id] = *owner;
  if (auto error = co_await conn_task) {
    LOG_ERROR("TCP connection error: " << error);
    co_return error;
  }

  {
    uint8_t flags = 0;
    uint16_t keep_alive = 0;
    VariableByteInteger prop_length(0);

    Buffer rem_buf;
    rem_buf << kProtocolName << kProtocolVersion << flags << keep_alive << prop_length << UtfString(client_id);

    FixedHeader header(ControlPacketType::kConnect, 0, rem_buf.size());
    Buffer buf ;

    buf << header << rem_buf.data();
    auto [n, err] = co_await socket->Write(buf.data(), buf.size());
    // TODO: Check writen length
    if (err) {
      co_return err;
    }
  }

  {
    std::vector<uint8_t> recv_buffer(100);  // TODO: How many bytes are enough. Internal buffer?
    auto [n, err] = co_await socket->Read(&recv_buffer, recv_buffer.size());
    LOG_INFO("Recv " << n << " bytes");
    if (err) {
      co_return err;
    }
    Buffer buf(recv_buffer);
    FixedHeader header{};
    buf >> header;
    LOG_INFO("Received header: " << header);
  }

  co_return Error();
}

AsyncConnect::AsyncConnect(EndPoint end_point, const TcpSocket *socket, std::string client_id)
    : socket_(socket), connect_task_(socket->Connect(std::move(end_point))), client_id_(std::move(client_id)) {}

AsyncConnect::Awaiter AsyncConnect::operator co_await() noexcept { return Awaiter(this); }

}  // namespace ntio::mqtt