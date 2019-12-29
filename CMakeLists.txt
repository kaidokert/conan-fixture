project(ConanDemo CXX)

cmake_minimum_required(VERSION 3.14.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS True)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

add_executable(demo demo.cpp)
set_property(TARGET demo PROPERTY CXX_STANDARD 11)
conan_target_link_libraries(demo)
