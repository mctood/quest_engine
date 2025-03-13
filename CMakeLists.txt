cmake_minimum_required(VERSION 3.30)
project(untitled)

set(CMAKE_CXX_STANDARD 20)

add_executable(untitled main.cpp
        struct/Box.h
        struct/Button.h
        struct/State.h
        States/helpers.cpp
        helpers/buttonhelpers.cpp
        States/buttons.cpp
        States/states.cpp
        utils/color.cpp)
