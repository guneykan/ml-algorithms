cmake_minimum_required(VERSION 3.10)

project(ML-Algorithms VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SRC_FILE_DIR ${PROJECT_SOURCE_DIR}/src)

file(GLOB_RECURSE SRC_FILES ${SRC_FILE_DIR}/*.c  ${SRC_FILE_DIR}/*.cpp)

add_executable(Test ${SRC_FILES})
