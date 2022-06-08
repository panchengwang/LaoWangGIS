cmake_minimum_required(VERSION 3.14)

project(laowangrender VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(PkgConfig REQUIRED)
pkg_check_modules(Cairo REQUIRED  IMPORTED_TARGET cairo)
pkg_check_modules(Geos REQUIRED  IMPORTED_TARGET geos)


find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Quick)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Quick)

include_directories(
    ${Cairo_INCLUDE_DIRS}
    ${Geos_INCLUDE_DIRS}
)

set(PROJECT_SOURCES
    LWMapRender.cpp
)

set(PROJECT_HEADERS
    LWMapRender.h
)

add_library(${PROJECT_NAME} SHARED ${PROJECT_SOURCES} ${PROJECT_HEADERS})
target_link_libraries(${PROJECT_NAME} PUBLIC PkgConfig::Cairo)
target_link_libraries(${PROJECT_NAME} PUBLIC PkgConfig::Geos -lgeos)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Core)
