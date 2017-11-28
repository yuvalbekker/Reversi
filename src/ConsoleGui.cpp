//
// Created by yuval on 28/11/17.
//

#include <iostream>
#include "ConsoleGui.h"
#include "Board.h"

using namespace std;

ConsoleGui::ConsoleGui() {

}

ConsoleGui::~ConsoleGui() {

}

void ConsoleGui::printBoard(Board *b) {
    int i = 0, j = 0, q = 0;

    // Column # Indicators:
    cout << " |";
    for (i = 0; i < b->getSize(); i++) {
        cout << " " << i + 1 << " |";
    }
    cout << endl;

    // Separator after this row:
    for (i = 0; i < (b->getSize() * 4) + 2; i++) {
        cout << "-";
    }
    cout << endl;

    // Row # Indicators and board values:
    for (i = 0; i < b->getSize(); i++) {
        cout << i + 1 << "|";
        for (j = 0; j < b->getSize(); j++) {
            b->getBoard()[i][j].print();
        }
        cout << endl;

        // Separators between lines:
        for (q = 0; q < (b->getSize() * 4) + 2; q++) {
            cout << "-";
        }
        cout << endl;
    }
}

void ConsoleGui::printPossiblePlays(std::vector<Checker::position> &moves) {
    for (int i = 0; i < moves.size(); i++) {
        cout << "(" << moves[i].row + 1
             << "," << moves[i].col + 1 << ")" << " ";
    }
}
