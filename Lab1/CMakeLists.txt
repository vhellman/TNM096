cmake_minimum_required(VERSION 3.7)
project(Lab1)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES State.cpp State.h PuzzleSolver.cpp PuzzleSolver.h runtime.cpp AStar.cpp AStar.h)
add_executable(Lab1 ${SOURCE_FILES})