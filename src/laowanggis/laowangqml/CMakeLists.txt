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
find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBPQ REQUIRED  IMPORTED_TARGET libpq)

message(${LIBPQ_LIBRARIES})
message(${LIBPQ_INCLUDE_DIRS})

set(PROJECT_SOURCES
    src/laowangqml_plugin.cpp
    src/LWMapControl.cpp
    src/LWFile.cpp
    src/LWSQLConnection.cpp
)

set(PROJECT_HEADERS
    src/laowangqml_plugin.h
    src/LWMapControl.h
    src/LWFile.h
    src/LWSQLConnection.h
)



#set(PROJECT_OTHERS
#    cn/pcgis/qmldir
#)


FILE(GLOB QML_FILES "cn/pcgis/*.qml")
ADD_CUSTOM_TARGET(qml
    SOURCES ${QML_FILES} cn/pcgis/qmldir
)



add_custom_command(
    OUTPUT qml.output
    COMMAND echo "hello pre buid"
#    COMMAND rm -rf ${PROJECT_BINARY_DIR}/cn/pcgis
    COMMAND mkdir -p ${PROJECT_BINARY_DIR}/cn/pcgis
#    COMMAND cp -f ${PROJECT_BINARY_DIR}/${CMAKE_SHARED_LIBRARY_PREFIX}${PROJECT_NAME}${CMAKE_SHARED_LIBRARY_SUFFIX} ${PROJECT_BINARY_DIR}/cn/pcgis/
    COMMAND cp -rf ${PROJECT_SOURCE_DIR}/cn/pcgis/* ${PROJECT_BINARY_DIR}/cn/pcgis/
)


add_library(${PROJECT_NAME}
    SHARED
    ${PROJECT_SOURCES} ${PROJECT_HEADERS}
    qml.output
)

#include_directories(${PROJECT_NAME}
#        ${LIBPQ_INCLUDE_DIRS}
#)

#add_dependencies(${PROJECT_NAME} qml)
target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${LIBPQ_INCLUDE_DIRS}
)

target_link_directories(${PROJECT_NAME}
    PRIVATE
        ${LIBPQ_LIBRARY_DIRS}
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Quick
        Qt${QT_VERSION_MAJOR}::QuickControls2
        Qt${QT_VERSION_MAJOR}::Qml
        ${LIBPQ_LIBRARIES}
)







add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND echo "hello post buid"
#    COMMAND rm -rf ${PROJECT_BINARY_DIR}/cn/pcgis
    COMMAND mkdir -p ${PROJECT_BINARY_DIR}/cn/pcgis
    COMMAND cp -f ${PROJECT_BINARY_DIR}/${CMAKE_SHARED_LIBRARY_PREFIX}${PROJECT_NAME}${CMAKE_SHARED_LIBRARY_SUFFIX} ${PROJECT_BINARY_DIR}/cn/pcgis/
    COMMAND cp -rf ${PROJECT_SOURCE_DIR}/cn/pcgis/* ${PROJECT_BINARY_DIR}/cn/pcgis/
)



add_custom_command(
    TARGET qml
    POST_BUILD
#    COMMAND rm -rf ${PROJECT_BINARY_DIR}/cn/pcgis
    COMMAND mkdir -p ${PROJECT_BINARY_DIR}/cn/pcgis
    COMMAND cp -f ${PROJECT_BINARY_DIR}/${CMAKE_SHARED_LIBRARY_PREFIX}${PROJECT_NAME}${CMAKE_SHARED_LIBRARY_SUFFIX} ${PROJECT_BINARY_DIR}/cn/pcgis/
    COMMAND cp -rf ${PROJECT_SOURCE_DIR}/cn/pcgis/* ${PROJECT_BINARY_DIR}/cn/pcgis/
)
