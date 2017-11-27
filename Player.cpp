//Yuval Bekker
//311254585

#include <iostream>
#include <sstream>
#include "Player.h"

Player::Player(Disk *disk, Board::PlayersType type) {
    this->disk = disk;
    this->type = type;
}

Disk *Player::playersDisk() {
    return this->disk;
}

Player::Player() {}

Board::PlayersType Player::getPlayerType() {
    return this->type;
}

GamePlay Player::generateGamePlay() {
    bool inputMoveScanned = false;
    while (!inputMoveScanned) {
        cout << "Please enter your move row,col: ";
        int row, col;
        string str;
        cin >> str;
        vector<int> separatedValues;

        stringstream ss(str);

        if (str == "exit") {
            return GamePlay(-1, -1);
        }

        int i;

        while (ss >> i) {
            separatedValues.push_back(i);

            if (ss.peek() == ',')
                ss.ignore();
        }
        try {

            row = separatedValues.at(0);
            col = separatedValues.at(1);
            return GamePlay(row, col);

        }
        catch (exception e) {
            cout << "Invalid input!\n";
        }
    }
}

Player::~Player() {
    delete disk;
}

