set(SOURCE_FILES
        ntio/mqtt/internal/fixed_header.cc
        ntio/mqtt/internal/utf_string.cc
        ntio/mqtt/internal/variable_byte_integer.cc
        ntio/mqtt/async_connect.cc
        ntio/mqtt/mqtt_client.cc
        )

set(PUBLIC_HEADERS
        ntio/mqtt/mqtt_client.h
        )

add_library(ntio_mqtt STATIC ${SOURCE_FILES} ${PUBLIC_HEADERS})
target_link_libraries(ntio_mqtt ntio_sockets)
target_compile_definitions(ntio_mqtt PUBLIC ${NTIO_MQTT_LOG_LEVEL})

target_include_directories(ntio_mqtt PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})