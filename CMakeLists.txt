cmake_minimum_required(VERSION 3.16)
project(main)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    message(STATUS "Compiler is Clang — enabling libc++ and coroutine support")

    add_compile_options(
        -Wall
        -Wextra
        -O3
        -fPIC
    )
    add_link_options(
    )
    # Optional: for older Clang < 14
    # add_compile_options(-fcoroutines-ts)
endif()

add_subdirectory(src)

# Adding the tests:
option(ENABLE_TESTING "Enable the tests" ON)
if(ENABLE_TESTING)
  include(CTest)
  enable_testing()
  message("Building Tests. Be sure to check out test/constexpr_tests for constexpr
testing")
  add_subdirectory(test)
endif()

install(TARGETS)