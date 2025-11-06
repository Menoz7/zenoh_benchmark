// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from latency_test_pkg:msg/LargeData.idl
// generated code does not contain a copyright notice

#ifndef LATENCY_TEST_PKG__MSG__DETAIL__LARGE_DATA__BUILDER_HPP_
#define LATENCY_TEST_PKG__MSG__DETAIL__LARGE_DATA__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "latency_test_pkg/msg/detail/large_data__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace latency_test_pkg
{

namespace msg
{

namespace builder
{

class Init_LargeData_data
{
public:
  explicit Init_LargeData_data(::latency_test_pkg::msg::LargeData & msg)
  : msg_(msg)
  {}
  ::latency_test_pkg::msg::LargeData data(::latency_test_pkg::msg::LargeData::_data_type arg)
  {
    msg_.data = std::move(arg);
    return std::move(msg_);
  }

private:
  ::latency_test_pkg::msg::LargeData msg_;
};

class Init_LargeData_size_mb
{
public:
  explicit Init_LargeData_size_mb(::latency_test_pkg::msg::LargeData & msg)
  : msg_(msg)
  {}
  Init_LargeData_data size_mb(::latency_test_pkg::msg::LargeData::_size_mb_type arg)
  {
    msg_.size_mb = std::move(arg);
    return Init_LargeData_data(msg_);
  }

private:
  ::latency_test_pkg::msg::LargeData msg_;
};

class Init_LargeData_header
{
public:
  Init_LargeData_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_LargeData_size_mb header(::latency_test_pkg::msg::LargeData::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_LargeData_size_mb(msg_);
  }

private:
  ::latency_test_pkg::msg::LargeData msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::latency_test_pkg::msg::LargeData>()
{
  return latency_test_pkg::msg::builder::Init_LargeData_header();
}

}  // namespace latency_test_pkg

#endif  // LATENCY_TEST_PKG__MSG__DETAIL__LARGE_DATA__BUILDER_HPP_
