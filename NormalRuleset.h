// Name: Eyal Lantzman ID: 205502818

#ifndef NORMALRULESET_H
#define NORMALRULESET_H

#include "Logic.h"

class NormalRuleset : public Logic {

public:

    /**
    * A constructor the normal rules logic. It gets a pointer
    * to a board to work with.
    */
    NormalRuleset(Board *b);

    /**
    * This function checks the right direction of the given board
    * position for the given player and sees if there's a possible move.
    **/
    bool checkRight(Checker::position pos, Player player);

    /**
    * This function checks the down direction of the given board
    * position for the given player and sees if there's a possible move.
    **/
    bool checkDown(Checker::position pos, Player player);

    /**
    * This function checks the up direction of the given board
    * position for the given player and sees if there's a possible move.
    **/
    bool checkUp(Checker::position pos, Player player);

    /**
    * This function checks the left direction of the given board
    * position for the given player and sees if there's a possible move.
    **/
    bool checkLeft(Checker::position pos, Player player);

    /**
    * This function checks the up-left direction of the given board
    * position for the given player and sees if there's a possible move.
    **/
    bool checkUpLeft(Checker::position pos, Player player);

    /**
    * This function checks the up-right direction of the given board
    * position for the given player and sees if there's a possible move.
    **/
    bool checkUpRight(Checker::position pos, Player player);

    /**
    * This function checks the down-left direction of the given board
    * position for the given player and sees if there's a possible move.
    **/
    bool checkDownLeft(Checker::position pos, Player player);

    /**
    * This function checks the down-right direction of the given board
    * position for the given player and sees if there's a possible move.
    **/
    bool checkDownRight(Checker::position pos, Player player);

    /**
    * This function computes the possible moves for a player, stores
    * them by board position into a vector and returns it.
    **/
    std::vector<struct Checker::position> &calcPossibleMoves(Player player);
};


#endif //EX1_NORMALRULESET_H
