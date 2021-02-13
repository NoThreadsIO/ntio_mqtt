//
// Created by flipback on 02.01.21.
//

#include "ntio/mqtt/internal/variable_byte_integer.h"

#include <catch2/catch.hpp>
#include <ntio/core/buffer.h>

using ntio::mqtt::internal::Buffer;
using ntio::mqtt::internal::VariableByteInteger;
using Bytes = std::vector<uint8_t>;

TEST_CASE("VariableByteInteger") {
  SECTION("should be encoded") {
    Buffer buf;
    SECTION("to 1 byte") {
      buf << VariableByteInteger(0) << VariableByteInteger(127);
      REQUIRE(buf.data() == Bytes{0, 127});
    }

    SECTION("to 2 bytes") {
      buf << VariableByteInteger(128) << VariableByteInteger(16'383);
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

  SECTION("should be decoded") {
    VariableByteInteger var1{}, var2{};
    SECTION("from 1 byte") {
      Buffer buf(Bytes{0, 127});
      buf >> var1 >> var2;
      REQUIRE(var1 == 0);
      REQUIRE(var2 == 127);
    }

    SECTION("from 2 bytes") {
      Buffer buf(Bytes{0x80, 0x01, 0xff, 0x7f});
      buf >> var1 >> var2;
      REQUIRE(var1 == 128);
      REQUIRE(var2 == 16'383);
    }

    SECTION("from 3 bytes") {
      Buffer buf(Bytes{0x80, 0x80, 0x01, 0xff, 0xff, 0x7f});
      buf >> var1 >> var2;
      REQUIRE(var1 == 16'384);
      REQUIRE(var2 == 2'097'151);
    }

    SECTION("from 4 bytes") {
      Buffer buf(Bytes{0x80, 0x80, 0x80, 0x01, 0xff, 0xff, 0xff, 0x7f});
      buf >> var1 >> var2;
      REQUIRE(var1 == 2'097'152);
      REQUIRE(var2 == 268'435'455);
    }
  }
}