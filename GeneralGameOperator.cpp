//Yuval Bekker
//311254585

#include <iostream>
#include <sstream>
#include "GeneralGameOperator.h"

bool GeneralGameOperator::isGameOver() {
    if (this->board->isFullBoard() || this->endGame) {
        return true;
    } else {
        if (!this->board->hasStandardPossibleGamePlays(Board::Black) &&
            !this->board->hasStandardPossibleGamePlays(Board::White)) {
            return true;
        }
    }
    return false;
}

void GeneralGameOperator::switchTurn() {
    if (this->currentPlayerTurn == this->firstPlayer) {
        this->currentPlayerTurn = this->secondPlayer;
    } else {
        this->currentPlayerTurn = this->firstPlayer;
    }
}

GameResult GeneralGameOperator::play(IRuleEnricher ruleEnricher) {
    while (!isGameOver()) {
        printBoard();
        //calculate the standard possible moves.
        vector<RowOccupationContainer> *possiblePlays = this->board->getStandardPossibleGamePlays(
                this->currentPlayerTurn->getPlayerType());
        possiblePlays = ruleEnricher.enrichPossiblePlays(possiblePlays);
        //print the possible moves
        showPossiblePlays(possiblePlays);
        if (possiblePlays->size() != 0) {
            GamePlay inputGamePlay;
            //read the input move
            do {
                inputGamePlay = this->currentPlayerTurn->generateGamePlay();
                if (inputGamePlay == GamePlay(-1, -1)) {
                    this->endGame = true;
                    break;
                }
            } while (!isValidGamePlay(inputGamePlay, possiblePlays));
            if (!endGame) {
                inputGamePlay.setRow(inputGamePlay.row());
                inputGamePlay.setColumn(inputGamePlay.column());

                for (int i = 0; i < possiblePlays->size(); i++) {
                    GamePlay cellToCompare(possiblePlays->at(i).getOccupaiedCell().row() + 1,
                                           possiblePlays->at(i).getOccupaiedCell().column() + 1);
                    if (cellToCompare == inputGamePlay) {
                        //apply the input move on the game board.
                        RowOccupationContainer container(possiblePlays->at(i).getOccupaiedCell());
                        for (int j = 0; j < possiblePlays->at(i).getCells()->size(); j++) {
                            container.addCellToOccupy(possiblePlays->at(i).getCells()->at(j));
                        }
                        this->board->makePlay(this->currentPlayerTurn->getPlayerType(), container);
                        break;
                    }
                }
            }
            for (int i = 0; i < possiblePlays->size(); i++) {
                delete possiblePlays->at(i).getCells();
            }
            delete possiblePlays;
        }
        switchTurn();
    }
    GameResult result = calculateGameResult();
    return result;

}

bool GeneralGameOperator::isValidGamePlay(GamePlay play, vector<RowOccupationContainer> *plays) {
    for (int i = 0; i < plays->size(); i++) {
        GamePlay cellToCompare(plays->at(i).getOccupaiedCell().row() + 1,
                               plays->at(i).getOccupaiedCell().column() + 1);
        if (play == cellToCompare) {
            return true;
        }
    }
    cout << "Invalid input!\n";
    return false;
}

void GeneralGameOperator::initializeGame(int rows, int columns) {
    this->currentPlayerTurn = this->firstPlayer;
    this->board = new Board(rows, columns);
    this->mapOfSymbols.insert(make_pair(Board::Black, this->firstPlayer->playersDisk()));
    this->mapOfSymbols.insert(make_pair(Board::White, this->secondPlayer->playersDisk()));
    this->endGame = false;
}

string GeneralGameOperator::parseGamePlayToString(GamePlay play) {
    string playString("(");
    stringstream ss;
    ss << play.row() + 1;
    playString += ss.str();
    playString += ",";
    ss.str("");
    ss << play.column() + 1;
    playString += ss.str();
    playString += ")";
    return playString;
}

GameResult GeneralGameOperator::calculateGameResult() {
    //calculate the winning score & player.
    int whitePlayerScore = this->board->getNumberOfDisks(Board::White);
    int blackPlayerScore = this->board->getNumberOfDisks(Board::Black);
    if (whitePlayerScore > blackPlayerScore) {
        return GameResult(Board::White, whitePlayerScore);
    } else if (whitePlayerScore < blackPlayerScore) {
        return GameResult(Board::Black, blackPlayerScore);
    } else {
        return GameResult(Board::None, blackPlayerScore);
    }
}
