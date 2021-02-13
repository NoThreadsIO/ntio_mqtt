//
// Created by flipback on 03.01.21.
//

#include "ntio/mqtt/internal/utf_string.h"

#include <catch2/catch.hpp>
#include <ntio/core/buffer.h>

using ntio::mqtt::internal::Buffer;
using ntio::mqtt::internal::UtfString;
using Bytes = std::vector<uint8_t>;

TEST_CASE("UtfString") {
  const Bytes kEncodedString{0, 13, 0xd0, 0x9f, 0xd1, 0x80, 0xd0, 0xb8, 0xd0, 0xb2, 0xd0, 0xb5, 0xd1, 0x82, 0x21};
  SECTION("should be decoded from buffer") {
    Buffer buffer(kEncodedString);
    UtfString utf_string;
    buffer >> utf_string;

    REQUIRE("Привет!" == static_cast<std::string>(utf_string));
  }

  SECTION("should be encoded to buffer") {
    Buffer buffer;
    UtfString utf_string("Привет!");
    buffer << utf_string;

    REQUIRE(buffer.data() == kEncodedString);
  }
}