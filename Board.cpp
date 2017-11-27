//Yuval Bekker
//311254585

#include <clocale>
#include "Board.h"

Board::Board(int numberOfRows, int numberOfColumns) {
    this->rows = numberOfRows;
    this->columns = numberOfColumns;
    this->boardMatrix = new PlayersType *[this->rows];
    for (int i = 0; i < rows; i++) {
        this->boardMatrix[i] = new PlayersType[columns];
    }
    initializeBoard();
}

void Board::initializeBoard() {

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            this->boardMatrix[i][j] = None;
        }
    }
    this->boardMatrix[3][3] = White;
    this->boardMatrix[4][4] = White;
    this->boardMatrix[4][3] = Black;
    this->boardMatrix[3][4] = Black;
    this->whitePlayerPositions = new vector<GamePlay>;
    this->blackPlayerPositions = new vector<GamePlay>;
    this->whitePlayerPositions->push_back(GamePlay(3, 3));
    this->whitePlayerPositions->push_back(GamePlay(4, 4));
    this->blackPlayerPositions->push_back(GamePlay(3, 4));
    this->blackPlayerPositions->push_back(GamePlay(4, 3));

}

Board::PlayersType Board::getBoardCellContent(int rowNumber, int columnNumber) {
    return this->boardMatrix[rowNumber][columnNumber];
}


Board::~Board() {
    for (int i = 0; i < rows; i++) {
        delete[] this->boardMatrix[i];
    }
    delete[] this->boardMatrix;
    delete this->blackPlayerPositions;
    delete this->whitePlayerPositions;
}

vector<RowOccupationContainer> *Board::getStandardPossibleGamePlays(Board::PlayersType type) {
    vector<RowOccupationContainer> *gamePlays = new vector<RowOccupationContainer>;
    vector<GamePlay> *opponentPositions;
    if (type == White) {
        opponentPositions = this->blackPlayerPositions;
    } else {
        opponentPositions = this->whitePlayerPositions;
    }

    for (int i = 0; i < opponentPositions->size(); i++) {
        GamePlay opponentPosition = opponentPositions->at(i);

        //top left side
        GamePlay checkPosition(opponentPosition.row() - 1, opponentPosition.column() - 1);
        if (!isOutOfBounds(checkPosition)) {
            vector<GamePlay> *rowsToOccupy = new vector<GamePlay>;
            //check if the position is not occupied.
            if (this->boardMatrix[checkPosition.row()][checkPosition.column()] == None) {
                int rowIndex = 1;
                int columnIndex = 1;
                bool endRowSearch = false;
                GamePlay searchRowPosition(opponentPosition.row() + rowIndex, opponentPosition.column() + columnIndex);
                while (!isOutOfBounds(searchRowPosition) && !endRowSearch) {
                    if (this->boardMatrix[searchRowPosition.row()][searchRowPosition.column()] == type) {
                        RowOccupationContainer container(GamePlay(checkPosition.row(), checkPosition.column()));
                        for (int i = 0; i < rowsToOccupy->size(); i++) {
                            container.addCellToOccupy(rowsToOccupy->at(i));
                        }
                        container.addCellToOccupy(opponentPosition);
                        bool hasDuplicate = false;
                        for (int i = 0; i < gamePlays->size(); i++) {
                            if (gamePlays->at(i).getOccupaiedCell() == container.getOccupaiedCell()) {
                                hasDuplicate = true;
                                for (int j = 0; j < container.getCells()->size(); j++) {
                                    gamePlays->at(i).addCellToOccupy(container.getCells()->at(j));
                                }
                            }
                        }
                        if (!hasDuplicate) {
                            gamePlays->push_back(container);
                        }
                        endRowSearch = true;
                    } else if (this->boardMatrix[searchRowPosition.row()][searchRowPosition.column()] == None) {
                        endRowSearch = true;
                    } else {
                        rowsToOccupy->push_back(searchRowPosition);
                        searchRowPosition.setRow(searchRowPosition.row() + rowIndex);
                        searchRowPosition.setColumn(searchRowPosition.column() + columnIndex);
                    }
                }
            }
            delete rowsToOccupy;
        }

        //top up side
        checkPosition.setRow(opponentPosition.row() - 1);
        checkPosition.setColumn(opponentPosition.column());
        if (!isOutOfBounds(checkPosition)) {
            vector<GamePlay> *rowsToOccupy = new vector<GamePlay>;
            //check if the position is not occupied.
            if (this->boardMatrix[checkPosition.row()][checkPosition.column()] == None) {
                int rowIndex = 1;
                bool endRowSearch = false;
                GamePlay searchRowPosition(opponentPosition.row() + rowIndex, opponentPosition.column());
                while (!isOutOfBounds(searchRowPosition) && !endRowSearch) {
                    if (this->boardMatrix[searchRowPosition.row()][searchRowPosition.column()] == type) {
                        RowOccupationContainer container(GamePlay(checkPosition.row(), checkPosition.column()));
                        for (int i = 0; i < rowsToOccupy->size(); i++) {
                            container.addCellToOccupy(rowsToOccupy->at(i));
                        }
                        container.addCellToOccupy(opponentPosition);
                        bool hasDuplicate = false;
                        for (int i = 0; i < gamePlays->size(); i++) {
                            if (gamePlays->at(i).getOccupaiedCell() == container.getOccupaiedCell()) {
                                hasDuplicate = true;
                                for (int j = 0; j < container.getCells()->size(); j++) {
                                    gamePlays->at(i).addCellToOccupy(container.getCells()->at(j));
                                }
                            }
                        }
                        if (!hasDuplicate) {
                            gamePlays->push_back(container);
                        }
                        endRowSearch = true;
                    } else if (this->boardMatrix[searchRowPosition.row()][searchRowPosition.column()] == None) {
                        endRowSearch = true;
                    } else {
                        rowsToOccupy->push_back(searchRowPosition);
                        searchRowPosition.setRow(searchRowPosition.row() + rowIndex);
                    }
                }
            }
            delete rowsToOccupy;
        }

        //top right side
        checkPosition.setRow(opponentPosition.row() - 1);
        checkPosition.setColumn(opponentPosition.column() + 1);
        if (!isOutOfBounds(checkPosition)) {
            vector<GamePlay> *rowsToOccupy = new vector<GamePlay>;
            //check if the position is not occupied.
            if (this->boardMatrix[checkPosition.row()][checkPosition.column()] == None) {
                int rowIndex = 1;
                int columnIndex = -1;
                bool endRowSearch = false;
                GamePlay searchRowPosition(opponentPosition.row() + rowIndex, opponentPosition.column() + columnIndex);
                while (!isOutOfBounds(searchRowPosition) && !endRowSearch) {
                    if (this->boardMatrix[searchRowPosition.row()][searchRowPosition.column()] == type) {
                        RowOccupationContainer container(GamePlay(checkPosition.row(), checkPosition.column()));
                        for (int i = 0; i < rowsToOccupy->size(); i++) {
                            container.addCellToOccupy(rowsToOccupy->at(i));
                        }
                        container.addCellToOccupy(opponentPosition);
                        bool hasDuplicate = false;
                        for (int i = 0; i < gamePlays->size(); i++) {
                            if (gamePlays->at(i).getOccupaiedCell() == container.getOccupaiedCell()) {
                                hasDuplicate = true;
                                for (int j = 0; j < container.getCells()->size(); j++) {
                                    gamePlays->at(i).addCellToOccupy(container.getCells()->at(j));
                                }
                            }
                        }
                        if (!hasDuplicate) {
                            gamePlays->push_back(container);
                        }
                        endRowSearch = true;
                    } else if (this->boardMatrix[searchRowPosition.row()][searchRowPosition.column()] == None) {
                        endRowSearch = true;
                    } else {
                        rowsToOccupy->push_back(searchRowPosition);
                        searchRowPosition.setRow(searchRowPosition.row() + rowIndex);
                        searchRowPosition.setColumn(searchRowPosition.column() + columnIndex);
                    }
                }
            }
            delete rowsToOccupy;
        }

        //middle right side
        checkPosition.setRow(opponentPosition.row());
        checkPosition.setColumn(opponentPosition.column() + 1);
        if (!isOutOfBounds(checkPosition)) {
            vector<GamePlay> *rowsToOccupy = new vector<GamePlay>;
            //check if the position is not occupied.
            if (this->boardMatrix[checkPosition.row()][checkPosition.column()] == None) {
                int columnIndex = -1;
                bool endRowSearch = false;
                GamePlay searchRowPosition(opponentPosition.row(), opponentPosition.column() + columnIndex);
                while (!isOutOfBounds(searchRowPosition) && !endRowSearch) {
                    if (this->boardMatrix[searchRowPosition.row()][searchRowPosition.column()] == type) {
                        RowOccupationContainer container(GamePlay(checkPosition.row(), checkPosition.column()));
                        for (int i = 0; i < rowsToOccupy->size(); i++) {
                            container.addCellToOccupy(rowsToOccupy->at(i));
                        }
                        container.addCellToOccupy(opponentPosition);
                        bool hasDuplicate = false;
                        for (int i = 0; i < gamePlays->size(); i++) {
                            if (gamePlays->at(i).getOccupaiedCell() == container.getOccupaiedCell()) {
                                hasDuplicate = true;
                                for (int j = 0; j < container.getCells()->size(); j++) {
                                    gamePlays->at(i).addCellToOccupy(container.getCells()->at(j));
                                }
                            }
                        }
                        if (!hasDuplicate) {
                            gamePlays->push_back(container);
                        }
                        endRowSearch = true;
                    } else if (this->boardMatrix[searchRowPosition.row()][searchRowPosition.column()] == None) {
                        endRowSearch = true;
                    } else {
                        rowsToOccupy->push_back(searchRowPosition);
                        searchRowPosition.setColumn(searchRowPosition.column() + columnIndex);
                    }
                }
            }
            delete rowsToOccupy;
        }

        //bottom right side
        checkPosition.setRow(opponentPosition.row() + 1);
        checkPosition.setColumn(opponentPosition.column() + 1);
        if (!isOutOfBounds(checkPosition)) {
            vector<GamePlay> *rowsToOccupy = new vector<GamePlay>;
            //check if the position is not occupied.
            if (this->boardMatrix[checkPosition.row()][checkPosition.column()] == None) {
                int rowIndex = -1;
                int columnIndex = -1;
                bool endRowSearch = false;
                GamePlay searchRowPosition(opponentPosition.row() + rowIndex, opponentPosition.column() + columnIndex);
                while (!isOutOfBounds(searchRowPosition) && !endRowSearch) {
                    if (this->boardMatrix[searchRowPosition.row()][searchRowPosition.column()] == type) {
                        RowOccupationContainer container(GamePlay(checkPosition.row(), checkPosition.column()));
                        for (int i = 0; i < rowsToOccupy->size(); i++) {
                            container.addCellToOccupy(rowsToOccupy->at(i));
                        }
                        container.addCellToOccupy(opponentPosition);
                        bool hasDuplicate = false;
                        for (int i = 0; i < gamePlays->size(); i++) {
                            if (gamePlays->at(i).getOccupaiedCell() == container.getOccupaiedCell()) {
                                hasDuplicate = true;
                                for (int j = 0; j < container.getCells()->size(); j++) {
                                    gamePlays->at(i).addCellToOccupy(container.getCells()->at(j));
                                }
                            }
                        }
                        if (!hasDuplicate) {
                            gamePlays->push_back(container);
                        }
                        endRowSearch = true;
                    } else if (this->boardMatrix[searchRowPosition.row()][searchRowPosition.column()] == None) {
                        endRowSearch = true;
                    } else {
                        rowsToOccupy->push_back(searchRowPosition);
                        searchRowPosition.setRow(searchRowPosition.row() + rowIndex);
                        searchRowPosition.setColumn(searchRowPosition.column() + columnIndex);
                    }
                }
            }
            delete rowsToOccupy;
        }

        //bottom down side
        checkPosition.setRow(opponentPosition.row() + 1);
        checkPosition.setColumn(opponentPosition.column());
        if (!isOutOfBounds(checkPosition)) {
            vector<GamePlay> *rowsToOccupy = new vector<GamePlay>;
            //check if the position is not occupied.
            if (this->boardMatrix[checkPosition.row()][checkPosition.column()] == None) {
                int rowIndex = -1;
                bool endRowSearch = false;
                GamePlay searchRowPosition(opponentPosition.row() + rowIndex, opponentPosition.column());
                while (!isOutOfBounds(searchRowPosition) && !endRowSearch) {
                    if (this->boardMatrix[searchRowPosition.row()][searchRowPosition.column()] == type) {
                        RowOccupationContainer container(GamePlay(checkPosition.row(), checkPosition.column()));
                        for (int i = 0; i < rowsToOccupy->size(); i++) {
                            container.addCellToOccupy(rowsToOccupy->at(i));
                        }
                        container.addCellToOccupy(opponentPosition);
                        bool hasDuplicate = false;
                        for (int i = 0; i < gamePlays->size(); i++) {
                            if (gamePlays->at(i).getOccupaiedCell() == container.getOccupaiedCell()) {
                                hasDuplicate = true;
                                for (int j = 0; j < container.getCells()->size(); j++) {
                                    gamePlays->at(i).addCellToOccupy(container.getCells()->at(j));
                                }
                            }
                        }
                        if (!hasDuplicate) {
                            gamePlays->push_back(container);
                        }
                        endRowSearch = true;
                    } else if (this->boardMatrix[searchRowPosition.row()][searchRowPosition.column()] == None) {
                        endRowSearch = true;
                    } else {
                        rowsToOccupy->push_back(searchRowPosition);
                        searchRowPosition.setRow(searchRowPosition.row() + rowIndex);
                    }
                }
            }
            delete rowsToOccupy;
        }

        //bottom left side
        checkPosition.setRow(opponentPosition.row() + 1);
        checkPosition.setColumn(opponentPosition.column() - 1);
        if (!isOutOfBounds(checkPosition)) {
            vector<GamePlay> *rowsToOccupy = new vector<GamePlay>;
            //check if the position is not occupied.
            if (this->boardMatrix[checkPosition.row()][checkPosition.column()] == None) {
                int rowIndex = -1;
                int columnIndex = 1;
                bool endRowSearch = false;
                GamePlay searchRowPosition(opponentPosition.row() + rowIndex, opponentPosition.column() + columnIndex);
                while (!isOutOfBounds(searchRowPosition) && !endRowSearch) {
                    if (this->boardMatrix[searchRowPosition.row()][searchRowPosition.column()] == type) {
                        RowOccupationContainer container(GamePlay(checkPosition.row(), checkPosition.column()));
                        for (int i = 0; i < rowsToOccupy->size(); i++) {
                            container.addCellToOccupy(rowsToOccupy->at(i));
                        }
                        container.addCellToOccupy(opponentPosition);
                        bool hasDuplicate = false;
                        for (int i = 0; i < gamePlays->size(); i++) {
                            if (gamePlays->at(i).getOccupaiedCell() == container.getOccupaiedCell()) {
                                hasDuplicate = true;
                                for (int j = 0; j < container.getCells()->size(); j++) {
                                    gamePlays->at(i).addCellToOccupy(container.getCells()->at(j));
                                }
                            }
                        }
                        if (!hasDuplicate) {
                            gamePlays->push_back(container);
                        }
                        endRowSearch = true;
                    } else if (this->boardMatrix[searchRowPosition.row()][searchRowPosition.column()] == None) {
                        endRowSearch = true;
                    } else {
                        rowsToOccupy->push_back(searchRowPosition);
                        searchRowPosition.setRow(searchRowPosition.row() + rowIndex);
                        searchRowPosition.setColumn(searchRowPosition.column() + columnIndex);
                    }
                }
            }
            delete rowsToOccupy;
        }

        //middle left side
        checkPosition.setRow(opponentPosition.row());
        checkPosition.setColumn(opponentPosition.column() - 1);
        if (!isOutOfBounds(checkPosition)) {
            vector<GamePlay> *rowsToOccupy = new vector<GamePlay>;
            //check if the position is not occupied.
            if (this->boardMatrix[checkPosition.row()][checkPosition.column()] == None) {
                int columnIndex = 1;
                bool endRowSearch = false;
                GamePlay searchRowPosition(opponentPosition.row(), opponentPosition.column() + columnIndex);
                while (!isOutOfBounds(searchRowPosition) && !endRowSearch) {
                    if (this->boardMatrix[searchRowPosition.row()][searchRowPosition.column()] == type) {
                        RowOccupationContainer container(GamePlay(checkPosition.row(), checkPosition.column()));
                        for (int i = 0; i < rowsToOccupy->size(); i++) {
                            container.addCellToOccupy(rowsToOccupy->at(i));
                        }
                        container.addCellToOccupy(opponentPosition);
                        bool hasDuplicate = false;
                        for (int i = 0; i < gamePlays->size(); i++) {
                            if (gamePlays->at(i).getOccupaiedCell() == container.getOccupaiedCell()) {
                                hasDuplicate = true;
                                for (int j = 0; j < container.getCells()->size(); j++) {
                                    gamePlays->at(i).addCellToOccupy(container.getCells()->at(j));
                                }
                            }
                        }
                        if (!hasDuplicate) {
                            gamePlays->push_back(container);
                        }
                        endRowSearch = true;
                    } else if (this->boardMatrix[searchRowPosition.row()][searchRowPosition.column()] == None) {
                        endRowSearch = true;
                    } else {
                        rowsToOccupy->push_back(searchRowPosition);
                        searchRowPosition.setColumn(searchRowPosition.column() + columnIndex);
                    }
                }
            }
            delete rowsToOccupy;
        }
    }
    return gamePlays;
}

bool Board::isFullBoard() {
    return rows * columns -
           this->whitePlayerPositions->size() * this->blackPlayerPositions->size() == 0;
}

bool Board::hasStandardPossibleGamePlays(Board::PlayersType type) {
    return !getStandardPossibleGamePlays(type)->empty();
}

void Board::makePlay(Board::PlayersType type, RowOccupationContainer play) {
    this->boardMatrix[play.getOccupaiedCell().row()][play.getOccupaiedCell().column()] = type;
    vector<GamePlay> *currentPlayer;
    if (type == White) {
        currentPlayer = this->whitePlayerPositions;
    } else {
        currentPlayer = this->blackPlayerPositions;
    }
    currentPlayer->push_back(play.getOccupaiedCell());
    for (int i = 0; i < play.getCells()->size(); i++) {
        this->boardMatrix[play.getCells()->at(i).row()][play.getCells()->at(i).column()] = type;
        currentPlayer->push_back(play.getCells()->at(i));
    }
    updateBoardOccupationStatus();

}

int Board::getNumberOfDisks(Board::PlayersType type) {
    switch (type) {
        case Black:
            return static_cast<int>(this->blackPlayerPositions->size());
        case White:
            return static_cast<int>(this->whitePlayerPositions->size());
        case None:
            break;
    }
}

bool Board::isOutOfBounds(GamePlay play) {
    return (play.row() < 0 ||
            play.row() >= rows ||
            play.column() < 0 ||
            play.column() >= columns);
}

void Board::updateBoardOccupationStatus() {
    for (int i = 0; i < this->whitePlayerPositions->size(); i++) {
        if (this->boardMatrix[this->whitePlayerPositions->at(i).row()][this->whitePlayerPositions->at(i).column()] !=
            White) {
            this->whitePlayerPositions->erase(this->whitePlayerPositions->begin() + i);
        }
    }
    for (int i = 0; i < this->blackPlayerPositions->size(); i++) {
        if (this->boardMatrix[this->blackPlayerPositions->at(i).row()][this->blackPlayerPositions->at(i).column()] !=
            Black) {
            //this->blackPlayerPositions->erase(this->blackPlayerPositions->begin() + i);
            this->blackPlayerPositions->erase(this->blackPlayerPositions->begin() + i);
        }
    }
}

