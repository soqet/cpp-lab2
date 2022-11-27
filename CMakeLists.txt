cmake_minimum_required(VERSION 3.18)
project(lab2 VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)


add_executable(lab2 interpreter_error.hpp interpreter.hpp command.hpp command.cpp main.cpp)

add_executable(lab2_test interpreter.hpp interpreter_error.hpp interpreter_test.cpp)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

#SET(WARN_FLAGS "-Wall -Wpedantic -Werror")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${WARN_FLAGS} ${ASAN_OPTIONS}")

enable_testing()

target_link_libraries(
  lab2_test
  GTest::gtest_main
)

target_compile_options(
  lab2_test
  PRIVATE
  -fsanitize=address
)

target_link_options(
  lab2_test
  PRIVATE
  -fsanitize=address
)

include(GoogleTest)
gtest_discover_tests(lab2_test)