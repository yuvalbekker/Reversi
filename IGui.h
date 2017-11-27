//Yuval Bekker
//311254585

#ifndef REVERSE_IGUI_H
#define REVERSE_IGUI_H


#include "RowOccupationContainer.h"

class IGui {
public:
    /**
    * The destructor.
    */
    virtual ~IGui() {};

    /**
    * Prints the Board.
    */
    virtual void printBoard() = 0;
    /**
    * Prints the input possible plays.
    */
    virtual void showPossiblePlays(vector<RowOccupationContainer> *plays) = 0;
};


#endif //REVERSE_IGUI_H
