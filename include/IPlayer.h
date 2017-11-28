#ifndef EX1_IPLAYER_H
#define EX1_IPLAYER_H


#include <vector>
#include "Checker.h"
#include "Logic.h"

class IPlayer {
public:
    /**
     * Generates a game play position according to the player strategy.
     * @param moves
     * @param board
     * @return position
     */
    virtual Checker::position generatePosition(std::vector<Checker::position> &moves, Board &board);

    /**
     * The destructor.
     */
    virtual ~IPlayer();

    char playerType;
};


#endif //EX1_IPLAYER_H
