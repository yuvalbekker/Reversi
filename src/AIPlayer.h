//
// Created by yuval on 27/11/17.
//

#ifndef EX1_AIPLAYER_H
#define EX1_AIPLAYER_H


#include "Checker.h"
#include "IPlayer.h"

class AIPlayer : public IPlayer {
public:
    AIPlayer(char playerType);
    virtual ~AIPlayer();
    Checker::position generatePosition(std::vector<Checker::position> &moves, Logic &logic);

};


#endif //EX1_AIPLAYER_H
