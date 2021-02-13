//
// Created by flipback on 13.02.21.
//

#ifndef NTIO_MQTT_TYPES_H
#define NTIO_MQTT_TYPES_H

#include <ntio/core/buffer.h>

namespace ntio::mqtt::internal {

using Buffer = ::ntio::core::Buffer<::ntio::core::Order::kBigEndian>;

}
#endif  // NTIO_MQTT_TYPES_H
