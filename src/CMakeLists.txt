cmake_minimum_required(VERSION 3.6)
project(src)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

<<<<<<< HEAD
set(SOURCE_FILES Common/Board.cpp Common/Board.h Common/Router.cpp Common/Router.h NetworkFlow/NFRouter.cpp NetworkFlow/NFRouter.h Common/main.cpp Common/Solver.cpp Common/Solver.h AStar/AstarRouter.cpp AStar/AstarRouter.h Rule/RuleRouter.cpp)
add_executable(src ${SOURCE_FILES})
=======
set(SOURCE_FILES Common/Board.cpp Common/Board.h Common/Router.cpp Common/Router.h NetworkFlow/NFRouter.cpp NetworkFlow/NFRouter.h Common/main.cpp Common/Solver.cpp Common/Solver.h AStar/AstarRouter.cpp AStar/AstarRouter.h DivideConquer/Quarter.cpp DivideConquer/Quarter.h DivideConquer/DCRouter.cpp DivideConquer/DCRouter.h Common/Timer.cpp Common/Timer.h)
add_executable(src ${SOURCE_FILES})
>>>>>>> 4d44df13dbc0f2dd7da89c5f9b7415ec9c8c2252
