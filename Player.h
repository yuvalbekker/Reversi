//Yuval Bekker
//311254585

#ifndef REVERSE_PLAYER_H
#define REVERSE_PLAYER_H


#include "Disk.h"
#include "Board.h"

class Player {
public:
    /**
     * The constructor.
     * @param disk
     * @param PlayersType
    */
    Player(Disk *disk, Board::PlayersType type);

    /**
     * The constructor.
    */
    Player();

    /**
     * The destructor.
    */
    virtual ~Player();

    /**
     * Returns the disk.
     * @return Disk
    */
    Disk *playersDisk();

    /**
     * Returns the type of the player.
     * @return PlayersType
    */
    Board::PlayersType getPlayerType();

    /**
     * Generates and returns a game play.
     * @return GamePlay
    */
    virtual GamePlay generateGamePlay();

private:
    Disk *disk;
    Board::PlayersType type;
};

#endif //REVERSE_PLAYER_H
