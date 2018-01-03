#include "../include/RegularPlayer.h"
#include <limits>

using namespace std;

RegularPlayer::RegularPlayer(char playerType) {
    this->playerType = playerType;
}

Checker::position RegularPlayer::generatePosition(std::vector<Checker::position> &moves, Board &board) {

    // Declare variables:
    Checker::position pos;
    int i = 0;
    int j = 0;

    // Interface with the user to get a move:
    while (true) {
        bool foundInMoves = false;
        cout << "\nPlease enter your move in the format: row col" << endl;
        cin >> i >> j;

        if (cin.fail() || i > 8 || i <= 0 || j > 8 || j <= 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input." << endl;
            continue;
        }

        // Check if the move is possible:
        for (int k = 0; k < moves.size(); k++) {
            if (moves[k].row == i - 1 && moves[k].col == j - 1) {
                foundInMoves = true;
            }
        }

        if (!foundInMoves) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Not a legal move." << endl;
            continue;
        }

        // If the move is possible:
        pos.row = i;
        pos.col = j;
        moves.clear();

        return pos;
    }
}

RegularPlayer::~RegularPlayer() {

}

