// Name: Eyal Lantzman ID: 205502818

#include "Flow.h"
#include <limits>

using namespace std;

Flow::Flow(Logic &l) : logic(l) {

    // Initialize booleans:

    blackMovesEnded = false;
    whiteMovesEnded = false;
}

int Flow::countWhite() const {
    int count = 0;
    int i = 0;
    int j = 0;
    for (i = 0; i < logic.getBoardClass().getSize(); i++) {
        for (j = 0; j < logic.getBoardClass().getSize(); j++) {
            if (logic.getBoardClass().getBoard()[i][j].getVal() == 'O') {
                count++;
            }
        }
    }

    return count;
}

int Flow::countBlack() const {
    int count = 0;
    int i = 0;
    int j = 0;
    for (i = 0; i < logic.getBoardClass().getSize(); i++) {
        for (j = 0; j < logic.getBoardClass().getSize(); j++) {
            if (logic.getBoardClass().getBoard()[i][j].getVal() == 'X') {
                count++;
            }
        }
    }

    return count;
}

void Flow::play() {
    while (true) {

        // Play a turn for Black:

        playBlack();

        // If the board is full or there are no more moves:

        if (countWhite() + countBlack() == (logic.getBoardClass().getSize() * logic.getBoardClass().getSize())
            || (whiteMovesEnded && blackMovesEnded)) {

            if (countBlack() > countWhite()) {
                cout << "Black wins! Good game." << endl;
                return;
            }


            if (countBlack() < countWhite()) {
                cout << "White wins! Good game." << endl;
                return;
            }

            if (countWhite() == countBlack()) {
                cout << "It's a tie! Good game." << endl;
                return;
            }
        }

        // Play a turn for White:

        playWhite();

        // If the board is full or there are no more moves:

        if (countWhite() + countBlack() == (logic.getBoardClass().getSize() * logic.getBoardClass().getSize())
            || (whiteMovesEnded && blackMovesEnded)) {
            if (countBlack() > countWhite()) {
                cout << "Black wins! Good game." << endl;
                return;
            }

            if (countBlack() < countWhite()) {
                cout << "White wins! Good game." << endl;
                return;
            }

            if (countWhite() == countBlack()) {
                cout << "It's a tie! Good game." << endl;
                return;
            }
        }
    }
}


void Flow::playBlack() {

    // Print the board status:
    cout << "Current Board: " << endl;
    logic.getBoardClass().print();


    // Get possible moves:
    vector<Checker::position> &moves = logic.calcPossibleMoves(Logic::Black);

    cout << "Player X: It's your turn." << endl;
    cout << "Your " << moves.size() << " possible moves: ";

    // If there are no possible moves, mark it and return:
    if (moves.empty()) {
        blackMovesEnded = true;
        cout << "You have no possible moves. Play goes to the "
                "other player." << endl;

        return;
    }

    // If there are moves, print them out:
    for (int i = 0; i < moves.size(); i++) {
        cout << "(" << moves[i].row + 1
             << "," << moves[i].col + 1 << ")" << " ";
    }

    Checker::position pos;
    int i = 0;
    int j = 0;

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

        break;
    }

    // Make the move:
    logic.makeMove(pos, Logic::Black);
}


void Flow::playWhite() {

    // Print the board status:
    cout << "Current Board: " << endl;
    logic.getBoardClass().print();

    // Get possible moves for White
    vector<Checker::position> &moves = logic.calcPossibleMoves(Logic::White);

    cout << "Player O: It's your turn." << endl;
    cout << "Your " << moves.size() << " possible moves: ";

    // If there are no possible moves:
    if (moves.empty()) {
        whiteMovesEnded = true;
        cout << "You have no possible moves. Play goes to the "
                "other player." << endl;

        return;
    }

    // If there are moves, print them out:

    for (int i = 0; i < moves.size(); i++) {
        cout << "(" << moves[i].row + 1
             << "," << moves[i].col + 1 << ")" << " ";
    }

    Checker::position pos;
    int i = 0;
    int j = 0;

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

        // Check if it's a legal move:
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

        // If it is, keep it:
        pos.row = i;
        pos.col = j;
        moves.clear();

        break;
    }

    // Make the move:
    logic.makeMove(pos, Logic::White);
}