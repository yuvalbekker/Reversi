#ifndef FLOW_H
#define FLOW_H

#include "Logic.h"
#include "IPlayer.h"
#include "IGui.h"
#include "GameResult.h"

class Flow {
public:

//Constructor:

    /**
     * A constructor for flow. It gets a reference to a Logic instance.
     * @param l
     * @param gui
     * @param first
     * @param second
     */
    Flow(Logic &l, IGui &gui, IPlayer *first, IPlayer *second);


// Members:

private:
    Logic &logic;
    IGui &gui;
    IPlayer *first;
    IPlayer *second;
    IPlayer *currentPlayer;

// Functions:

private:

    /**
     * Return true is the game is over, otherwise false.
     * @return bool
     */
    bool isGameOver();

    /**
     * Switch the current player turn.
     */
    void switchPlayerTurn();
    /**
     * Calculate the result of the game.
     * @return GameResult
     */
    GameResult calculateGameResult();

public:

    /**
     * This function runs the game flow.
     * @return GameResult
     */
    GameResult play();
};


#endif //EX1_FLOW_H
