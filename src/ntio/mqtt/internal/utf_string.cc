//
// Created by flipback on 03.01.21.
//

#include "utf_string.h"
namespace ntio::mqtt::internal {

UtfString::UtfString() : string_() {}

UtfString::UtfString(const std::string& str) : string_(str.begin(), str.end()) {}

Buffer& operator>>(Buffer& buffer, UtfString& str) {
  uint16_t len;
  buffer >> len;

  str.string_.resize(len);
  buffer >> str.string_;

  return buffer;
}

Buffer& operator<<(Buffer& buffer, const UtfString& str) {
  buffer << static_cast<uint16_t>(str.string_.size()) << str.string_;
  return buffer;
}

UtfString::operator std::string() const { return std::string(string_.begin(), string_.end()); }

}  // namespace ntio::mqtt::internal
