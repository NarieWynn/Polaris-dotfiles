cmake_minimum_required(VERSION 3.20)
project(polaris_shared LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core DBus)

add_library(polaris_shared STATIC
        network/wifi.cpp
        hardware/hardwareInterface.cpp
)

target_include_directories(polaris_shared PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)


target_link_libraries(polaris_shared PUBLIC
        Qt6::Core
        Qt6::DBus
)
