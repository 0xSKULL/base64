cmake_minimum_required(VERSION 3.14)
project(mtrp-base64 LANGUAGES C CXX)

include(CTest) # automatically creates a BUILD_TESTING option
set(BUILD_TESTS OFF)
option(BUILD_TOOLS OFF)
option(BUILD_SHARED_LIBS OFF)

# Configuration
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

if(NOT CMAKE_ARCHIVE_OUTPUT_DIRECTORY)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/lib/")
endif()

if(NOT CMAKE_LIBRARY_OUTPUT_DIRECTORY)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/lib/")
endif()

if(NOT CMAKE_RUNTIME_OUTPUT_DIRECTORY)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin/")
endif()

# Library
add_library(mtrp-base64 "${CMAKE_CURRENT_SOURCE_DIR}/src/base64.c" "${CMAKE_CURRENT_SOURCE_DIR}/src/base64url.c")
target_include_directories(mtrp-base64 PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/")

# Tests
if(BUILD_TESTING)
    include("${CMAKE_CURRENT_SOURCE_DIR}/tests/tests.cmake")
endif()

# Tools
if(BUILD_TOOLS)
    include("${CMAKE_CURRENT_SOURCE_DIR}/tools/tools.cmake")
endif()
