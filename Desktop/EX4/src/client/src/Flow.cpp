#include "../include/Flow.h"
#include "../include/LocalOnlinePlayer.h"
#include "../include/RemoteOnlinePlayer.h"

using namespace std;

Flow::Flow(Logic &l, IGui &gui, IPlayer *first, IPlayer *second) : logic(l), gui(gui) {
    this->first = first;
    this->second = second;
    if (this->first->playerType == 'X') {
        this->currentPlayer = first;
        this->opponent = second;
    }
    if (this->second->playerType == 'X') {
        this->currentPlayer = second;
        this->opponent = first;
    }
}

GameResult Flow::playOnline() {

    // Run this code while the game is not over:
    while (!isGameOver()) {

        // Print the board:
        this->gui.printBoard(&this->logic.getBoardClass());
        int whiteScore = logic.getBoardClass().countPlayersCheckers('O');
        int blackScore = logic.getBoardClass().countPlayersCheckers('X');
        this->gui.printScore(blackScore, whiteScore);

        // If it's this player's turn:
        if (this->currentPlayer == this->first) {

            // Get the possible moves for the player:
            Logic::Player playerType = Logic::Black;
            if (this->currentPlayer->playerType == 'X') {
                playerType = Logic::Black;
            } else if (this->currentPlayer->playerType == 'O') {
                playerType = Logic::White;
            }
            vector<Checker::position> &moves = logic.calcPossibleMoves(playerType);

            //Print the moves:
            this->gui.printPossiblePlays(moves, this->currentPlayer);

            // If the current player has possible moves:
            if (!moves.empty()) {
                Checker::position generatedPosition = this->currentPlayer->generatePosition(moves, this->logic.getBoardClass());
                this->gui.printChosenPlay(generatedPosition);

                // Make the move:
                if (this->currentPlayer->playerType == 'X') {
                    logic.makeMove(generatedPosition, Logic::Black);
                } else {
                    logic.makeMove(generatedPosition, Logic::White);
                }
            }
        }

            // If it's the other player's turn:
        else {
            cout << "Waiting for remote player to make his move..." << endl;
            RemoteOnlinePlayer* onlineOpponent = (RemoteOnlinePlayer*) this->opponent;
            Checker::position pos;
            onlineOpponent->generatePosition(pos);
            //cout << "I got the move: " << pos.row << ", " << pos.col << endl;
            break;
            //logic.makeMove(pos, this->opponent->playerType);
        }

        //switchPlayerTurn();
    }

    //Print the final board.
    this->gui.printBoard(&this->logic.getBoardClass());
    return calculateGameResult();
}

























GameResult Flow::play() {

    // Run this code while the game is not over:
    while (!isGameOver()) {

        //Print the board:
        this->gui.printBoard(&this->logic.getBoardClass());
        int whiteScore = logic.getBoardClass().countPlayersCheckers('O');
        int blackScore = logic.getBoardClass().countPlayersCheckers('X');
        this->gui.printScore(blackScore, whiteScore);

        // Get the possible moves for the player:
        Logic::Player playerType = Logic::Black;
        if (this->currentPlayer->playerType == 'X') {
            playerType = Logic::Black;
        } else if (this->currentPlayer->playerType == 'O') {
            playerType = Logic::White;
        }
        vector<Checker::position> &moves = logic.calcPossibleMoves(playerType);

        //Print the moves:
        this->gui.printPossiblePlays(moves, this->currentPlayer);

        // If the current player has possible moves:
        if (!moves.empty()) {
            Checker::position generatedPosition = this->currentPlayer->generatePosition(moves, this->logic.getBoardClass());
            this->gui.printChosenPlay(generatedPosition);

            // Make the move:
            if (this->currentPlayer->playerType == 'X') {
                logic.makeMove(generatedPosition, Logic::Black);
            } else {
                logic.makeMove(generatedPosition, Logic::White);
            }
        }
        switchPlayerTurn();
    }

    //Print the final board.
    this->gui.printBoard(&this->logic.getBoardClass());
    return calculateGameResult();
}

bool Flow::isGameOver() {

    // If there are no more possible moves for both players, end the game:
    if (this->logic.calcPossibleMoves(Logic::Black).size() == 0
        && this->logic.calcPossibleMoves(Logic::White).size() == 0) {
        return true;
    }

    // If the board is full, end it as well:
    int blackScore = this->logic.getBoardClass().countPlayersCheckers('X');
    int whiteScore = this->logic.getBoardClass().countPlayersCheckers('O');
    int boardSize = this->logic.getBoardClass().getSize() * this->logic.getBoardClass().getSize();
    return ((whiteScore + blackScore) == boardSize);
}

void Flow::switchPlayerTurn() {

    // Change turn according to the current turn:
    if (this->currentPlayer->playerType == this->first->playerType) {
        this->currentPlayer = this->second;
    } else if (this->currentPlayer->playerType == this->second->playerType) {
        this->currentPlayer = this->first;
    }
}

GameResult Flow::calculateGameResult() {

    // Count the player's pieces:
    int whiteScore = logic.getBoardClass().countPlayersCheckers('O');
    int blackScore = logic.getBoardClass().countPlayersCheckers('X');

    // Return the result based on the count:
    if (blackScore > whiteScore) {
        return GameResult(GameResult::Black, blackScore);
    }
    if (blackScore < whiteScore) {
        return GameResult(GameResult::White, whiteScore);
    }
    if (whiteScore == blackScore) {
        return GameResult(GameResult::None, whiteScore);
    }
}