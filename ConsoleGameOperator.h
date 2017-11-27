//Yuval Bekker
//311254585

#ifndef REVERSE_CONSOLEGAMEOPERATOR_H
#define REVERSE_CONSOLEGAMEOPERATOR_H


#include "GeneralGameOperator.h"

class ConsoleGameOperator : public GeneralGameOperator {
public:

    /**
    * The constructor.
    */
    ConsoleGameOperator(Player *first, Player *second, int rows, int columns);

    /**
    * The destructor.
    */
    virtual ~ConsoleGameOperator();

    /**
    * Prints the input vector of game plays.
     * @param plays vector<RowOccupationContainer> object
    */
    virtual void showPossiblePlays(vector<RowOccupationContainer> *plays);

    /**
    * Prints the Board.
    */
    virtual void printBoard();
};


#endif //REVERSE_CONSOLEGAMEOPERATOR_H
