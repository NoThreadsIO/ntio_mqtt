//
// Created by flipback on 02.01.21.
//

#ifndef NTIO_MQTT_VARIABLE_BYTE_INTEGER_H
#define NTIO_MQTT_VARIABLE_BYTE_INTEGER_H

#include <ntio/core/buffer.h>

namespace ntio::mqtt::internal {
class VariableByteInteger {
 public:
  explicit VariableByteInteger(int value);
  friend core::Buffer& operator << (core::Buffer& buffer, const VariableByteInteger& integer);
  explicit operator int() const;
 private:
  int value_;
};
}
#endif  // NTIO_MQTT_VARIABLE_BYTE_INTEGER_H
