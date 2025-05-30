cmake_minimum_required(VERSION 3.16)

project(VideoCardControl VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Sql Widgets Charts)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Sql Widgets Charts)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(VideoCardControl
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        cardinfo.h cardinfo.cpp cardinfo.ui
        videocardcollector.h videocardcollector.cpp
        graphwindow.h graphwindow.cpp graphwindow.ui
        cardmode.h cardmode.cpp cardmode.ui
        cardlogger.h cardlogger.cpp cardlogger.ui
        databasecollector.h databasecollector.cpp
        linkingwindow.h linkingwindow.cpp linkingwindow.ui
        profilemanager.h profilemanager.cpp profilemanager.ui
        interfacehelper.h interfacehelper.cpp interfacehelper.ui









    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET VideoCardControl APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(VideoCardControl SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(VideoCardControl
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(VideoCardControl PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Charts Qt${QT_VERSION_MAJOR}::Sql)

# Додати шлях до заголовків -- HERE
target_include_directories(VideoCardControl PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/external/nvapi/include)

target_sources(VideoCardControl PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/external/nvapi/source/NvApiDriverSettings.c
)
target_sources(VideoCardControl PRIVATE app_manifest.rc)

target_link_libraries(VideoCardControl PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/external/nvapi/libs/nvapi64.lib)
# -- HERE


# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.VideoCardControl)
endif()
set_target_properties(VideoCardControl PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS VideoCardControl
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(VideoCardControl)
endif()
