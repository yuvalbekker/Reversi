#include <iostream>
#include <sstream>
#include "../include/ConsoleGui.h"
#include "../include/AIPlayer.h"
#include "../include/RegularPlayer.h"

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

    // Print the possible moves:
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

    // Print the game result based on the winner:
    switch (result.getResult()) {
        case GameResult::Black:
            cout << "Black wins! Your score is " << result.getScore() << endl;
            break;
        case GameResult::White:
            cout << "White wins! Your score is " << result.getScore() << endl;
            break;
        case GameResult::None:
            cout << "It's a tie! The score is " << result.getScore() << endl;
            break;
    }
}

IPlayer *ConsoleGui::scanPlayerType() {

    // Print a menu for the player to choose from:
    cout << "Welcome to Reversi!\n";
    cout << "Choose your opponent: \n";
    cout << "Press 1 for Human player: \n";
    cout << "Press 2 for AI player: \n";
    int playerTypeInput = -1;
    string input;

    // Ask for the player's input:
    while (playerTypeInput != 1 && playerTypeInput != 2) {
        cin >> input;
        try {
            stringstream ss(input);
            ss >> playerTypeInput;
            if (playerTypeInput != 1 && playerTypeInput != 2) {
                cout << "Invalid input! try again: \n";
            }
        }
        catch (exception e) {
            cout << "Invalid input! try again: \n";
        }
    }

    // Return the chosen player type:
    if (playerTypeInput == 1) {
        return new RegularPlayer('O');
    } else if (playerTypeInput == 2) {
        return new AIPlayer('O');
    }
}

void ConsoleGui::printScore(int blackPlayerScore, int whitePlayerScore) {

    // Print Black and White's scores:
    cout << "Score:\n";
    cout << "X: " << blackPlayerScore << "\nO: " << whitePlayerScore << "\n";
}

void ConsoleGui::printChosenPlay(Checker::position move) {
    cout << "Chosen move: (" << move.row << "," << move.col << ")\n";
}
