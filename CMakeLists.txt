cmake_minimum_required(VERSION 3.16)

project(VideoCardControl VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Sql Widgets Charts)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Sql Widgets Charts)

qt_wrap_ui(UI_HEADERS interface/cardinfo.ui)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        interface/mainwindow.ui
)

# Додаємо .rc файл з іконкою тільки на Windows
if(WIN32)
    set(APP_ICON_RESOURCE_WINDOWS "${CMAKE_CURRENT_SOURCE_DIR}/app_manifest.rc")
endif()

if(QT_VERSION_MAJOR GREATER_EQUAL 6)
    qt_add_executable(VideoCardControl
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ${APP_ICON_RESOURCE_WINDOWS}
        src/cardinfo/cardinfo.h
        src/cardinfo/cardinfo.cpp
        src/cardinfo/interface/cardinfo.ui

        src/cardinfo/videocardcollector.h
        src/cardinfo/videocardcollector.cpp

        src/cardinfo/graphwindow.h
        src/cardinfo/graphwindow.cpp
        src/cardinfo/interface/graphwindow.ui

        src/cardsettings/cardmode.h
        src/cardsettings/cardmode.cpp
        src/cardsettings/interface/cardmode.ui

        src/cardsettings/linkingwindow.h
        src/cardsettings/linkingwindow.cpp
        src/cardsettings/interface/linkingwindow.ui

        src/cardsettings/profilemanager.h
        src/cardsettings/profilemanager.cpp
        src/cardsettings/interface/profilemanager.ui

        src/cardlogger/cardlogger.h
        src/cardlogger/cardlogger.cpp
        src/cardlogger/interface/cardlogger.ui

        src/database/databasecollector.h
        src/database/databasecollector.cpp

        src/infohelper/interfacehelper.h
        src/infohelper/interfacehelper.cpp
        src/infohelper/interface/interfacehelper.ui
        # Add additional sources here if needed








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
#target_sources(VideoCardControl PRIVATE app_manifest.rc)

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
