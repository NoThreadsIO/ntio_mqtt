//
// Created by flipback on 02.01.21.
//

#include "ntio/mqtt/internal/fixed_header.h"

#include <catch2/catch.hpp>
#include <ntio/core/buffer.h>

using ntio::core::Buffer;
using ntio::mqtt::internal::ControlPacketType;
using ntio::mqtt::internal::FixedHeader;
using Bytes = std::vector<uint8_t>;

TEST_CASE("FixedHeader") {
  Buffer buf;
  SECTION("should encode to buffer") {
    FixedHeader header(ControlPacketType::kConnect, 3, 128);
    buf << header;
    REQUIRE(buf.data() == Bytes {0x13, 0x80, 0x01});
  }
}