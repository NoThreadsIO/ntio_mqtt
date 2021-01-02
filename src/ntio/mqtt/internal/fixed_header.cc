//
// Created by flipback on 01.01.21.
//

#include "ntio/mqtt/internal/fixed_header.h"

namespace ntio::mqtt::internal {

FixedHeader::FixedHeader(ControlPacketType type, int flags, size_t remaining_length)
    : type_(type), flags_(flags), remaining_length_(remaining_length) {}

core::Buffer& operator<<(core::Buffer& buf, const FixedHeader& header) {
  uint8_t control = header.type_ | (header.flags_ & 0x0f);
  return buf << control << header.remaining_length_;
}

}  // namespace ntio::mqtt::internal