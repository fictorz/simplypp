cmake_minimum_required(VERSION 3.16)
project(main)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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