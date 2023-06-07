cmake_minimum_required(VERSION 3.14)
project(Schiffeversenken)
set(CMAKE_CXX_STANDARD 17)

include_directories(include)
#include_directories(external)

find_package(pybind11 REQUIRED)


#für pybind11
#add_subdirectory(pybind11)
<<<<<<< HEAD
#pybind11_add_module(schiffeversenken demopybind11.cpp)

=======
#pybind11_add_module(schiffeversenken demopybind.cpp)
>>>>>>> 2a4c753f8f4a4823e79fe9d225be34f731f3483f


add_compile_options(-fsanitize=address)
add_link_options(-fsanitize=address)

<<<<<<< HEAD

=======
include_directories(include)
include_directories(external)
>>>>>>> 2a4c753f8f4a4823e79fe9d225be34f731f3483f

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
<<<<<<< HEAD
    examples/demopybind11.cpp
=======
   examples/demopybind.cpp
>>>>>>> 2a4c753f8f4a4823e79fe9d225be34f731f3483f
    ${SRC_FILES}
)

install(TARGETS schiffeversenken
   COMPONENT python
   LIBRARY DESTINATION "${PROJECT_SOURCE_DIR}/extra")

#cmake -S . -B build && cmake --build build
# ./build/demo1
