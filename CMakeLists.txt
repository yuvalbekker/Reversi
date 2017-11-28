cmake_minimum_required(VERSION 3.8)
project(Reversi)

set(CMAKE_CXX_STANDARD 98)

include_directories(src)
add_subdirectory(lib/googletest-release-1.8.0)
include_directories(lib/googletest-release-1.8.0/googletest/include)
include_directories(lib/googletest-release-1.8.0/googlemock/include)

set(SOURCE_FILES src/main.cpp src/Board.cpp src/Board.h src/Checker.cpp src/Checker.h src/Logic.cpp
        src/Logic.h src/Flow.cpp src/Flow.h src/NormalRuleset.cpp src/NormalRuleset.h src/IPlayer.cpp
        src/IPlayer.h src/RegularPlayer.cpp src/RegularPlayer.h src/AIPlayer.cpp src/AIPlayer.h src/IGui.cpp
        src/IGui.h src/ConsoleGui.cpp src/ConsoleGui.h)
add_executable(Reversi ${SOURCE_FILES} src/Board.cpp src/Board.h)

set(TEST_FILES tests/NormalRulesetTest.cpp tests/include/NormalRulesetTest.h)
add_executable(tests src/Board.h src/Board.cpp src/Checker.cpp src/Checker.h src/Flow.cpp src/Flow.h
        src/Logic.cpp src/Logic.h src/NormalRuleset.cpp src/NormalRuleset.h ${TEST_FILES} tests/main.cpp tests/include/NormalRulesetTest.h)
target_link_libraries(tests gtest gtest_main pthread)
