cmake_minimum_required(VERSION 3.14)

project(laowangqml VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Quick QuickControls2 Qml)
find_package(QT NAMES Qt6 REQUIRED COMPONENTS Core Quick QuickControls2 Qml)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Quick QuickControls2 Qml)


set(PROJECT_SOURCES
    src/laowangqml_plugin.cpp
    src/LWMapControl.cpp
)

set(PROJECT_HEADERS
    src/laowangqml_plugin.h
    src/LWMapControl.h
)


set(PROJECT_OTHERS
    qmldir
)


FILE(GLOB QML_FILES "qml/*.qml")
ADD_CUSTOM_TARGET(qml SOURCES ${QML_FILES})


add_library(${PROJECT_NAME}
    SHARED
    ${PROJECT_SOURCES} ${PROJECT_HEADERS} ${PROJECT_OTHERS}
)



target_link_libraries(${PROJECT_NAME}
    PRIVATE
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Quick
        Qt${QT_VERSION_MAJOR}::QuickControls2
        Qt${QT_VERSION_MAJOR}::Qml
)



add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND rm -rf ${PROJECT_BINARY_DIR}/cn/pcgis
    COMMAND mkdir -p ${PROJECT_BINARY_DIR}/cn/pcgis
    COMMAND cp -f ${PROJECT_BINARY_DIR}/${CMAKE_SHARED_LIBRARY_PREFIX}${PROJECT_NAME}${CMAKE_SHARED_LIBRARY_SUFFIX} ${PROJECT_BINARY_DIR}/cn/pcgis/
    COMMAND cp -f ${PROJECT_SOURCE_DIR}/qmldir ${PROJECT_BINARY_DIR}/cn/pcgis/
    COMMAND cp -f ${PROJECT_SOURCE_DIR}/qml/*.qml ${PROJECT_BINARY_DIR}/cn/pcgis/
)

