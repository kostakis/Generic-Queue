cmake_minimum_required(VERSION 3.16.0)

project(GenericQueue)

enable_testing()
add_subdirectory(external)
set(CMAKE_SUPPRESS_REGENERATION true)

set(qLibSrcFiles
    queue.c)

set(qLibHeaderFiles
    queue.h)

add_library(genericQueue
            STATIC
            ${qLibSrcFiles} ${qLibHeaderFiles})

target_include_directories(genericQueue PRIVATE .)

add_executable(example main.c)
target_link_libraries(example genericQueue)

add_subdirectory(tests)

