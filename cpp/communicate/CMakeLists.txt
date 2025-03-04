cmake_minimum_required(VERSION 3.10)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build)

project(communicate CXX)

add_executable(communicate ${CMAKE_CURRENT_SOURCE_DIR}/src/downlink.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/uplink.cpp)