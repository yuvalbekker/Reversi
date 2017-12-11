//Yuval Bekker
//311254585

#ifndef REVERSE_GAMERESULT_H
#define REVERSE_GAMERESULT_H


#include "Board.h"

class GameResult {
public:
    /**
    * The constructor.
    */
    GameResult();

    /**
    * The constructor.
     * @param type
     * @param score
    */
    GameResult(Board::PlayersType type, int score);

    /**
    * Returns the score.
     * @return int
    */
    int getScore();
    /**
    * Returns the type.
     * @return PlayersType
    */
    Board::PlayersType getType();

private:
    Board::PlayersType type;
    int score;

};


#endif //REVERSE_GAMERESULT_H
