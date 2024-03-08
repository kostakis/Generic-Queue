cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 14)
include(GoogleTest)
enable_testing()

file(GLOB test_src_files
     "*.cpp"
)

add_executable(
  QueueTest
  ${test_src_files}
)

target_include_directories(QueueTest PRIVATE "${CMAKE_SOURCE_DIR}/include")
target_link_libraries(QueueTest PRIVATE gtest_main genericQueue)

gtest_discover_tests(QueueTest)

#Run unit tests after build
# add_custom_command(
#      TARGET QueueTest
#      COMMENT "Run tests"
#      POST_BUILD 
#      WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
#      COMMAND ${CMAKE_CTEST_COMMAND}
# )