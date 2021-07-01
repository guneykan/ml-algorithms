cmake_minimum_required(VERSION 3.10)

project(ML-Algorithms VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

set(SRC_FILE_DIR ${PROJECT_SOURCE_DIR}/src)
set(TEST_FILE_DIR ${PROJECT_SOURCE_DIR}/test)

file(GLOB_RECURSE SRC_FILES ${SRC_FILE_DIR}/*.c  ${SRC_FILE_DIR}/*.cpp)
file(GLOB_RECURSE TEST_FILES ${TEST_FILE_DIR}/*.c  ${TEST_FILE_DIR}/*.cpp)


add_executable(tests ${SRC_FILES} ${TEST_FILES})

target_include_directories(tests PRIVATE ${SRC_FILE_DIR})

target_link_libraries(
  tests
  gtest_main
)

