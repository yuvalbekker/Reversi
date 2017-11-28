// Name: Eyal Lantzman ID: 205502818

#include "Flow.h"

using namespace std;

Flow::Flow(Logic &l, IGui &gui, IPlayer *first, IPlayer *second) : logic(l), gui(gui) {
    blackMovesEnded = false;
    whiteMovesEnded = false;
    this->first = first;
    this->second = second;
    this->currentPlayer = first;
}

int Flow::countPlayersCheckers(char playerType) const {
    int count = 0;
    int i = 0;
    int j = 0;
    for (i = 0; i < logic.getBoardClass().getSize(); i++) {
        for (j = 0; j < logic.getBoardClass().getSize(); j++) {
            if (logic.getBoardClass().getBoard()[i][j].getVal() == playerType) {
                count++;
            }
        }
    }

    return count;
}

void Flow::play() {
    while (!isGameOver()) {
        // Print the board status:
        cout << "Current Board: " << endl;
        //logic.getBoardClass().print();

        this->gui.printBoard(&this->logic.getBoardClass());

        // Get possible moves:
        Logic::Player playerType = Logic::Black;
        if (this->currentPlayer->playerType == 'X') {
            playerType = Logic::Black;
        } else if (this->currentPlayer->playerType == 'O') {
            playerType = Logic::White;
        }
        vector<Checker::position> &moves = logic.calcPossibleMoves(playerType);
        cout << "Player " << this->currentPlayer->playerType << " It's your turn." << endl;
        cout << "Your " << moves.size() << " possible moves: ";

        // If there are no possible moves, mark it and return:
        if (moves.empty()) {
            cout << "You have no possible moves. Play goes to the "
                    "other player." << endl;
        } else {
            // If there are moves, print them out:
            /*for (int i = 0; i < moves.size(); i++) {
                cout << "(" << moves[i].row + 1
                     << "," << moves[i].col + 1 << ")" << " ";
            }*/
            this->gui.printPossiblePlays(moves);
            Checker::position pos = this->currentPlayer->generatePosition(moves, this->logic);
            // Make the move:
            if (this->currentPlayer->playerType == 'X') {
                logic.makeMove(pos, Logic::Black);
            } else {
                logic.makeMove(pos, Logic::White);
            }
        }
        switchPlayers();

    }
}

bool Flow::isGameOver() {
    // If the board is full or there are no more moves:
    if (countPlayersCheckers('O') + countPlayersCheckers('X') ==
        (logic.getBoardClass().getSize() * logic.getBoardClass().getSize())
        || (whiteMovesEnded && blackMovesEnded)) {
        if (countPlayersCheckers('X') > countPlayersCheckers('O')) {
            cout << "Black wins! Good game." << endl;
            return true;
        }

        if (countPlayersCheckers('X') < countPlayersCheckers('O')) {
            cout << "White wins! Good game." << endl;
            return true;
        }

        if (countPlayersCheckers('O') == countPlayersCheckers('X')) {
            cout << "It's a tie! Good game." << endl;
            return true;
        }
    }
    return false;
}

void Flow::switchPlayers() {
    if (this->currentPlayer->playerType == this->first->playerType) {
        this->currentPlayer = this->second;
    } else if (this->currentPlayer->playerType == this->second->playerType) {
        this->currentPlayer = this->first;
    }

}


