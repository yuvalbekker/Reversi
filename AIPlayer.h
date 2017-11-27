//
// Created by yuval on 27/11/17.
//

#ifndef REVERSE_AIPLAYER_H
#define REVERSE_AIPLAYER_H


#include "Player.h"

class AIPlayer : public Player {
public:


    /**
 * The constructor.
 * @param disk
 * @param PlayersType
*/
    AIPlayer(Disk *disk, Board::PlayersType type) : Player(disk,type){}

/**
     * The constructor.
    */
    AIPlayer();

    /**
     * The destructor.
    */
    virtual ~AIPlayer();

    /**
     * Generates and returns a game play.
     * @return GamePlay
    */
    virtual GamePlay generateGamePlay();

private:
    static Disk *disk;
    static Board::PlayersType type;
};


#endif //REVERSE_AIPLAYER_H
