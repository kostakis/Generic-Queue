cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 14)
include(GoogleTest)
enable_testing()

add_executable(
  QueueTest
  QueueTests.cpp
)

target_include_directories(QueueTest PUBLIC ${CMAKE_SOURCE_DIR})

target_link_libraries(
  QueueTest
  gtest_main
  genericQueue
)

gtest_discover_tests(QueueTest)
