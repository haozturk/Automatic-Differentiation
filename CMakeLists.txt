cmake_minimum_required(VERSION 2.8.12.2)
project(sourceCode)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp function.cpp function.h graph.cpp graph.h variable.cpp variable.h)
add_executable(project4 ${SOURCE_FILES})