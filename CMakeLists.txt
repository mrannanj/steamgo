cmake_minimum_required(VERSION 3.16)

project(trollgo VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Gui)
find_package(Qt6 REQUIRED COMPONENTS Widgets)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

qt_add_executable(trollgo
    main.cpp
    mainwindow.cpp
    boardviewer.cpp
    resources.qrc
)

target_link_libraries(trollgo PRIVATE Qt6::Widgets)
