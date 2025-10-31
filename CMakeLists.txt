cmake_minimum_required(VERSION 3.16.0)

project(GenericQueue)

# Disable gtest installation
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)

add_subdirectory(external)

file(GLOB_RECURSE Queue_Header "include/*.h")
file(GLOB_RECURSE Queue_Src "src/*.c")

# Generic queue static libray
add_library(genericQueue STATIC ${Queue_Header} ${Queue_Src})
target_include_directories(genericQueue PUBLIC "include/")

# A simple main for example
add_executable(example "main.c")
target_link_libraries(example PRIVATE genericQueue)

# Unit tests
enable_testing()
add_subdirectory(tests)

# Installation rules
install(TARGETS genericQueue
    ARCHIVE DESTINATION lib)

install(FILES include/queue.h
    DESTINATION include)
