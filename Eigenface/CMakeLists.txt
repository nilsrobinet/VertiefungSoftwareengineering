cmake_minimum_required(VERSION 3.13)

project(eingenface)
set(CMAKE_CXX_STANDARD 20)

# Set the compiler options based on the build type
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Configuring for Debug build")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g")
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    message(STATUS "Configuring for Release build")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
else()
    message(WARNING "Unknown build type: ${CMAKE_BUILD_TYPE}")
endif()

add_subdirectory(src)
add_subdirectory(test)

set(
      ARCHIVE_OUTPUT_DIRECTORY "build"
      LIBRARY_OUTPUT_DIRECTORY "build"
      RUNTIME_OUTPUT_DIRECTORY "build"
)

