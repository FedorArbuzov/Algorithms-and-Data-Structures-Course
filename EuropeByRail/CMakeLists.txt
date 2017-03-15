cmake_minimum_required(VERSION 3.6)
project(EuropeByRail)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp City.h Service.h RailSystem.h RailSystem.cpp)
add_executable(EuropeByRail ${SOURCE_FILES})