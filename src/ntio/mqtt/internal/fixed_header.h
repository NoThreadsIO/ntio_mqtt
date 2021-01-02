//
// Created by flipback on 01.01.21.
//

#ifndef NTIO_MQTT_FIXED_HEADER_H
#define NTIO_MQTT_FIXED_HEADER_H

#include <ntio/core/buffer.h>

#include <cstddef>

#include "ntio/mqtt/internal/variable_byte_integer.h"

namespace ntio::mqtt::internal {

enum ControlPacketType : uint8_t {
  kConnect = 1 << 4,  //! Connection request
  kConnAck = 2 << 4,  //! Connect acknowledgment
};

class FixedHeader {
 public:
  FixedHeader(ControlPacketType type, int flags, size_t remaining_length);

  friend core::Buffer& operator<<(core::Buffer& buf, const FixedHeader& header);

 private:
  ControlPacketType type_;
  int flags_;
  VariableByteInteger remaining_length_;
};

}  // namespace ntio::mqtt::internal
#endif  // NTIO_MQTT_FIXED_HEADER_H
