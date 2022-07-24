cmake_minimum_required(VERSION 3.14)

project(laowangmap VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND LAOWANG_QML_IMPORT_PATH ${PROJECT_BINARY_DIR}/../laowangqml)
set(QML_IMPORT_PATH "${LAOWANG_QML_IMPORT_PATH}" CACHE STRING "Laowang qml import paths")

#find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Quick)
find_package(QT NAMES Qt6 REQUIRED COMPONENTS Core Quick)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Quick)

set(PROJECT_SOURCES
        main.cpp
        qml.qrc
        laowangmap.sh
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(laowangmap
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET laowangmap APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(laowangmap SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(laowangmap
          ${PROJECT_SOURCES}
        )
    endif()
endif()

target_compile_definitions(laowangmap
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(laowangmap
  PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick)

set_target_properties(laowangmap PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER laowang.pcgis.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_import_qml_plugins(laowangmap)
    qt_finalize_executable(laowangmap)
endif()


add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND cp -f ${PROJECT_SOURCE_DIR}/laowangmap.sh ${PROJECT_BINARY_DIR}/
)

