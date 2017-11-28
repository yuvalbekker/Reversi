#ifndef EX1_REGULARPLAYER_H
#define EX1_REGULARPLAYER_H


#include "IPlayer.h"

class RegularPlayer : public IPlayer {
public:
    RegularPlayer(char playerType);
    virtual ~RegularPlayer();
    Checker::position generatePosition(std::vector<Checker::position> &moves, Board &board);
};


#endif //EX1_REGULARPLAYER_H
