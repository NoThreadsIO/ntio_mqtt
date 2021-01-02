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
  auto err = co_await mqtt_client.Connect(EndPoint("127.0.0.1", 1883), "test_client");
  co_return err;
}

int main() {
  MqttConnect();
  return 0;
}