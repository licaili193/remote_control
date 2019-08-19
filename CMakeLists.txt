cmake_minimum_required(VERSION 3.1.0)

project(remote_control)

set (CMAKE_CXX_STANDARD 14)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_PREFIX_PATH ${QT_PATH})
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

# Universial dependency:

# OpenCV
find_package(OpenCV REQUIRED)
message(STATUS "OpenCV library status:")
message(STATUS "version: ${OpenCV_VERSION}")
message(STATUS "libraries: ${OpenCV_LIBS}")
message(STATUS "include path: ${OpenCV_INCLUDE_DIRS}")
include_directories(${OpenCV_INCLUDE_DIRS})

# GLog
find_package(Glog REQUIRED)
include_directories(${GLOG_INCLUDE_DIRS}) 

# GFlags
find_package (gflags REQUIRED)
include_directories (${gflags_INCLUDE_DIR})

# Yaml-cpp
find_package (yaml-cpp REQUIRED)
include_directories (${YAML_CPP_INCLUDE_DIR})

# Fast-RTPS
find_package(fastcdr REQUIRED)
find_package(fastrtps REQUIRED)

# Thread
find_package(Threads REQUIRED)

# Blend2d
set(BLEND2D_DIR "${CMAKE_SOURCE_DIR}/src/third_party/blend2d")
set(ASMJIT_DIR "${CMAKE_SOURCE_DIR}/src/third_party/asmhit")
set(BLEND2D_STATIC TRUE)
include("${BLEND2D_DIR}/CMakeLists.txt")

add_subdirectory(src)
