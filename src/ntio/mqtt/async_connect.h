//
// Created by flipback on 30.12.20.
//

#ifndef NTIO_MQTT_ASYNC_CONNECT_H
#define NTIO_MQTT_ASYNC_CONNECT_H

#include <ntio/core/task.h>
#include <ntio/sockets/end_point.h>
#include <ntio/sockets/tcp_socket.h>

#include <coroutine>
#include <ostream>

namespace ntio::mqtt {

class AsyncConnect {
 public:
  AsyncConnect(sockets::EndPoint end_point, const sockets::TcpSocket* socket);

  struct Awaiter {
    explicit Awaiter(AsyncConnect *owner);

    bool await_ready() noexcept;
    void await_suspend(std::coroutine_handle<> handle) noexcept;
    core::Task<core::Error> await_resume() noexcept;

    AsyncConnect* owner;
  };

  Awaiter operator co_await() noexcept;

 private:
  sockets::AsyncConnect connect_task_;
  const sockets::TcpSocket* socket_;
};
}  // namespace ntio::mqtt
#endif  // NTIO_MQTT_ASYNC_CONNECT_H
