#ifndef IPLAYER_H
#define IPLAYER_H


#include <vector>
#include "Checker.h"
#include "Logic.h"

// This class is in charge of a player.
class IPlayer {

public:

// D'tor:
    /**
     * A virtual d'tor to prevent polymorphism issues.
     */
    virtual ~IPlayer();

// Functions:
    /**
     * This function gets a possible moves vector and a board, and decides
     * which move to choose based on user input or an AI algorithm.
     * @param moves
     * @param board
     * @return position
     */
    virtual Checker::position generatePosition(std::vector<Checker::position> &moves, Board &board);

// Memebers:
    char playerType;
};


#endif //IPLAYER_H
