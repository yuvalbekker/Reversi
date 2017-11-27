cmake_minimum_required(VERSION 3.8)
project(ex1)

set(CMAKE_CXX_STANDARD 98)

set(SOURCE_FILES main.cpp Board.cpp Board.h Checker.cpp Checker.h Logic.cpp Logic.h Flow.cpp Flow.h NormalRuleset.cpp NormalRuleset.h)
add_executable(ex1 ${SOURCE_FILES} Board.cpp Board.h)