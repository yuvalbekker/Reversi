#ifndef FLOW_H
#define FLOW_H

#include "Logic.h"
#include "IPlayer.h"
#include "IGui.h"
#include "GameResult.h"

class Flow {

//Constructor:
public:

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
    IPlayer *opponent;

// Functions:
protected:

    /**
     * This function true if the game is over, otherwise false.
     * @return bool
     */
    bool isGameOver();

    /**
     * This function switches the current player's turn.
     */
    void switchPlayerTurn();

    /**
     * This function determines the result of the game.
     * @return GameResult
     */
    GameResult calculateGameResult();

public:

    /**
     * This function runs the game flow.
     * @return GameResult
     */
    GameResult play();

    /**
    * This function runs the online game flow.
    * @return GameResult
    */
    GameResult playOnline();
};


#endif //FLOW_H