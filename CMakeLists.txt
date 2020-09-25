project(ConanDemo CXX)

cmake_minimum_required(VERSION 3.14.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS True)

include(cmake/ConfigConan.cmake)

add_executable(demo demo.cpp)
set_property(TARGET demo PROPERTY CXX_STANDARD 11)
conan_target_link_libraries(demo)

add_executable(demo_tests demo_tests.cpp)
set_property(TARGET demo_tests PROPERTY CXX_STANDARD 11)
conan_target_link_libraries(demo_tests)

include(CTest)
include(Catch)
catch_discover_tests(demo_tests
    EXTRA_ARGS -s
)