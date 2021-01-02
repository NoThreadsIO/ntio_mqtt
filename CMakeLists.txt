cmake_minimum_required(VERSION 3.13)
project(ntio_mqtt VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

set(NTIO_MQTT_LOG_LEVEL "LOG_LEVEL_DEBUG" CACHE STRING "Log level LOG_LEVEL_<LEVEL>. Use empty string to switch it off")
set(NTIO_MQTT_ENABLE_EXAMPLES OFF CACHE BOOL "Compile /examples")
set(NTIO_MQTT_ENABLE_TESTS OFF CACHE BOOL "Compile /tests")

include_directories(${CMAKE_SOURCE_DIR}/src)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fcoroutines")

add_subdirectory(3dparty/ntio_sockets)
add_subdirectory(src)

if (NTIO_MQTT_ENABLE_EXAMPLES)
    add_subdirectory(examples)
endif ()

if (NTIO_MQTT_ENABLE_TESTS)
    add_subdirectory(tests)
endif ()