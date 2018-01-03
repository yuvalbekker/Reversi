#include "../include/Game.h"

Game::Game(string name, Player *player1, Player *player2) {
    this->name = name;
    this->firstPlayer = player1;
    this->firstPlayer = player2;
}

Game::Game(string name) {
    this->name = name;
    this->firstPlayer = new Player('X');
    this->secondPlayer = new Player('O');
}

Game::~Game() {
    //delete this->firstPlayer;
    //delete this->secondPlayer;
}

string Game::getGameName() {
    return this->name;
}

Player *Game::getFirstPlayer() {
    return this->firstPlayer;
}

Player *Game::getSecondPlayer() {
    return this->secondPlayer;
}

void Game::setSecondPlayer(Player *player) {
    this->secondPlayer = player;
}

void Game::setFirstPlayer(Player *player) {
    this->firstPlayer = player;
}

void Game::setGameName(string name) {
    this->name = name;
}

bool Game::isBusy() {
    return this->firstPlayer->isConnected() && this->secondPlayer->isConnected();
}


