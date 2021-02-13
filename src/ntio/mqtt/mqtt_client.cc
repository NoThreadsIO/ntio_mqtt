//
// Created by flipback on 30.12.20.
//

#include "ntio/mqtt/mqtt_client.h"

#include <ntio/sockets/tcp_socket.h>

namespace ntio::mqtt {

using core::Error;
using sockets::EndPoint;
using sockets::TcpSocket;

class MqttClient::Impl {
 public:
  Impl() : socket(){};

  AsyncConnect Connect(sockets::EndPoint end_point, std::string client_id) const noexcept {
    return AsyncConnect(std::move(end_point), &socket, std::move(client_id));
  }

 private:
  TcpSocket socket;
};

MqttClient::MqttClient() : impl_(std::make_unique<Impl>()) {}

MqttClient::~MqttClient() = default;

AsyncConnect MqttClient::Connect(sockets::EndPoint end_point, std::string client_id) const noexcept {
  return impl_->Connect(std::move(end_point), std::move(client_id));
}

}  // namespace ntio::mqtt