cmake_minimum_required(VERSION 3.8)
project(Reversi)

set(CMAKE_CXX_STANDARD 98)

include_directories(src)
add_subdirectory(lib/googletest-release-1.8.0)
include_directories(lib/googletest-release-1.8.0/googletest/include)
include_directories(lib/googletest-release-1.8.0/googlemock/include)

set(SOURCE_FILES src/main.cpp src/Board.cpp include/Board.h src/Checker.cpp include/Checker.h src/Logic.cpp
        include/Logic.h src/Flow.cpp include/Flow.h src/NormalRuleset.cpp include/NormalRuleset.h src/IPlayer.cpp
        include/IPlayer.h src/RegularPlayer.cpp include/RegularPlayer.h src/AIPlayer.cpp include/AIPlayer.h src/IGui.cpp
        include/IGui.h src/ConsoleGui.cpp include/ConsoleGui.h src/GameResult.cpp include/GameResult.h)
add_executable(Reversi ${SOURCE_FILES} src/Board.cpp include/Board.h)

set(TEST_FILES tests/NormalRulesetTest.cpp tests/include/NormalRulesetTest.h tests/LogicFlipTest.cpp tests/include/LogicFlipTest.h)
add_executable(tests include/Board.h src/Board.cpp src/Checker.cpp include/Checker.h src/Flow.cpp include/Flow.h src/GameResult.cpp include/GameResult.h
        src/Logic.cpp include/Logic.h src/NormalRuleset.cpp include/NormalRuleset.h ${TEST_FILES} tests/main.cpp)
target_link_libraries(tests gtest gtest_main pthread)
