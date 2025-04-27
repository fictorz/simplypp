cmake_minimum_required(VERSION 3.28)

project(Simply VERSION 1.0 DESCRIPTION "Simply" LANGUAGES CXX)

add_compile_options("-Wno-deprecated-declarations" "-Wno-inconsistent-missing-override")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPERIMENTAL_CXX_MODULES ON)

## PROTO SECTION ##
find_package(Protobuf REQUIRED)

include_directories(${PROTOBUF_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS proto/example.proto)
## PROTO SECTION END ##
SET(APPLICATION_SOURCE_FILES
    util/logging.cc
    shapes/circle.cc
    shapes/square.cc
    proto/message_handler.cc
)

set(MODULE_SOURCES
    modules/math.ixx
)

set(APPLICATION_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}
)

add_library(application_lib SHARED ${APPLICATION_SOURCE_FILES} ${PROTO_SRCS} ${PROTO_HDRS} ${MODULE_SOURCES})

target_sources(application_lib
    PUBLIC FILE_SET my_modules TYPE CXX_MODULES
        BASE_DIRS modules
        FILES
            ${MODULE_SOURCES}
)

target_compile_features(application_lib PUBLIC cxx_std_20)
target_include_directories(application_lib PUBLIC ${APPLICATION_INCLUDE_DIRS})
target_link_libraries(application_lib ${PROTOBUF_LIBRARIES})

add_executable(application "main.cc")
target_link_libraries(application application_lib)

install(TARGETS application)
