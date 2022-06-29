cmake_minimum_required(VERSION 3.14)

project(laowangqml VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Quick QuickControls2 Qml)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Quick QuickControls2 Qml)


set(PROJECT_SOURCES
    laowangqml_plugin.cpp
    MapControl.cpp
)

set(PROJECT_HEADERS
    laowangqml_plugin.h
    MapControl.h
)


add_library(${PROJECT_NAME}
    SHARED
    ${PROJECT_SOURCES} ${PROJECT_HEADERS}
)


target_link_libraries(${PROJECT_NAME}
    PRIVATE
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Quick
        Qt${QT_VERSION_MAJOR}::QuickControls2
        Qt${QT_VERSION_MAJOR}::Qml
)
