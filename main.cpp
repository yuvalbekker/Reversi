//Yuval Bekker
//311254585

#include <iostream>
#include <sstream>
#include "Board.h"
#include "ConsoleGameOperator.h"
#include "StandardRuleEnricher.h"
#include "AIPlayer.h"

using namespace std;

int getPlayerType() {
    cout << "Choose your opponent: \n";
    cout << "Press 1 for Human player: \n";
    cout << "Press 2 for AI player: \n";
    int playerTypeInput = -1;
    string input;
    while (playerTypeInput != 1 && playerTypeInput != 2) {
        cin >> input;
        try {
            stringstream ss(input);
            ss >> playerTypeInput;
            if (playerTypeInput != 1 && playerTypeInput != 2) {
                cout << "Wrong input! try again: \n";
            }
        }
        catch (exception e) {
            cout << "Wrong input! try again: \n";
        }
    }
    return playerTypeInput;
}

/**
* The main function of the program.
* @return int
*/
int main() {
    //check branch commit

    cout << "Welcome to Reversi!\n";

    //Initialize your player
    Player *first = new Player(new Disk('X'), Board::Black);
    Player *second;
    int playerTypeInput = getPlayerType();
    if (playerTypeInput == 1) {
        second = new Player(new Disk('O'), Board::White);
    } else if (playerTypeInput == 2) {
        second = new AIPlayer(new Disk('O'), Board::White);
    }
    /*
    Player *second = new Player(new Disk('O'), Board::White);*/
    ConsoleGameOperator *gameOperator = new ConsoleGameOperator(first, second, 8, 8);
    GameResult result = gameOperator->play((StandardRuleEnricher()));
    switch (result.getType()) {
        case Board::White:
            cout << "O Player Won! your score is " << result.getScore();
            break;
        case Board::Black:
            cout << "X Player Won! your score is " << result.getScore();
            break;
        case Board::None:
            cout << "Tie. score is " << result.getScore();
            break;
    }
    cout << "\n";
    delete gameOperator;
    delete first;
    delete second;
    return 0;
}

