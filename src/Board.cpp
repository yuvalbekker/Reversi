#include "../include/Board.h"

using namespace std;

Board::Board(int s) : size(s) {
    int i = 0, j = 0;

    // Initialize the board:
    board = new Checker *[s];
    for (int i = 0; i < size; i++) {
        board[i] = new Checker[size];
    }

    // Initial B&W positions:
    board[(getSize() / 2) - 1][(getSize() / 2) - 1].setO();
    board[getSize() / 2][getSize() / 2].setO();
    board[(getSize() / 2) - 1][getSize() / 2].setX();
    board[getSize() / 2][(getSize() / 2) - 1].setX();

    // Update the checkers' positions info:
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            board[i][j].setPosition(i, j);
        }
    }
};


Board::~Board() {

    // Free the checkers:
    for (int i = 0; i < size; i++) {
        delete[] board[i];
    }

    // Delete the actual matrix:
    delete[] board;
}


Checker **Board::getBoard() const {
    return board;
}

int Board::getSize() const {
    return size;
}

int Board::countPlayersCheckers(char playerType) {
    int count = 0;

    // Go over the board and get the score count:
    for (int i = 0; i < this->size; i++) {
        for (int j = 0; j < this->size; j++) {
            if (this->board[i][j].getVal() == playerType) {
                count++;
            }
        }
    }
    return count;
}

void Board::cloneBoard(Board *b) {

    // Clone this board by going over it and setting
    // the pieces:
    for (int i = 0; i < this->size; i++) {
        for (int j = 0; j < this->size; j++) {
            if (b->getBoard()[i][j].getVal() == 'X') {
                this->board[i][j].setX();
            } else if (b->getBoard()[i][j].getVal() == 'O') {
                this->board[i][j].setO();
            } else {
                this->board[i][j].setEmpty();
            }
        }
    }
}
