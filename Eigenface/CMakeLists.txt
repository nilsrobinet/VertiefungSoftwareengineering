cmake_minimum_required(VERSION 3.13)

project(eingenface)
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src)
add_subdirectory(test)

set(
      ARCHIVE_OUTPUT_DIRECTORY "build"
      LIBRARY_OUTPUT_DIRECTORY "build"
      RUNTIME_OUTPUT_DIRECTORY "build"
)

