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

    virtual void printPossiblePlays(std::vector<Checker::position> &moves, IPlayer *player);

    virtual void printGameResult(GameResult result);

    virtual IPlayer *scanPlayerType();

    virtual void printScore(int blackPlayerScore, int whitePlayerScore);

    virtual void printChosenPlay(Checker::position move);

};


#endif //EX1_CONSOLEGUI_H
