//
// Created by yuval on 28/11/17.
//

#ifndef EX1_IGUI_H
#define EX1_IGUI_H


#include <vector>
#include "Board.h"

class IGui {
public:
    /**
    * The destructor.
    */
    virtual ~IGui();

    /**
    * Prints the Board.
    */
    virtual void printBoard(Board *b);

    virtual void printPossiblePlays(std::vector<Checker::position> &moves);

};


#endif //EX1_IGUI_H
