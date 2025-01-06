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

# Qt6 client
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Gui)
find_package(Qt6 REQUIRED COMPONENTS Widgets)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

qt_add_executable(steamgo
    src/client/main.cpp
    src/client/mainwindow.cpp
    src/client/boardviewer.cpp
    resources.qrc
)
target_link_libraries(steamgo PRIVATE Qt6::Widgets)
target_link_libraries(steamgo PRIVATE $<TARGET_OBJECTS:steamgo_common>)
target_include_directories(steamgo PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>)

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
