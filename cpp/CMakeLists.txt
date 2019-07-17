cmake_minimum_required (VERSION 2.6)
project (SousVide)
set(CMAKE_BUILD_TYPE Release)

include_directories(inc)
add_subdirectory(pybind11)

file(GLOB SOURCES "src/*.cpp")

pybind11_add_module(SousVide ${SOURCES})
