//
// Created by yuval on 27/11/17.
//

#ifndef EX1_REGULARPLAYER_H
#define EX1_REGULARPLAYER_H


#include "IPlayer.h"

class RegularPlayer : public IPlayer {
public:
    RegularPlayer(char playerType);
    virtual ~RegularPlayer();
    Checker::position generatePosition(std::vector<Checker::position> &moves, Logic &logic);
};


#endif //EX1_REGULARPLAYER_H
