#include "../include/AIPlayer.h"
#include "../include/NormalRuleset.h"

AIPlayer::AIPlayer(char playerType) {
    this->playerType = playerType;
}

Checker::position AIPlayer::generatePosition(std::vector<Checker::position> &moves, Board &board) {

    // This AI player chooses moves based on the minimax algorithm.
    // Declare variables and determine the AI's color:
    Logic::Player playerType;
    Logic::Player opponentType;
    char opponentSymbol;

    if (this->playerType == 'X') {
        playerType = Logic::Black;
        opponentType = Logic::White;
        opponentSymbol = 'O';

    } else if (this->playerType == 'O') {
        playerType = Logic::White;
        opponentType = Logic::Black;
        opponentSymbol = 'X';
    }

    // Declare min & max variables for the opponent's score:
    int minimumOpponentScore = board.getSize() * board.getSize();
    int maxOpponentScore;
    Checker::position aiPosition;

    // Go over this AI player's moves:
    for (int i = 0; i < moves.size(); i++) {

        // For each move, make it over a mock board:
        maxOpponentScore = 0;
        Board *tempBoard = new Board(board.getSize());
        tempBoard->cloneBoard(&board);
        Logic *rules = new NormalRuleset(tempBoard);
        Checker::position moveToMake = moves.at(i);
        moveToMake.row++;
        moveToMake.col++;
        rules->makeMove(moveToMake, playerType);

        // Get the opponent's possible moves for this move:
        std::vector<Checker::position> &opponentMoves = rules->calcPossibleMoves(opponentType);

        // Go over them:
        for (int j = 0; j < opponentMoves.size(); j++) {

            // Make the move on a mock board:
            Board *opponentBoard = new Board(board.getSize());
            opponentBoard->cloneBoard(tempBoard);
            Logic *opponentRules = new NormalRuleset(opponentBoard);
            Checker::position opponentMoveToMake = opponentMoves.at(j);
            opponentMoveToMake.row++;
            opponentMoveToMake.col++;
            opponentRules->makeMove(opponentMoveToMake, opponentType);

            // Check the score for this move:
            int opponentScore = opponentRules->getBoardClass().countPlayersCheckers(opponentSymbol);
            if (opponentScore > maxOpponentScore) {
                maxOpponentScore = opponentScore;
            }
            delete opponentRules;
            delete opponentBoard;
        }
        if (maxOpponentScore < minimumOpponentScore) {
            minimumOpponentScore = maxOpponentScore;
            aiPosition.row = moves.at(i).row;
            aiPosition.col = moves.at(i).col;
        }
        delete rules;
        delete tempBoard;
    }

    // Return the best move for the AI:
    aiPosition.row++;
    aiPosition.col++;
    return aiPosition;
}

AIPlayer::~AIPlayer() {

}
