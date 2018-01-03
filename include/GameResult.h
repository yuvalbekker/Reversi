#ifndef GAMERESULT_H
#define GAMERESULT_H

// This class holds the result of the game.
class GameResult {

public:

// Definitions:
    enum ResultType {
        White, Black, None
    };

// C'tor:
    /**
    * A constructor for GameResult
     * @param player
     * @param score
    */
    GameResult(ResultType resultType, int score);

// Functions:
    /**
    * This is a getter for the game's result.
    * @return ResultType
    */
    ResultType getResult();

    /**
    * This function returns the currect score of the game.
    * @return an int.
    */
    int getScore();

// Members:

private:
    ResultType resultType;
    int score;
};


#endif //GAMERESULT_H
