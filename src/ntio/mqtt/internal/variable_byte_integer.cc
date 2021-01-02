//
// Created by flipback on 02.01.21.
//

#include "variable_byte_integer.h"

namespace ntio::mqtt::internal {
VariableByteInteger::VariableByteInteger(int value) : value_(value) {}

VariableByteInteger::operator int() const { return value_; }

core::Buffer& operator<<(core::Buffer& buffer, const VariableByteInteger& integer) {
  auto val = static_cast<const int>(integer);
  do {
    auto encoded_byte = static_cast<uint8_t>(val % 128);
    val /= 128;
    if (val > 0) {
      encoded_byte |= 0x80;
    }
    buffer << encoded_byte;
  } while (val > 0);
  return buffer;
}

}  // namespace ntio::mqtt::internal