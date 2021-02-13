Include(FetchContent)

FetchContent_Declare(
        Catch2
        URL https://github.com/catchorg/Catch2/archive/v2.13.4.zip)

FetchContent_MakeAvailable(Catch2)

set(SOURCE_FILES
        ntio/mqtt/internal/fixed_header_test.cc
        ntio/mqtt/internal/utf_string_test.cc
        ntio/mqtt/internal/variable_byte_integer_test.cc
        main.cc)

add_executable(ntio_mqtt_test ${SOURCE_FILES})

target_link_libraries(ntio_mqtt_test PRIVATE Catch2::Catch2 ntio_mqtt)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/contrib)
include(CTest)
include(Catch)
catch_discover_tests(ntio_mqtt_test)