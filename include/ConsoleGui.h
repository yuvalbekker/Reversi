#ifndef CONSOLEGUI_H
#define CONSOLEGUI_H


#include "IGui.h"

// This class is responsible for the game's interface in console mode.
// (functions' comments appear on interface IGui.h).
class ConsoleGui : public IGui {
public:

    /**
    * A c'tor for a ConsoleGui.
    */
    ConsoleGui();

    /**
    * A virtual d'tor to prevent polymorphism issues.
    */
    virtual ~ConsoleGui();

    virtual void printBoard(Board *b);

    virtual void printPossiblePlays(std::vector<Checker::position> &moves, IPlayer *player);

    virtual void printGameResult(GameResult result);

    virtual IPlayer *scanPlayerType();

    virtual void printScore(int blackPlayerScore, int whitePlayerScore);

    virtual void printChosenPlay(Checker::position move);

};


#endif //CONSOLEGUI_H
