#include <sstream>
#include "../include/OnlineFlow.h"
#include "../include/LocalOnlinePlayer.h"
#include "../include/RemoteOnlinePlayer.h"

using namespace std;

OnlineFlow::OnlineFlow(Logic &l, IGui &gui, LocalOnlinePlayer *first, RemoteOnlinePlayer *second) : logic(l), gui(gui) {

    // Set the current player and the opponent player by their symbol:
    this->first = first;
    this->second = second;
    if (this->first->playerType == 'X') {
        this->currentPlayer = first;
        this->opponent = second;
    } else {
        this->currentPlayer = second;
        this->opponent = first;
    }
    this->isGameClosed = false;
}

GameResult OnlineFlow::play() {

    // Run this code while the game is not over:
    while (!isGameOver() && !this->isGameClosed) {
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

            if (moves.empty()) {
                try {
                    LocalOnlinePlayer *lop = (LocalOnlinePlayer *) currentPlayer;

                    // Inform the server there are no possible moves for this turn:
                    lop->getClient()->sendPosition(-1, ' ', -1);
                    switchPlayerTurn();
                    continue;
                }

                catch (const char *msg) {
                    cout << "Failed to send chosen position to server. Reason:" << msg << endl;
                }
            }

            // If the current player has possible moves:
            if (!moves.empty()) {
                Checker::position generatedPosition = this->currentPlayer->generatePosition(moves,
                                                                                            this->logic.getBoardClass());
                //Check if 'close' command entered
                if (generatedPosition.row == -3 && generatedPosition.col == -3) {
                    cout << "Sending 'close' command to the server..." << endl;
                } else {
                    this->gui.printChosenPlay(generatedPosition);

                    // Make the move:
                    if (this->currentPlayer->playerType == 'X') {
                        logic.makeMove(generatedPosition, Logic::Black);
                    }
                    if (this->currentPlayer->playerType == 'O') {
                        logic.makeMove(generatedPosition, Logic::White);
                    }
                }
                try {
                    LocalOnlinePlayer *lop = (LocalOnlinePlayer *) currentPlayer;
                    int result = lop->getClient()->sendPosition(generatedPosition.row, ' ', generatedPosition.col);
                    //check if the 'close' command entered
                    if (result == 2) {
                        this->isGameClosed = true;
                    }
                }

                catch (const char *msg) {
                    cout << "Failed to send chosen position to server. Reason:" << msg << endl;
                }

            }
        }

        // If it's the other player's turn:
        if (this->currentPlayer == this->second) {

            cout << "Waiting for remote player to make his move..." << endl;
            Checker::position pos;

            // Read a move from the server:
            second->generatePosition(pos);
            //Check if the game is closed
            if (pos.row == -4 && pos.col == -4) {
                cout << "Closing the game" << endl;
                this->isGameClosed = true;
            } else {
                // If there are no moves for the other player:
                if (pos.row == -1 && pos.col == -1) {
                    switchPlayerTurn();
                    continue;
                }

                // Make the move that was read:
                if (this->opponent->playerType == 'O') {
                    logic.makeMove(pos, Logic::Black);
                } else if (this->opponent->playerType == 'X') {
                    logic.makeMove(pos, Logic::White);
                }
            }
        }
        if (!this->isGameClosed) {
            switchPlayerTurn();
        }
    }

    if (!this->isGameClosed) {
        // Inform the server the game has ended:
        try {
            LocalOnlinePlayer *lop = (LocalOnlinePlayer *) currentPlayer;
            lop->getClient()->sendPosition(0, ' ', 0);
        }

        catch (const char *msg) {
            cout << "Failed to send endgame message to server. Reason:" << msg << endl;
        }

        // Print the final board.
        this->gui.printBoard(&this->logic.getBoardClass());
        return calculateGameResult();
    } else {
        return GameResult(GameResult::None, 0);
    }
}


bool OnlineFlow::isGameOver() {

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

void OnlineFlow::switchPlayerTurn() {

    // Change turn according to the current turn:
    if (this->currentPlayer == this->first) {
        this->currentPlayer = this->second;
        this->opponent = this->first;
    } else if (this->currentPlayer == this->second) {
        this->currentPlayer = this->first;
        this->opponent = this->second;
    }
}

GameResult OnlineFlow::calculateGameResult() {

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

