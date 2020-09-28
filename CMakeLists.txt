find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
  set(CMAKE_CXX_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")
endif()
set(CMAKE_NO_SYSTEM_FROM_IMPORTED True)

project(ConanDemo CXX)

cmake_minimum_required(VERSION 3.14.0)

if(MSVC)

else()
  add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS True)

include(cmake/ConfigConan.cmake)

add_executable(demo demo.cpp)
set_property(TARGET demo PROPERTY CXX_STANDARD 14)
conan_target_link_libraries(demo)

add_executable(demo_tests demo_tests.cpp demo_mocks.cpp demo_interface.h
                          demo_interface.cpp)
set_property(TARGET demo_tests PROPERTY CXX_STANDARD 14)
target_include_directories(demo_tests PRIVATE include)
conan_target_link_libraries(demo_tests)

# Prevent auto-generated ctest targets from being added
set_property(GLOBAL PROPERTY CTEST_TARGETS_ADDED 1)

include(CTest)
include(Catch)
catch_discover_tests(demo_tests EXTRA_ARGS -s)
