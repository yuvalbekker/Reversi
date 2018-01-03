#include <iostream>
#include <sstream>
#include "../include/ConsoleGui.h"
#include "../include/AIPlayer.h"
#include "../include/RegularPlayer.h"
#include "../include/RemoteOnlinePlayer.h"

using namespace std;

ConsoleGui::ConsoleGui() {

}

ConsoleGui::~ConsoleGui() {

}

void ConsoleGui::printBoard(Board *b) {
    cout << "\n";
    cout << "Current Board: \n" << endl;
    int i = 0, j = 0, q = 0;

    // Column # Indicators:
    cout << " |";
    for (i = 0; i < b->getSize(); i++) {
        cout << " " << i + 1 << " |";
    }
    cout << endl;

    // Separator after this row:
    for (i = 0; i < (b->getSize() * 4) + 2; i++) {
        cout << "-";
    }
    cout << endl;

    // Row # Indicators and board values:
    for (i = 0; i < b->getSize(); i++) {
        cout << i + 1 << "|";
        for (j = 0; j < b->getSize(); j++) {
            cout << " " << b->getBoard()[i][j].getVal() << " |";
        }
        cout << endl;

        // Separators between lines:
        for (q = 0; q < (b->getSize() * 4) + 2; q++) {
            cout << "-";
        }
        cout << endl;
    }
}

void ConsoleGui::printPossiblePlays(std::vector<Checker::position> &moves, IPlayer *player) {
    cout << "Player " << player->playerType << " It's your turn." << endl;
    cout << "Your " << moves.size() << " possible moves: ";
    if (moves.empty()) {
        cout << "You have no possible moves. Play goes to the "
                "other player." << endl;
    } else {
        for (int i = 0; i < moves.size(); i++) {
            cout << "(" << moves[i].row + 1
                 << "," << moves[i].col + 1 << ")" << " ";
        }
        cout << "\n";
    }
}

void ConsoleGui::printGameResult(GameResult result) {
    switch (result.getResult()) {
        case GameResult::Black:
            cout << "Black wins! He has a score of " << result.getScore() << endl;
            break;
        case GameResult::White:
            cout << "White wins! He has a score of " << result.getScore() << endl;
            break;
        case GameResult::None:
            cout << "It's a tie! The score is " << result.getScore() << endl;
            break;
    }
}

int ConsoleGui::scanPlayerType() {
    cout << "Welcome to Reversi!\n";
    cout << "Choose your opponent: \n";
    cout << "Press 0 exit: \n";
    cout << "Press 1 for Human player: \n";
    cout << "Press 2 for AI player: \n";
    cout << "Press 3 for Remote player: \n";
    int playerTypeInput = -1;
    string input;
    while (playerTypeInput != 0 && playerTypeInput != 1 && playerTypeInput != 2 && playerTypeInput != 3) {
        cin >> input;
        try {
            stringstream ss(input);
            ss >> playerTypeInput;
            if (playerTypeInput != 0 && playerTypeInput != 1 && playerTypeInput != 2 && playerTypeInput != 3) {
                cout << "Invalid input! try again: \n";
            }
        }
        catch (exception e) {
            cout << "Invalid input! try again: \n";
        }
    }
    return playerTypeInput;
}

void ConsoleGui::printScore(int blackPlayerScore, int whitePlayerScore) {
    cout << "Score:\n";
    cout << "X: " << blackPlayerScore << "\nO: " << whitePlayerScore << "\n";
}

void ConsoleGui::printChosenPlay(Checker::position move) {
    cout << "Chosen move: (" << move.row << "," << move.col << ")\n";
}