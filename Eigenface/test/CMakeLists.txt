include(GoogleTest)

cmake_minimum_required(VERSION 3.14)
project(my_project)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# TODO: move to testDirectories
# TODO: dedicated tests for different classes


add_executable(
    test_Eigenface 
    src/test_EigenfaceMathBase.cpp
    src/test_EigenfaceEigenvectorFinder.cpp
)
target_link_libraries(
    test_Eigenface
    GTest::gtest_main
)
include_directories(
    ../include
)

include(GoogleTest)
gtest_discover_tests(test_Eigenface)

