cmake_minimum_required(VERSION 3.6)
project(assignment1b)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    CMakeLists.txt
    README.md
    Item.h
    MapOfItemsTest.cpp)

add_executable(assignment1b ${SOURCE_FILES})