//Yuval Bekker
//311254585

#ifndef REVERSE_GENERALGAMEOPERATOR_H
#define REVERSE_GENERALGAMEOPERATOR_H


#include <string>
#include <map>
#include "IGui.h"
#include "GameResult.h"
#include "Player.h"
#include "IRuleEnricher.h"

class GeneralGameOperator : public IGui {
public:
    /**
    * Begin the game play flow.
     * @param ruleEnricher
     * @return GameResult
    */
    GameResult play(IRuleEnricher ruleEnricher);

protected:
    Board *board;
    Player *firstPlayer;
    Player *secondPlayer;
    map<Board::PlayersType, Disk *> mapOfSymbols;
    Player *currentPlayerTurn;
    bool endGame;

    /**
    * Parses the input gamePlay to a string.
     * @param play
     * @return string
    */
    string parseGamePlayToString(GamePlay play);

    /**
    * Initializes the game.
     * @param rows
     * @param columns
    */
    void initializeGame(int rows, int columns);

    /**
    * Returns true if the game is over, otherwise false.
     * @return bool
    */
    bool isGameOver();

    /**
    * Returns true if the input game play is valid, otherwise false.
     * @param play
     * @param plays
     * @return bool
    */
    bool isValidGamePlay(GamePlay play, vector<RowOccupationContainer> *plays);

    /**
    * Switches the current player turn.
    */
    void switchTurn();
    /**
    * Calculate the result of the game.
     * @return GameResult
    */
    GameResult calculateGameResult();

};


#endif //REVERSE_GENERALGAMEOPERATOR_H
