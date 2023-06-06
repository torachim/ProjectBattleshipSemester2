cmake_minimum_required(VERSION 3.14)
project(Schiffeversenken)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-fsanitize=address)
add_link_options(-fsanitize=address)

include_directories(include)
#include_directories(external)

#find_package(pybind11 REQUIRED)

file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)
add_executable(demo1
    examples/demo.cpp
    ${SRC_FILES}
)

#pybind11_add_module(hangman
#    examples/demo_pybind.cpp
#    ${SRC_FILES}
#)

#install(TARGETS hangman
#   COMPONENT python
#   LIBRARY DESTINATION "${PROJECT_SOURCE_DIR}/extra")

#cmake -S . -B build && cmake --build build
# ./build/demo1
