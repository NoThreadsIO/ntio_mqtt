//
// Created by flipback on 02.01.21.
//

#include "ntio/mqtt/internal/variable_byte_integer.h"

#include <catch2/catch.hpp>
#include <ntio/core/buffer.h>

using ntio::core::Buffer;
using ntio::mqtt::internal::VariableByteInteger;
using Bytes = std::vector<uint8_t>;

TEST_CASE("VariableByteInteger") {
  SECTION("should encode") {
    Buffer buf;
    SECTION("to 1 byte") {
      buf << VariableByteInteger(0) << VariableByteInteger(127);
      REQUIRE(buf.data() == Bytes{0, 127});
    }

    SECTION("to 2 bytes") {
      buf << VariableByteInteger(128) << VariableByteInteger(16383);
      REQUIRE(buf.data() == Bytes{0x80, 0x01, 0xff, 0x7f});
    }

    SECTION("to 3 bytes") {
      buf << VariableByteInteger(16'384) << VariableByteInteger(2'097'151);
      REQUIRE(buf.data() == Bytes{0x80, 0x80, 0x01, 0xff, 0xff, 0x7f});
    }

    SECTION("to 4 bytes") {
      buf << VariableByteInteger(2'097'152) << VariableByteInteger(268'435'455);
      REQUIRE(buf.data() == Bytes{0x80, 0x80, 0x80, 0x01, 0xff, 0xff, 0xff, 0x7f});
    }
  }
}