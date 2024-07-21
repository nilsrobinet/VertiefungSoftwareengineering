# Set the compiler options based on the build type
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Configuring for Debug build")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g -Wall -shared -pthread -fPIC -fwrapv -fno-strict-aliasing")
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    message(STATUS "Configuring for Release build")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -Wall -Werror -shared -pthread -fPIC -fwrapv -fno-strict-aliasing")
else()
    message(WARNING "Unknown build type: ${CMAKE_BUILD_TYPE}")
endif()
set(CMAKE_SHARED_LIBRARY_PREFIX "")

add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/Eigenface.cpp
    COMMAND cython ${PROJECT_SOURCE_DIR}/cython/Eigenface.pyx --cplus --3str -o ${CMAKE_CURRENT_BINARY_DIR}/Eigenface.cpp
    DEPENDS Eigenface.pyx
    COMMENT "Genreating Eigenface.cpp from Eigenface.pyx"
    VERBATIM
)
add_custom_target(
    Eigenface_cython ALL
    DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/Eigenface.cpp
)
# Find Python executable
find_package(PythonInterp REQUIRED)

# Get the NumPy include directory
execute_process(
    COMMAND ${PYTHON_EXECUTABLE} -c "import numpy; print(numpy.get_include())"
    OUTPUT_VARIABLE NUMPY_INCLUDE_DIR
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

include_directories(
    /usr/include/python3.12/
    ../include
    ${NUMPY_INCLUDE_DIR}
)

add_definitions(-DNPY_NO_DEPRECATED_API=NPY_1_7_API_VERSION)

add_library(
    Eigenface
    SHARED
    ${CMAKE_CURRENT_BINARY_DIR}/Eigenface.cpp
    ${PROJECT_SOURCE_DIR}/src/EigenfaceMain.cpp
    
)
add_dependencies(Eigenface Eigenface_cython)

install( TARGETS Eigenface
        DESTINATION ${PROJECT_SOURCE_DIR}/../bin
)