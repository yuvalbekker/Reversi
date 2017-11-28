//
// Created by yuval on 28/11/17.
//

#ifndef EX1_CONSOLEGUI_H
#define EX1_CONSOLEGUI_H


#include "IGui.h"

class ConsoleGui : public IGui {
public:
    ConsoleGui();

    virtual ~ConsoleGui();

    /**
    * Prints the Board.
    */
    virtual void printBoard(Board *b);

    virtual void printPossiblePlays(std::vector<Checker::position> &moves);

};


#endif //EX1_CONSOLEGUI_H
