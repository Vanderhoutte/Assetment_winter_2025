cmake_minimum_required(VERSION 3.10)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build)

project(communicate CXX)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(communicate_msgs REQUIRED)

add_executable(communicate ${CMAKE_CURRENT_SOURCE_DIR}/src/downlink.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/uplink.cpp)

target_link_libraries(communicate
  rclcpp
  std_msgs::msg
  geometry_msgs::msg
  communicate_msgs::msg)

ament_target_dependencies(communicate
  "rclcpp"
  "std_msgs"
  "geometry_msgs"
  "communicate_msgs")
