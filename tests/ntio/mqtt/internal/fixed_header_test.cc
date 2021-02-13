//
// Created by flipback on 02.01.21.
//

#include "ntio/mqtt/internal/fixed_header.h"

#include <catch2/catch.hpp>
#include <ntio/core/buffer.h>

using ntio::mqtt::internal::ControlPacketType;
using ntio::mqtt::internal::FixedHeader;
using ntio::mqtt::internal::Buffer;
using Bytes = std::vector<uint8_t>;

TEST_CASE("FixedHeader") {
  SECTION("should be decoded from buffer") {
    Buffer buf(Bytes {0x13, 0x80, 0x01});
    FixedHeader header{};
    buf >> header;
    REQUIRE(header.type() == ControlPacketType::kConnect);
    REQUIRE(header.flags() == 3);
    REQUIRE(header.remaining_length() == 128);
  }

  SECTION("should be encoded to buffer") {
    Buffer buf;
    FixedHeader header(ControlPacketType::kConnect, 3, 128);
    buf << header;
    REQUIRE(buf.data() == Bytes {0x13, 0x80, 0x01});
  }
}