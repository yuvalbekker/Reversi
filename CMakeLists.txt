cmake_minimum_required(VERSION 3.8)
project(Reverse)

set(CMAKE_CXX_STANDARD 98)

set(SOURCE_FILES main.cpp Board.cpp Board.h Player.cpp Player.h Disk.cpp Disk.h GamePlay.cpp GamePlay.h GameResult.cpp GameResult.h RowOccupationContainer.cpp RowOccupationContainer.h IGui.cpp IGui.h GeneralGameOperator.cpp GeneralGameOperator.h ConsoleGameOperator.cpp ConsoleGameOperator.h IRuleEnricher.cpp IRuleEnricher.h StandardRuleEnricher.cpp StandardRuleEnricher.h AIPlayer.cpp AIPlayer.h)
add_executable(Reverse ${SOURCE_FILES})