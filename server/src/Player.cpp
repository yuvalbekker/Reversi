#include <unistd.h>
#include "../include/Player.h"
#include <string>
#include <iostream>
#include <sys/socket.h>

using namespace std;

Player::Player(int socket) {
    this->socket = socket;
    this->symbol = 0;
}

Player::Player(int socket, char symbol) {
    this->socket = socket;
    this->symbol = symbol;
}


Player::Player(char symbol) {
    this->symbol = symbol;
    this->socket = -1;
}

Player::Player() {
    this->symbol = 0;
    this->socket = -1;
}


Player::~Player() {
    if (this->socket != -1) {
        disconnect();
    }
}

int Player::getSocket() {
    return this->socket;
}

char Player::getSymbol() {
    return this->symbol;
}

void Player::setSocket(int socket) {
    this->socket = socket;
}

void Player::setSymbol(char symbol) {
    this->symbol = symbol;
}

bool Player::isConnected() {
    return this->socket != -1;
}

void Player::disconnect() {
    string positionMessage = "-5 -5";
    int n = send(this->socket, positionMessage.data(), sizeof(positionMessage),
                 MSG_NOSIGNAL);
    cout << "Disconnect message sent to socket '" << this->socket << endl;
    close(this->socket);
    this->socket = -1;
}

void Player::closeGame() {
    string positionMessage = "-4 -4";
    int n = send(this->socket, positionMessage.data(), sizeof(positionMessage),
                 MSG_NOSIGNAL);
    cout << "Close Game message sent to socket " << this->socket << endl;
}

