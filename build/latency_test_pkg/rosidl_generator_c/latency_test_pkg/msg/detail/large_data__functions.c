// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from latency_test_pkg:msg/LargeData.idl
// generated code does not contain a copyright notice
#include "latency_test_pkg/msg/detail/large_data__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"
// Member `data`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

bool
latency_test_pkg__msg__LargeData__init(latency_test_pkg__msg__LargeData * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    latency_test_pkg__msg__LargeData__fini(msg);
    return false;
  }
  // size_mb
  // data
  if (!rosidl_runtime_c__uint8__Sequence__init(&msg->data, 0)) {
    latency_test_pkg__msg__LargeData__fini(msg);
    return false;
  }
  return true;
}

void
latency_test_pkg__msg__LargeData__fini(latency_test_pkg__msg__LargeData * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // size_mb
  // data
  rosidl_runtime_c__uint8__Sequence__fini(&msg->data);
}

bool
latency_test_pkg__msg__LargeData__are_equal(const latency_test_pkg__msg__LargeData * lhs, const latency_test_pkg__msg__LargeData * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__are_equal(
      &(lhs->header), &(rhs->header)))
  {
    return false;
  }
  // size_mb
  if (lhs->size_mb != rhs->size_mb) {
    return false;
  }
  // data
  if (!rosidl_runtime_c__uint8__Sequence__are_equal(
      &(lhs->data), &(rhs->data)))
  {
    return false;
  }
  return true;
}

bool
latency_test_pkg__msg__LargeData__copy(
  const latency_test_pkg__msg__LargeData * input,
  latency_test_pkg__msg__LargeData * output)
{
  if (!input || !output) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__copy(
      &(input->header), &(output->header)))
  {
    return false;
  }
  // size_mb
  output->size_mb = input->size_mb;
  // data
  if (!rosidl_runtime_c__uint8__Sequence__copy(
      &(input->data), &(output->data)))
  {
    return false;
  }
  return true;
}

latency_test_pkg__msg__LargeData *
latency_test_pkg__msg__LargeData__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  latency_test_pkg__msg__LargeData * msg = (latency_test_pkg__msg__LargeData *)allocator.allocate(sizeof(latency_test_pkg__msg__LargeData), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(latency_test_pkg__msg__LargeData));
  bool success = latency_test_pkg__msg__LargeData__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
latency_test_pkg__msg__LargeData__destroy(latency_test_pkg__msg__LargeData * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    latency_test_pkg__msg__LargeData__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
latency_test_pkg__msg__LargeData__Sequence__init(latency_test_pkg__msg__LargeData__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  latency_test_pkg__msg__LargeData * data = NULL;

  if (size) {
    data = (latency_test_pkg__msg__LargeData *)allocator.zero_allocate(size, sizeof(latency_test_pkg__msg__LargeData), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = latency_test_pkg__msg__LargeData__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        latency_test_pkg__msg__LargeData__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
latency_test_pkg__msg__LargeData__Sequence__fini(latency_test_pkg__msg__LargeData__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      latency_test_pkg__msg__LargeData__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

latency_test_pkg__msg__LargeData__Sequence *
latency_test_pkg__msg__LargeData__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  latency_test_pkg__msg__LargeData__Sequence * array = (latency_test_pkg__msg__LargeData__Sequence *)allocator.allocate(sizeof(latency_test_pkg__msg__LargeData__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = latency_test_pkg__msg__LargeData__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
latency_test_pkg__msg__LargeData__Sequence__destroy(latency_test_pkg__msg__LargeData__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    latency_test_pkg__msg__LargeData__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
latency_test_pkg__msg__LargeData__Sequence__are_equal(const latency_test_pkg__msg__LargeData__Sequence * lhs, const latency_test_pkg__msg__LargeData__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!latency_test_pkg__msg__LargeData__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
latency_test_pkg__msg__LargeData__Sequence__copy(
  const latency_test_pkg__msg__LargeData__Sequence * input,
  latency_test_pkg__msg__LargeData__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(latency_test_pkg__msg__LargeData);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    latency_test_pkg__msg__LargeData * data =
      (latency_test_pkg__msg__LargeData *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!latency_test_pkg__msg__LargeData__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          latency_test_pkg__msg__LargeData__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!latency_test_pkg__msg__LargeData__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
