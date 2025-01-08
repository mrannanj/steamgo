cmake_minimum_required(VERSION 3.16)

project(steamgo VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Common library
add_library(steamgo_common OBJECT
    src/common/gamestate.cpp
    src/common/sgf.cpp)
target_include_directories(steamgo_common PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>)

# gRPC and Protobuf
find_package(Protobuf REQUIRED)
find_package(gRPC REQUIRED)
find_package(Threads)

set(PROTO_FILES
    protos/go_service.proto
)
add_library(steamgo_proto OBJECT ${PROTO_FILES})
target_link_libraries(steamgo_proto PRIVATE
    protobuf::libprotobuf
    gRPC::grpc
    gRPC::grpc++
)
target_include_directories(steamgo_proto PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
get_target_property(grpc_cpp_plugin_location gRPC::grpc_cpp_plugin LOCATION)
protobuf_generate(TARGET steamgo_proto LANGUAGE cpp)
protobuf_generate(TARGET steamgo_proto LANGUAGE grpc
    GENERATE_EXTENSIONS .grpc.pb.h .grpc.pb.cc
    PLUGIN "protoc-gen-grpc=${grpc_cpp_plugin_location}"
)

# Qt6 client
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Gui)
find_package(Qt6 REQUIRED COMPONENTS Widgets)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

qt_add_executable(steamgo
    src/client/appstate.cpp
    src/client/main.cpp
    src/client/mainwindow.cpp
    src/client/boardviewer.cpp
    src/client/go_service_client.cpp
    resources.qrc
)
target_link_libraries(steamgo PRIVATE Qt6::Widgets)
target_link_libraries(steamgo PRIVATE $<TARGET_OBJECTS:steamgo_common>)
target_include_directories(steamgo PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>)

target_include_directories(steamgo PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(steamgo PRIVATE
    protobuf::libprotobuf
    gRPC::grpc
    gRPC::grpc++
)
target_link_libraries(steamgo PRIVATE $<TARGET_OBJECTS:steamgo_proto>)

# Server
add_executable(steamgo_server
    src/server/main.cpp
    src/server/go_service.cpp
)
target_include_directories(steamgo_server PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>)
target_link_libraries(steamgo_server PRIVATE $<TARGET_OBJECTS:steamgo_common>)

target_include_directories(steamgo_server PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(steamgo_server PRIVATE
    protobuf::libprotobuf
    gRPC::grpc
    gRPC::grpc++
)
target_link_libraries(steamgo_server PRIVATE $<TARGET_OBJECTS:steamgo_proto>)

# Tests
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.15.2
)
FetchContent_MakeAvailable(googletest)

enable_testing()
add_executable(sgf_tests
    tests/sgf_tests.cpp
)
target_include_directories(sgf_tests PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>)
target_compile_definitions(sgf_tests PRIVATE
    PROJECT_SOURCE_DIR="${PROJECT_SOURCE_DIR}")
target_link_libraries(sgf_tests PRIVATE $<TARGET_OBJECTS:steamgo_common>)
target_link_libraries(sgf_tests PRIVATE GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(sgf_tests)
