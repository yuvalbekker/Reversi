#ifndef IGUI_H
#define IGUI_H

#include <vector>
#include "Board.h"
#include "GameResult.h"
#include "IPlayer.h"

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

    virtual void printPossiblePlays(std::vector<Checker::position> &moves, IPlayer *player);

    virtual void printGameResult(GameResult result);

    virtual int scanPlayerType();

    virtual void printScore(int blackPlayerScore, int whitePlayerScore);

    virtual void printChosenPlay(Checker::position move);


};


#endif //IGUI_H