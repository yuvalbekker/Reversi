#ifndef EX1_IGUI_H
#define EX1_IGUI_H


#include <vector>
#include "Board.h"
#include "GameResult.h"
#include "IPlayer.h"

class IGui {
public:
    /**
    * The destructor.
    */
    virtual ~IGui();

    /**
     * Prints the Board.
     * @param b
     */
    virtual void printBoard(Board *b);

    /**
     * Print the input moves of the input player.
     * @param moves
     * @param player
     */
    virtual void printPossiblePlays(std::vector<Checker::position> &moves, IPlayer *player);

    /**
     * Print the result of the game.
     * @param result
     */
    virtual void printGameResult(GameResult result);

    /**
     * Scan a player type from the user.
     * @return IPlayer
     */
    virtual IPlayer *scanPlayerType();

    /**
     * Print the score of input players.
     * @param blackPlayerScore
     * @param whitePlayerScore
     */
    virtual void printScore(int blackPlayerScore, int whitePlayerScore);

    /**
     * Print the input move.
     * @param move
     */
    virtual void printChosenPlay(Checker::position move);


};


#endif //EX1_IGUI_H
