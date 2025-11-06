// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from latency_test_pkg:msg/LargeData.idl
// generated code does not contain a copyright notice

#ifndef LATENCY_TEST_PKG__MSG__DETAIL__LARGE_DATA__STRUCT_H_
#define LATENCY_TEST_PKG__MSG__DETAIL__LARGE_DATA__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.h"
// Member 'data'
#include "rosidl_runtime_c/primitives_sequence.h"

/// Struct defined in msg/LargeData in the package latency_test_pkg.
typedef struct latency_test_pkg__msg__LargeData
{
  std_msgs__msg__Header header;
  uint64_t size_mb;
  rosidl_runtime_c__uint8__Sequence data;
} latency_test_pkg__msg__LargeData;

// Struct for a sequence of latency_test_pkg__msg__LargeData.
typedef struct latency_test_pkg__msg__LargeData__Sequence
{
  latency_test_pkg__msg__LargeData * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} latency_test_pkg__msg__LargeData__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // LATENCY_TEST_PKG__MSG__DETAIL__LARGE_DATA__STRUCT_H_
