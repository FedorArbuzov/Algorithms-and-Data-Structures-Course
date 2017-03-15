cmake_minimum_required(VERSION 3.6)
project(CarService)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp car.cpp car.h)
add_executable(CarService ${SOURCE_FILES})