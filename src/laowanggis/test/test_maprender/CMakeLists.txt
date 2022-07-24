cmake_minimum_required(VERSION 3.14)

project(test_maprender VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#find_package(PkgConfig REQUIRED)
#pkg_check_modules(Gdal REQUIRED  IMPORTED_TARGET gdal)
find_package(GDAL CONFIG REQUIRED)
find_package(GEOS CONFIG REQUIRED)

#find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Sql)
find_package(QT NAMES Qt6 REQUIRED COMPONENTS Core Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Sql)

set(PROJECT_SOURCES
    test_maprender.cpp
)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})
target_link_libraries(${PROJECT_NAME} PUBLIC laowangrender)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Sql)
target_link_libraries(${PROJECT_NAME} PRIVATE GDAL::GDAL)
target_link_libraries(${PROJECT_NAME} PRIVATE GEOS::geos)
