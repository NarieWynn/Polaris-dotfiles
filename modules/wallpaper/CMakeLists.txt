cmake_minimum_required(VERSION 3.20)
project(polaris_wallpaper LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick)
find_package(LayerShellQt REQUIRED)

qt_add_executable(polaris_wallpaper
        src/main.cpp
        src/wallpapermanager.h
        src/wallpapermanager.cpp
        src/wallpaperdaemon.h
        src/wallpaperdaemon.cpp
)

qt_add_qml_module(polaris_wallpaper
        URI Polaris.Wallpaper
        VERSION 1.0
        QML_FILES qml/main.qml
)

target_link_libraries(polaris_wallpaper PRIVATE
        polaris_shared
        Qt6::Core
        Qt6::Gui
        Qt6::Qml
        Qt6::Quick
        LayerShellQt::Interface
)