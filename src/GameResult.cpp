#include "../include/GameResult.h"

GameResult::GameResult(ResultType resultType, int score) {
    this->resultType = resultType;
    this->score = score;

}

int GameResult::getScore() {
    return this->score;
}

GameResult::ResultType GameResult::getResult() {
    return this->resultType;
}
