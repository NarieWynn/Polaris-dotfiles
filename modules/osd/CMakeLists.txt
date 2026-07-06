cmake_minimum_required(VERSION 3.20)
project(polaris_osd LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick)

find_package(LayerShellQt REQUIRED)

qt_add_executable(polaris_osd
        src/main.cpp
)

qt_add_qml_module(polaris_osd
        URI Polaris.OSD
        VERSION 1.0
        QML_FILES qml/main.qml
)

target_link_libraries(polaris_osd PRIVATE
        polaris_shared
        Qt6::Core
        Qt6::Gui
        Qt6::Qml
        Qt6::Quick
        LayerShellQt::Interface
)