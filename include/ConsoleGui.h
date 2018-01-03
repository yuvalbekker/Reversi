#ifndef CONSOLEGUI_H
#define CONSOLEGUI_H

#include "IGui.h"

class ConsoleGui : public IGui {
public:
    ConsoleGui();

    virtual ~ConsoleGui();

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


#endif //CONSOLEGUI_H