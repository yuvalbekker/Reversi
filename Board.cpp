//Name: Eyal Lantzman ID: 205502818

#include "Board.h"
#include <iostream>

using namespace std;

Board::Board(int s) : size(s) {
    int i = 0, j = 0;

    // Initialize the board:
    board = new Checker *[s];
    for (int i = 0; i < size; i++) {
        board[i] = new Checker[size];
    }

    // Initial B&W positions:
    board[(getSize()/2) - 1][(getSize()/2) - 1].setO();
    board[getSize()/2][getSize()/2].setO();
    board[(getSize()/2) - 1][getSize()/2].setX();
    board[getSize()/2][(getSize()/2) - 1].setX();

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

void Board::print() const {
    int i = 0, j = 0, q = 0;

    // Column # Indicators:
    cout << " |";
    for (i = 0; i < size; i++) {
        cout << " " << i + 1 << " |";
    }
    cout << endl;

    // Separator after this row:
    for (i = 0; i < (size * 4) + 2; i++) {
        cout << "-";
    }
    cout << endl;

    // Row # Indicators and board values:
    for (i = 0; i < size; i++) {
        cout << i + 1 << "|";
        for (j = 0; j < size; j++) {
            board[i][j].print();
        }
        cout << endl;

        // Separators between lines:
        for (q = 0; q < (size * 4) + 2; q++) {
            cout << "-";
        }
        cout << endl;
    }
}

Checker **Board::getBoard() const {
    return board;
}

int Board::getSize() const {
    return size;
}