cmake_minimum_required(VERSION 3.14)
project(Schiffeversenken)
set(CMAKE_CXX_STANDARD 17)

include_directories(include)
#include_directories(external)

find_package(pybind11 REQUIRED)


#für pybind11
#add_subdirectory(pybind11)
#pybind11_add_module(schiffeversenken demopybind11.cpp)



add_compile_options(-fsanitize=address)
add_link_options(-fsanitize=address)


find_package(pybind11 REQUIRED)

file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)
add_executable(demo1
    examples/demo.cpp
    ${SRC_FILES}
)



include(FetchContent)
if (CMAKE_VERSION VERSION_GREATER_EQUAL "3.24.0")
    cmake_policy(SET CMP0135 NEW)
endif()

FetchContent_Declare(
    googletest 
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)
include(GoogleTest)

enable_testing()

add_executable(test1 test/test1.cpp)
target_link_libraries(test1 GTest::gtest_main)
gtest_discover_tests(test1)

pybind11_add_module(schiffeversenken
   examples/demopybind.cpp
    ${SRC_FILES}
)

install(TARGETS schiffeversenken
   COMPONENT python
   LIBRARY DESTINATION "${PROJECT_SOURCE_DIR}/extra")

#cmake -S . -B build && cmake --build build
# ./build/demo1
