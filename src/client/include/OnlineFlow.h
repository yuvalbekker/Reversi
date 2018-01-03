#ifndef ONLINEFLOW_H
#define ONLINEFLOW_H

#include "Logic.h"
#include "IPlayer.h"
#include "IGui.h"
#include "GameResult.h"
#include "LocalOnlinePlayer.h"
#include "RemoteOnlinePlayer.h"

class OnlineFlow {

//Constructor:
public:

    /**
    * A constructor for OnlineFlow. It gets two online players.
    */
    OnlineFlow(Logic &l, IGui &gui, LocalOnlinePlayer *first, RemoteOnlinePlayer *second);


// Members:
private:

    Logic &logic;
    IGui &gui;
    LocalOnlinePlayer *first;
    RemoteOnlinePlayer *second;
    IPlayer *currentPlayer;
    IPlayer *opponent;
    bool isGameClosed;

// Functions:
private:

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
};


#endif //ONLINEFLOW_H