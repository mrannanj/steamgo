cmake_minimum_required(VERSION 3.16)

project(trollgo VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Core)

qt_add_executable(trollgo
    main.cpp
)

target_link_libraries(trollgo PRIVATE Qt6::Widgets)
