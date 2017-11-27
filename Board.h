//Name: Eyal Lantzman ID: 205502818

#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include "Checker.h"

// This class holds the board matrix and details about the board.
class Board {

//Members:

private:

    int size;
    Checker **board;


//Constructor & D'tor:

public:

    /**
    * A constructor for board.
    */
    Board(int s);

    /**
    * A d'tor for board.
    */
    ~Board();


//Functions:

    /**
    * This function prints the board matrix.
    */
    void print() const;

    /**
    * This is a getter for the board size.
    */
    int getSize() const;

    /**
    * This is a getter for the board matrix.
    */
    Checker **getBoard() const;
};


#endif