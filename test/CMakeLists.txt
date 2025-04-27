cmake_minimum_required(VERSION 3.28)

project(Simply_test VERSION 1.0 DESCRIPTION "Simply Tests" LANGUAGES CXX)

add_compile_options("-Wno-deprecated-declarations" "-Wno-inconsistent-missing-override")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPERIMENTAL_CXX_MODULES ON)

message(STATUS "Building ${CMAKE_BUILD_TYPE}")

if(CMAKE_BUILD_TYPE MATCHES Debug)
    set(CMAKE_C_FLAGS_DEBUG "-ggdb -O0")
    set(CMAKE_CXX_FLAGS_DEBUG "-ggdb -O0")
else()
    set(CMAKE_C_FLAGS "-O3 -DNDEBUG")
    set(CMAKE_CXX_FLAGS "-O3 -DNDEBUG")
endif()

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

set(TEST_APPLICATION_SRC
    modules/test_math.cc
    shapes/test_shapes.cc
    proto/test_message_handler.cc
)

add_executable(basic_test_application "main.cc" ${TEST_APPLICATION_SRC})

target_include_directories(basic_test_application PUBLIC "${PROJECT_SOURCE_DIR}/../src")

target_link_libraries(basic_test_application
    PUBLIC
        application_lib
        ${GTEST_LIBRARIES}
        pthread
)

install(TARGETS basic_test_application)

add_test(NAME basic_test_application COMMAND basic_test_application)
