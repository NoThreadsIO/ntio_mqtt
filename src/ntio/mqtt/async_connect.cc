//
// Created by flipback on 30.12.20.
//

#include "ntio/mqtt/async_connect.h"

#include <ntio/core/buffer.h>

#include <utility>

#include "ntio/mqtt/internal/fixed_header.h"

namespace ntio::mqtt {

using core::Buffer;
using internal::ControlPacketType;
using internal::FixedHeader;
using sockets::EndPoint;
using sockets::TcpSocket;

AsyncConnect::Awaiter::Awaiter(AsyncConnect *owner) : owner(owner) {}
bool AsyncConnect::Awaiter::await_ready() noexcept { return true; }

void AsyncConnect::Awaiter::await_suspend(std::coroutine_handle<> handle) noexcept {}

core::Task<core::Error> AsyncConnect::Awaiter::await_resume() noexcept {
  auto [conn_task, socket] = *owner;
  if (auto error = co_await conn_task) {
    LOG_ERROR("TCP connection error: " << error);
    co_return error;
  }

  FixedHeader header(ControlPacketType::kConnect, 0, 1);
  Buffer buf;
  buf << header;
  auto [n, error] = co_await socket->Write(buf.data(), buf.size());
  // TODO: Check writen length

  co_return error;
}

AsyncConnect::AsyncConnect(EndPoint end_point, const TcpSocket *socket)
    : socket_(socket), connect_task_(socket->Connect(std::move(end_point))) {}

AsyncConnect::Awaiter AsyncConnect::operator co_await() noexcept { return Awaiter(this); }

}  // namespace ntio::mqtt