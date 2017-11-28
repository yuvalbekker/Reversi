#ifndef LOGIC_H
#define LOGIC_H

#include <iostream>
#include <vector>
#include <string>
#include "Board.h"

class Logic {

// Constructor:

public:

    /**
     * This c'tor for Logic gets a pointer to a Board instance.
     * @param b
     */
    Logic(Board *b);

    /**
     * This is virtual d'tor to prevent polymorphism issues.
     */
    virtual ~Logic();

// Definitions & Members:

public:

    enum Player {
        White, Black
    };

protected:

    Player p;
    Board *boardClass;
    std::vector<struct Checker::position> moves;

// Functions:

public:

    /**
     * This functions returns a reference to a Board instance.
     * @return  Board &
     */
    Board &getBoardClass() const;

    /**
     * This function computes the possible moves for a player, stores
     * them by board position into a vector and returns it.
     * @param player
     * @return vector<struct Checker::position>
     */
    virtual std::vector<struct Checker::position> &calcPossibleMoves(Player player) = 0;

    /**
     * This function makes a move for the given player based
     * on the given board position.
     * @param pos
     * @param player
     */
    void makeMove(struct Checker::position pos, Player player);

protected:

    /**
     * This function checks the right direction of the given board
     * position for the given player and sees if there's a possible move.
     * @param pos
     * @param player
     * @return bool
     */
    virtual bool checkRight(Checker::position pos, Player player) = 0;

    /**
     * This function checks the down direction of the given board
     * position for the given player and sees if there's a possible move.
     * @param pos
     * @param player
     * @return bool
     */
    virtual bool checkDown(Checker::position pos, Player player) = 0;

    /**
     * This function checks the up direction of the given board
     * position for the given player and sees if there's a possible move.
     * @param pos
     * @param player
     * @return bool
     */
    virtual bool checkUp(Checker::position pos, Player player) = 0;

    /**
     * This function checks the left direction of the given board
     * position for the given player and sees if there's a possible move.
     * @param pos
     * @param player
     * @return bool
     */
    virtual bool checkLeft(Checker::position pos, Player player) = 0;

    /**
     * This function checks the up-left direction of the given board
     * position for the given player and sees if there's a possible move.
     * @param pos
     * @param player
     * @return bool
     */
    virtual bool checkUpLeft(Checker::position pos, Player player) = 0;

    /**
    * This function checks the up-right direction of the given board
    * position for the given player and sees if there's a possible move.
    **/
    virtual bool checkUpRight(Checker::position pos, Player player) = 0;

    /**
     * This function checks the down-left direction of the given board
     * position for the given player and sees if there's a possible move.
     * @param pos
     * @param player
     * @return bool
     */
    virtual bool checkDownLeft(Checker::position pos, Player player) = 0;

    /**
     * This function checks the down-right direction of the given board
     * position for the given player and sees if there's a possible move.
     * @param pos
     * @param player
     * @return bool
     */
    virtual bool checkDownRight(Checker::position pos, Player player) = 0;

    /**
     * This function flips the right direction of the given board
     * position for the given player, if there are pieces to flip.
     * @param pos
     * @param player
     */
    void flipRight(Checker::position pos, Player player);

    /**
     * This function flips the down direction of the given board
     * position for the given player, if there are pieces to flip.
     * @param pos
     * @param player
     */
    void flipDown(Checker::position pos, Player player);

    /**
     * This function flips the up direction of the given board
     * position for the given player, if there are pieces to flip.
     * @param pos
     * @param player
     */
    void flipUp(Checker::position pos, Player player);

    /**
     * This function flips the left direction of the given board
     * position for the given player, if there are pieces to flip.
     * @param pos
     * @param player
     */
    void flipLeft(Checker::position pos, Player player);

    /**
     * This function flips the up-left direction of the given board
     * position for the given player, if there are pieces to flip.
     * @param pos
     * @param player
     */
    void flipUpLeft(Checker::position pos, Player player);

    /**
     * This function flips the up-right direction of the given board
     * position for the given player, if there are pieces to flip.
     * @param pos
     * @param player
     */
    void flipUpRight(Checker::position pos, Player player);

    /**
     * This function flips the down-left direction of the given board
     * position for the given player, if there are pieces to flip.
     * @param pos
     * @param player
     */
    void flipDownLeft(Checker::position pos, Player player);

    /**
     * This function flips the down-right direction of the given board
     * position for the given player, if there are pieces to flip.
     * @param pos
     * @param player
     */
    void flipDownRight(Checker::position pos, Player player);
};


#endif //EX1_LOGIC_H
