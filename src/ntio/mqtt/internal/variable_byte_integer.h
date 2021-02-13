//
// Created by flipback on 02.01.21.
//

#ifndef NTIO_MQTT_VARIABLE_BYTE_INTEGER_H
#define NTIO_MQTT_VARIABLE_BYTE_INTEGER_H

#include "ntio/mqtt/internal/types.h"

namespace ntio::mqtt::internal {
class VariableByteInteger {
 public:

  VariableByteInteger() = default;

  explicit VariableByteInteger(int value);
  friend Buffer& operator << (Buffer& buffer, const VariableByteInteger& integer);
  friend Buffer& operator >> (Buffer& buffer, VariableByteInteger& integer);
  operator int() const;
 private:
  int value_;
};
}
#endif  // NTIO_MQTT_VARIABLE_BYTE_INTEGER_H
