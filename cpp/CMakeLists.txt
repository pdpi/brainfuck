cmake_minimum_required(VERSION 3.3)
project(Brainfuck)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -ggdb")

set(SOURCE_FILES src/main.cpp src/Interpreter.cpp src/Interpreter.h src/Memory.cpp src/Memory.h)
add_executable(Brainfuck ${SOURCE_FILES})