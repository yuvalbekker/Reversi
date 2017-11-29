#ifndef AIPLAYER_H
#define AIPLAYER_H


#include "Checker.h"
#include "IPlayer.h"

// This class defines the AI player.
class AIPlayer : public IPlayer {

//Functions:
public:
    /**
     * The constructor.
     * @param playerType
     */
    AIPlayer(char playerType);

    /**
     * This is a virtual d'tor to prevent polymorphism issues.
     */
    virtual ~AIPlayer();

    /**
    * This function gets a possible moves vector and a board, and decides
    * which move to choose using the minimax algorithm.
    * @param playerType
    */
    Checker::position generatePosition(std::vector<Checker::position> &moves, Board &board);

};


#endif //AIPLAYER_H
