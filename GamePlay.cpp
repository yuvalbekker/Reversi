//Yuval Bekker
//311254585

#include "GamePlay.h"

GamePlay::GamePlay(int ruwNumber, int columnNumber) {
    this->rowNum = ruwNumber;
    this->columnNum = columnNumber;
}

int GamePlay::row() {
    return this->rowNum;
}

int GamePlay::column() {
    return this->columnNum;
}

bool GamePlay::operator==(GamePlay play) {
    return (this->rowNum == play.row() && this->columnNum == play.column());
}

GamePlay::GamePlay() {

}

void GamePlay::setRow(int row) {
    this->rowNum = row;
}

void GamePlay::setColumn(int column) {
    this->columnNum = column;
}

GamePlay::~GamePlay() {

}
