//
// Created by flipback on 03.01.21.
//

#ifndef NTIO_MQTT_UTF_STRING_H
#define NTIO_MQTT_UTF_STRING_H

#include <string>

#include "ntio/mqtt/internal/types.h"

namespace ntio::mqtt::internal {
class UtfString {
 public:
  UtfString();
  explicit UtfString(const std::string& str);

  operator std::string() const;

  friend Buffer& operator<<(Buffer& buffer, const UtfString& str);
  friend Buffer& operator>>(Buffer& buffer, UtfString& str);

 private:
  std::vector<uint8_t> string_;
};
}  // namespace ntio::mqtt::internal
#endif  // NTIO_MQTT_UTF_STRING_H
