cmake_minimum_required(VERSION 3.5)

project(CS205_Proj)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)
include_directories(src)
include_directories(C:/Qt/6.6.1/mingw_64/include/QtWidgets)

aux_source_directory(./src PROJECT_SOURCES)
aux_source_directory(./include PROJECT_INCLUDES)

add_executable(CS205_Proj main.cpp ${PROJECT_SOURCES}
        src/move.cpp
        include/move.hpp)


#project(CS205_Proj VERSION 0.1 LANGUAGES CXX)
#
#set(CMAKE_AUTOUIC ON)
#set(CMAKE_AUTOMOC ON)
#set(CMAKE_AUTORCC ON)
#
#set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_PREFIX_PATH "C:/Qt/6.6.1/mingw_64")
#
#include_directories(include)
#include_directories(src)
#include_directories(C:/Qt/6.6.1/mingw_64/include/QtWidgets)
#
#find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
#find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
#
#set(PROJECT_SOURCES
#        main.cpp
#        mainwindow.cpp
#        mainwindow.h
#        mainwindow.ui
#        src/unit.cpp
#        src/player.cpp
#        src/box.cpp
#        src/map.cpp
#        src/level.cpp
#)
#
#
#if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
#    qt_add_executable(CS205_Proj
#        MANUAL_FINALIZATION
#        ${PROJECT_SOURCES}
#        README.md
#    )
#    message("Qt version is greater than 6:" ${QT_VERSION_MAJOR})
## Define target properties for Android with Qt 6 as:
##    set_property(TARGET CS205_Proj APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
##                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
## For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
#else()
#    if(ANDROID)
#        add_library(CS205_Proj SHARED
#            ${PROJECT_SOURCES}
#        )
## Define properties for Android with Qt 5 after find_package() calls as:
##    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    else()
#        add_executable(CS205_Proj
#            ${PROJECT_SOURCES}
#        )
#    endif()
#endif()
#
#target_compile_options(qt_cmake PUBLIC "/Zc:__cplusplus")
#target_link_libraries(CS205_Proj PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
#
## Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
## If you are developing for iOS or macOS you should consider setting an
## explicit, fixed bundle identifier manually though.
#if(${QT_VERSION} VERSION_LESS 6.1.0)
#  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.CS205_Proj)
#endif()
#set_target_properties(CS205_Proj PROPERTIES
#    ${BUNDLE_ID_OPTION}
#    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
#    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
#    MACOSX_BUNDLE TRUE
#    WIN32_EXECUTABLE TRUE
#)
#
#include(GNUInstallDirs)
#install(TARGETS CS205_Proj
#    BUNDLE DESTINATION .
#    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
#)
#
#if(QT_VERSION_MAJOR EQUAL 6)
#    qt_finalize_executable(CS205_Proj)
#endif()
