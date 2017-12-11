//Yuval Bekker
//311254585

#include "GameResult.h"

GameResult::GameResult() {

}

GameResult::GameResult(Board::PlayersType type, int score) {
    this->type = type;
    this->score = score;

}

int GameResult::getScore() {
    return this->score;
}

Board::PlayersType GameResult::getType() {
    return this->type;
}
