#ifndef EX1_AIPLAYER_H
#define EX1_AIPLAYER_H


#include "Checker.h"
#include "IPlayer.h"

class AIPlayer : public IPlayer {
public:
    /**
     * The constructor.
     * @param playerType
     */
    AIPlayer(char playerType);


    virtual ~AIPlayer();

    Checker::position generatePosition(std::vector<Checker::position> &moves, Board &board);

};


#endif //EX1_AIPLAYER_H
