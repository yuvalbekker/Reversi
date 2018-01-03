#ifndef REGULARPLAYER_H
#define REGULARPLAYER_H

#include "IPlayer.h"

// This class is in charge of a human player.
class RegularPlayer : public IPlayer {
public:
    RegularPlayer(char playerType);
    virtual ~RegularPlayer();
    Checker::position generatePosition(std::vector<Checker::position> &moves, Board &board);
};


#endif //REGULARPLAYER_H
