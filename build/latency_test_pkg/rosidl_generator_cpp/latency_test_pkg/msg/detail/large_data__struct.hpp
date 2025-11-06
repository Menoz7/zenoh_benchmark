// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from latency_test_pkg:msg/LargeData.idl
// generated code does not contain a copyright notice

#ifndef LATENCY_TEST_PKG__MSG__DETAIL__LARGE_DATA__STRUCT_HPP_
#define LATENCY_TEST_PKG__MSG__DETAIL__LARGE_DATA__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__latency_test_pkg__msg__LargeData __attribute__((deprecated))
#else
# define DEPRECATED__latency_test_pkg__msg__LargeData __declspec(deprecated)
#endif

namespace latency_test_pkg
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct LargeData_
{
  using Type = LargeData_<ContainerAllocator>;

  explicit LargeData_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->size_mb = 0ull;
    }
  }

  explicit LargeData_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->size_mb = 0ull;
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _size_mb_type =
    uint64_t;
  _size_mb_type size_mb;
  using _data_type =
    std::vector<uint8_t, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<uint8_t>>;
  _data_type data;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__size_mb(
    const uint64_t & _arg)
  {
    this->size_mb = _arg;
    return *this;
  }
  Type & set__data(
    const std::vector<uint8_t, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<uint8_t>> & _arg)
  {
    this->data = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    latency_test_pkg::msg::LargeData_<ContainerAllocator> *;
  using ConstRawPtr =
    const latency_test_pkg::msg::LargeData_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<latency_test_pkg::msg::LargeData_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<latency_test_pkg::msg::LargeData_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      latency_test_pkg::msg::LargeData_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<latency_test_pkg::msg::LargeData_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      latency_test_pkg::msg::LargeData_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<latency_test_pkg::msg::LargeData_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<latency_test_pkg::msg::LargeData_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<latency_test_pkg::msg::LargeData_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__latency_test_pkg__msg__LargeData
    std::shared_ptr<latency_test_pkg::msg::LargeData_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__latency_test_pkg__msg__LargeData
    std::shared_ptr<latency_test_pkg::msg::LargeData_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const LargeData_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->size_mb != other.size_mb) {
      return false;
    }
    if (this->data != other.data) {
      return false;
    }
    return true;
  }
  bool operator!=(const LargeData_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct LargeData_

// alias to use template instance with default allocator
using LargeData =
  latency_test_pkg::msg::LargeData_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace latency_test_pkg

#endif  // LATENCY_TEST_PKG__MSG__DETAIL__LARGE_DATA__STRUCT_HPP_
