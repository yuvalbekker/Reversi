//
// Created by yuval on 27/11/17.
//

#include "AIPlayer.h"


AIPlayer::AIPlayer(char playerType) {
    this->playerType = playerType;
}


Checker::position AIPlayer::generatePosition(std::vector<Checker::position> &moves,Logic &logic) {
    return Checker::position();
}

AIPlayer::~AIPlayer() {

}
