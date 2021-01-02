//
// Created by flipback on 30.12.20.
//

#ifndef NTIO_MQTT_MQTT_CLIENT_H
#define NTIO_MQTT_MQTT_CLIENT_H

#include <ntio/sockets/end_point.h>

#include <memory>

#include "ntio/mqtt/async_connect.h"

namespace ntio::mqtt {

using sockets::EndPoint;

class IMqttClient {
 public:
  virtual ~IMqttClient() = default;
  virtual AsyncConnect Connect(EndPoint end_point, std::string client_id) const noexcept = 0;
};

class MqttClient : public IMqttClient {
 public:
  MqttClient();
  ~MqttClient() override;
  AsyncConnect Connect(EndPoint end_point, std::string client_id) const noexcept override;

 private:
  class Impl;
  std::unique_ptr<Impl> impl_;
};

}  // namespace ntio::mqtt

#endif  // NTIO_MQTT_MQTT_CLIENT_H
