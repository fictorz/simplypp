cmake_minimum_required(VERSION 3.16.3)

project(Simply  VERSION 1.0
                DESCRIPTION "Simply"
                LANGUAGES CXX)

add_compile_options("-Wno-deprecated-declarations")
add_compile_options("-Wno-inconsistent-missing-override")
add_compile_options("-Wunused-parameter")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

message(STATUS "Building ${CMAKE_BUILD_TYPE}")
IF(CMAKE_BUILD_TYPE MATCHES DEBUG)
    SET(CMAKE_C_FLAGS_DEBUG "-ggdb -O0")  # Tuning debugger for gdb and level 0 of optimisation
    SET(CMAKE_CXX_FLAGS_DEBUG "-ggdb -O0")  # Tuning debugger for gdb and level 0 of optimisation
ELSE()
    SET(CMAKE_C_FLAGS "-O3 -DNDEBUG")  # Tuning debugger for gdb and level 3 of optimisation
    SET(CMAKE_CXX_FLAGS "-O3 -DNDEBUG")  # Tuning for level 3 of optimisation
ENDIF(CMAKE_BUILD_TYPE MATCHES DEBUG)

IF(NOT DEFINED APP_NAME)
    set(APP_NAME "application")
    message(STATUS "Hack to provide default variable, APP_NAME to prevent an error message.")
ENDIF()

## PROTO SECTION ## 
find_package(Protobuf REQUIRED)

# Include generated protobuf files
include_directories(${PROTOBUF_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

# Generate C++ files from the .proto file
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS proto/example.proto)

## PROTO SECTION END ## 

SET(APPLICATION_SOURCE_FILES 
    util/logging.cc
    shapes/circle.cc
    shapes/square.cc
    coroutines/coroutines.cc
    coroutines/timeout_awaitable.cc
    coroutines/executables.cc
    proto/message_handler.cc
)

SET(APPLICATION_INCLUDE_DIRS
    src
)

find_package (glog 0.5.0 REQUIRED)

# Compile library (to reuse with tests)
add_library(application_lib SHARED ${APPLICATION_SOURCE_FILES} ${PROTO_SRCS} ${PROTO_HDRS})
target_include_directories(application_lib PUBLIC ${APPLICATION_INCLUDE_DIRS})
target_link_libraries(application_lib glog::glog ${PROTOBUF_LIBRARIES})

# Compile Application
add_executable(application "main.cc")
target_link_libraries(application application_lib)

install(TARGETS application)
