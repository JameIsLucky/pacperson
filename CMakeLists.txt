cmake_minimum_required(VERSION 3.29.8)
project(pacperson)

set(CMAKE_CXX_STANDARD 23)

# SFML
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(pacperson main.cpp
        Spieler.cpp
        Spieler.h
        Punkt.cpp
        Punkt.h)

target_link_libraries(pacperson sfml-graphics sfml-window sfml-system)