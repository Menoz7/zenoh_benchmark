// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from latency_test_pkg:msg/LargeData.idl
// generated code does not contain a copyright notice

#ifndef LATENCY_TEST_PKG__MSG__DETAIL__LARGE_DATA__TRAITS_HPP_
#define LATENCY_TEST_PKG__MSG__DETAIL__LARGE_DATA__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "latency_test_pkg/msg/detail/large_data__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"

namespace latency_test_pkg
{

namespace msg
{

inline void to_flow_style_yaml(
  const LargeData & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: size_mb
  {
    out << "size_mb: ";
    rosidl_generator_traits::value_to_yaml(msg.size_mb, out);
    out << ", ";
  }

  // member: data
  {
    if (msg.data.size() == 0) {
      out << "data: []";
    } else {
      out << "data: [";
      size_t pending_items = msg.data.size();
      for (auto item : msg.data) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const LargeData & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: header
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "header:\n";
    to_block_style_yaml(msg.header, out, indentation + 2);
  }

  // member: size_mb
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "size_mb: ";
    rosidl_generator_traits::value_to_yaml(msg.size_mb, out);
    out << "\n";
  }

  // member: data
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.data.size() == 0) {
      out << "data: []\n";
    } else {
      out << "data:\n";
      for (auto item : msg.data) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const LargeData & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace latency_test_pkg

namespace rosidl_generator_traits
{

[[deprecated("use latency_test_pkg::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const latency_test_pkg::msg::LargeData & msg,
  std::ostream & out, size_t indentation = 0)
{
  latency_test_pkg::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use latency_test_pkg::msg::to_yaml() instead")]]
inline std::string to_yaml(const latency_test_pkg::msg::LargeData & msg)
{
  return latency_test_pkg::msg::to_yaml(msg);
}

template<>
inline const char * data_type<latency_test_pkg::msg::LargeData>()
{
  return "latency_test_pkg::msg::LargeData";
}

template<>
inline const char * name<latency_test_pkg::msg::LargeData>()
{
  return "latency_test_pkg/msg/LargeData";
}

template<>
struct has_fixed_size<latency_test_pkg::msg::LargeData>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<latency_test_pkg::msg::LargeData>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<latency_test_pkg::msg::LargeData>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // LATENCY_TEST_PKG__MSG__DETAIL__LARGE_DATA__TRAITS_HPP_
