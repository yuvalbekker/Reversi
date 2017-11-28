// Name: Eyal Lantzman ID: 205502818

#ifndef FLOW_H
#define FLOW_H

#include "Logic.h"
#include "IPlayer.h"
#include "IGui.h"

class Flow {
public:

//Constructor:

    /**
    * A constructor for flow. It gets a reference to a Logic instance.
    */
    Flow(Logic &l, IGui &gui, IPlayer *first, IPlayer *second);


// Members:

private:
    Logic &logic;
    IGui &gui;
    bool blackMovesEnded;
    bool whiteMovesEnded;
    IPlayer *first;
    IPlayer *second;
    IPlayer *currentPlayer;

// Functions:

private:

    /**
    * This function returns the # of playerType
    * checkers on the board.
    */
    int countPlayersCheckers(char playerType) const;

    bool isGameOver();

    void switchPlayers();

public:

    /**
    * This function runs the game flow.
    */
    void play();
};


#endif //EX1_FLOW_H
