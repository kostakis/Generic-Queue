cmake_minimum_required(VERSION 3.16.0)

project(GenericQueue)

add_subdirectory(external)

# For google test
set(CMAKE_SUPPRESS_REGENERATION true)

file(GLOB_RECURSE Queue_Header "include/*.h")
file(GLOB_RECURSE Queue_Src "src/*.c")

add_library(genericQueue STATIC ${Queue_Header} ${Queue_Src})
target_include_directories(genericQueue PUBLIC "include/")

add_executable(example "main.c")
target_link_libraries(example PRIVATE genericQueue)

enable_testing()
add_subdirectory(tests)
