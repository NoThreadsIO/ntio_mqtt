//
// Created by flipback on 01.01.21.
//

#include "ntio/mqtt/internal/fixed_header.h"

namespace ntio::mqtt::internal {

FixedHeader::FixedHeader(ControlPacketType type, int flags, size_t remaining_length)
    : type_(type), flags_(flags), remaining_length_(remaining_length) {}

Buffer& operator<<(Buffer& buf, const FixedHeader& header) {
  uint8_t control = header.type_ | (header.flags_ & 0x0f);
  return buf << control << header.remaining_length_;
}

Buffer& operator>>(Buffer& buf, FixedHeader& header) {
  uint8_t control;
  buf >> control >> header.remaining_length_;

  header.type_ = static_cast<ControlPacketType>(0xf0 & control);
  header.flags_ = 0x0f & control;
  return buf;
}

ControlPacketType FixedHeader::type() const { return type_; }

int FixedHeader::flags() const { return flags_; }

int FixedHeader::remaining_length() const { return remaining_length_; }

std::ostream& operator<<(std::ostream& os, const FixedHeader& header) {
  os << "FixedHeader<type=" << header.type_ << ",flags=" << std::hex << header.flags_
     << ",remaining_length=" << std::dec << header.remaining_length_ << ">";
  return os;
}

}  // namespace ntio::mqtt::internal