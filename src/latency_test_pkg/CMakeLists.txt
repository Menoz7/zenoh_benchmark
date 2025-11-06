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
  DEPENDENCIES std_msgs
)

# Publisher executable
add_executable(large_data_publisher src/large_data_publisher.cpp)
ament_target_dependencies(large_data_publisher rclcpp std_msgs)
rosidl_target_interfaces(large_data_publisher ${PROJECT_NAME} "rosidl_typesupport_cpp")

# Subscriber executable
add_executable(large_data_subscriber src/large_data_subscriber.cpp)
ament_target_dependencies(large_data_subscriber rclcpp std_msgs)
rosidl_target_interfaces(large_data_subscriber ${PROJECT_NAME} "rosidl_typesupport_cpp")

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
