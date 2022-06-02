cmake_minimum_required(VERSION 3.22)
project(Ex3)

set(CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_FLAGS  -lpthread)

include_directories(.)

add_executable(Ex3
        main.cpp Buffer.h Producer.h Dispatcher.h CoEditor.h ScreenManager.h)
