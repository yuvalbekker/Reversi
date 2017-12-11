//Yuval Bekker
//311254585

#include <iostream>
#include "ConsoleGameOperator.h"

ConsoleGameOperator::ConsoleGameOperator(Player *first, Player *second, int rows, int columns) {
    this->firstPlayer = first;
    this->secondPlayer = second;
    initializeGame(rows, columns);
}

ConsoleGameOperator::~ConsoleGameOperator() {
    delete this->board;
}

void ConsoleGameOperator::showPossiblePlays(vector<RowOccupationContainer> *plays) {
    cout << this->currentPlayerTurn->playersDisk()->symbol << ": It's your move.\n";
    if (plays->size() == 0) {
        cout << "Your possible moves. Play passes back tho the other player\n";
    } else {
        cout << "Your possible moves:";
        for (int i = 0; i < plays->size(); i++) {
            if (i != 0) {
                cout << ",";
            }
            string move = parseGamePlayToString(plays->at(i).getOccupaiedCell());
            cout << move;
        }
        cout << "\n\n";
    }
}

void ConsoleGameOperator::printBoard() {
    int rowsCounter = 1;
    int columnsCounter = 1;
    for (int i = 0; i < this->board->columns; i++) {
        cout << " | " << columnsCounter;
        columnsCounter++;
    }

    char blackSymbol = this->mapOfSymbols.find(Board::Black)->second->symbol;
    char whiteSymbol = this->mapOfSymbols.find(Board::White)->second->symbol;
    char noneSymbol = ' ';

    cout << " |";
    cout << "\n";
    cout << "--";
    for (int i = 0; i < this->board->columns; i++) {
        cout << "----";
    }
    cout << "\n";
    for (int i = 0; i < this->board->rows; i++) {
        cout << rowsCounter;
        for (int j = 0; j < this->board->columns; j++) {
            switch (this->board->getBoardCellContent(i, j)) {
                case Board::Black:
                    cout << "| " << blackSymbol << " ";
                    break;
                case Board::White:
                    cout << "| " << whiteSymbol << " ";
                    break;
                case Board::None:
                    cout << "| " << noneSymbol << " ";
                    break;
                default:
                    break;
            }
        }
        cout << "|\n";
        for (int i = 0; i < this->board->columns; i++) {
            cout << "----";
        }
        cout << "--";
        cout << "\n";
        rowsCounter++;
    }
    cout << "X: " << this->board->getNumberOfDisks(Board::Black) << ", O: "
         << this->board->getNumberOfDisks(Board::White) << "\n";
}
