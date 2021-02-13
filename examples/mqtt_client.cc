//
// Created by flipback on 31.12.20.
//

#include <ntio/mqtt/mqtt_client.h>

#include <coroutine>
#include <iostream>

using Task = ntio::core::Task<ntio::core::Error>;

Task MqttConnect() {
  using ntio::mqtt::MqttClient;
  using ntio::sockets::EndPoint;

  MqttClient mqtt_client;
  auto err = co_await mqtt_client.Connect(EndPoint("172.23.0.3", 1883), "test_client");
  co_return err;
}

int main() {
  auto err = MqttConnect();
  LOG_INFO("Res:" << err);
  return 0;
}