cmake_minimum_required(VERSION 3.6)
project(src)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES Common/Board.cpp Common/Board.h Common/Router.cpp Common/Router.h NetworkFlow/NFRouter.cpp NetworkFlow/NFRouter.h Common/main.cpp Common/Solver.cpp Common/Solver.h AStar/AstarRouter.cpp AStar/AstarRouter.h)
add_executable(src ${SOURCE_FILES})