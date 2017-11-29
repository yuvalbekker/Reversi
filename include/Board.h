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
     * @param s
     */
    Board(int s);

    /**
    * A d'tor for board.
    */
    ~Board();


//Functions:
    /**
     * This function clones the given board.
     */
    void cloneBoard(Board *b);

    /**
     * This function returns the # of playerType
     * checkers on the board.
     * @param playerType
     * @return int
     */
    int countPlayersCheckers(char playerType);

    /**
     * This is a getter for the board size.
     * @return int
     */
    int getSize() const;

    /**
     * This is a getter for the board matrix.
     * @return  Checker **
     */
    Checker **getBoard() const;
};


#endif