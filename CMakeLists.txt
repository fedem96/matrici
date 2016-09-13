cmake_minimum_required(VERSION 3.5)
project(matrici)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_subdirectory(test)

set(SOURCE_FILES main.cpp Matrix.h Row.h Column.h)
add_executable(matrici ${SOURCE_FILES})

add_library(mytest ${SOURCE_FILES})
target_link_libraries(matrici mytest)