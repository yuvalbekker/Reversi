//
// Created by yuval on 27/11/17.
//

#ifndef EX1_IPLAYER_H
#define EX1_IPLAYER_H


#include <vector>
#include "Checker.h"
#include "Logic.h"

class IPlayer {
public:
    virtual Checker::position generatePosition(std::vector<Checker::position> &moves, Logic &logic);
    virtual ~IPlayer();
    char playerType;
};


#endif //EX1_IPLAYER_H
