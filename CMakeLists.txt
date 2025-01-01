cmake_minimum_required(VERSION 3.16)

project(trollgo VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.15.2
)
FetchContent_MakeAvailable(googletest)

find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Gui)
find_package(Qt6 REQUIRED COMPONENTS Widgets)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

qt_add_executable(trollgo
    src/gamestate.cpp
    src/main.cpp
    src/mainwindow.cpp
    src/boardviewer.cpp
    src/sgf.cpp
    resources.qrc
)

target_link_libraries(trollgo PRIVATE Qt6::Widgets)

enable_testing()
add_executable(sgf_tests
    tests/sgf_tests.cpp
    src/gamestate.cpp
    src/sgf.cpp
)
target_include_directories(sgf_tests PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>)
target_compile_definitions(sgf_tests PUBLIC
    PROJECT_SOURCE_DIR="${PROJECT_SOURCE_DIR}")
target_link_libraries(sgf_tests GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(sgf_tests)
