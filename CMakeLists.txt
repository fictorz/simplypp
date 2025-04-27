
cmake_minimum_required(VERSION 3.28)

project(main)
project(MyModulesTest LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPERIMENTAL_CXX_MODULES ON)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fuse-ld=lld")

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