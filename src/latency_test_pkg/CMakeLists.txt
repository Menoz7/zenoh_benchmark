cmake_minimum_required(VERSION 3.8)
project(latency_test_pkg)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(rosidl_default_generators REQUIRED)

# Generate messages
rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/LargeData.msg"
  "msg/LargeDataAck.msg"
  DEPENDENCIES std_msgs
)

ament_export_dependencies(rosidl_default_runtime)

# Publisher executable
add_executable(large_data_publisher src/large_data_publisher.cpp)
ament_target_dependencies(large_data_publisher rclcpp std_msgs)
rosidl_get_typesupport_target(cpp_typesupport_target ${PROJECT_NAME} "rosidl_typesupport_cpp")
target_link_libraries(large_data_publisher "${cpp_typesupport_target}")

# Subscriber executable
add_executable(large_data_subscriber src/large_data_subscriber.cpp)
ament_target_dependencies(large_data_subscriber rclcpp std_msgs)
target_link_libraries(large_data_subscriber "${cpp_typesupport_target}")

# Install executables
install(TARGETS
  large_data_publisher
  large_data_subscriber
  DESTINATION lib/${PROJECT_NAME}
)

# Install config files
install(DIRECTORY
  config
  DESTINATION share/${PROJECT_NAME}
)

ament_package()
