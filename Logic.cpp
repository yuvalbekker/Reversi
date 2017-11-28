// Name: Eyal Lantzman ID: 205502818

#include "Logic.h"

using namespace std;

Logic::Logic(Board *b) : boardClass(b) {
}

Board &Logic::getBoardClass() const {

    // Return a dereferenced pointer (a ref):
    return *boardClass;
}

Logic::~Logic() {

}

///////// FLIPPING: /////////////////////////////////

void Logic::makeMove(struct Checker::position pos, Player player) {

    // Decrement the given position to fit the array (index starting from 0):
    pos.row--;
    pos.col--;

    // Get the piece in this position:
    Checker &checker = boardClass->getBoard()[pos.row][pos.col];

    // Place the piece in the given position:

    if (player == Black) {
        checker.setX();
    }

    if (player == White) {
        checker.setO();
    }

    // If piece is in corner #1, flip these directions
    if (pos.row == 0 && pos.col == 0) {
        flipRight(checker.getPosition(), player);
        flipDown(checker.getPosition(), player);
        flipDownRight(checker.getPosition(), player);
        return;
    }

    // If piece is in corner #2, flip these directions
    if (pos.row == boardClass->getSize() - 1 && pos.col == 0) {
        flipRight(checker.getPosition(), player);
        flipUp(checker.getPosition(), player);
        flipUpRight(checker.getPosition(), player);
        return;
    }

    // If piece is in corner #3, flip these directions
    if (pos.row == 0 && pos.col == boardClass->getSize() - 1) {
        flipLeft(checker.getPosition(), player);
        flipDown(checker.getPosition(), player);
        flipDownLeft(checker.getPosition(), player);
        return;
    }

    // If piece is in corner #4, flip these directions
    if (pos.row == boardClass->getSize() - 1 && pos.col == boardClass->getSize() - 1) {
        flipUp(checker.getPosition(), player);
        flipLeft(checker.getPosition(), player);
        flipUpLeft(checker.getPosition(), player);
        return;
    }

    // If piece is in frame-row #1, flip these directions
    if (pos.row == 0 && pos.col != 0) {
        flipDown(checker.getPosition(), player);
        flipLeft(checker.getPosition(), player);
        flipRight(checker.getPosition(), player);
        flipDownRight(checker.getPosition(), player);
        flipDownLeft(checker.getPosition(), player);
        return;
    }

    // If piece is in frame-row #2, flip these directions
    if (pos.row == getBoardClass().getSize() - 1 && pos.col != 0) {
        flipUp(checker.getPosition(), player);
        flipLeft(checker.getPosition(), player);
        flipRight(checker.getPosition(), player);
        flipUpRight(checker.getPosition(), player);
        flipUpLeft(checker.getPosition(), player);
        return;
    }

    // If piece is in frame-row #3, flip these directions
    if (pos.row != 0 && pos.col == boardClass->getSize() - 1) {
        flipUp(checker.getPosition(), player);
        flipLeft(checker.getPosition(), player);
        flipDown(checker.getPosition(), player);
        flipUpLeft(checker.getPosition(), player);
        flipDownLeft(checker.getPosition(), player);
        return;
    }

    // If piece is in frame-row #4, flip these directions
    if (pos.row != 0 && pos.col == 0) {
        flipUpRight(checker.getPosition(), player);
        flipUp(checker.getPosition(), player);
        flipRight(checker.getPosition(), player);
        flipDownRight(checker.getPosition(), player);
        flipDown(checker.getPosition(), player);
        return;
    }

    // If piece is in open space, flip these directions
    if (pos.row != 0 && pos.col != 0) {
        flipRight(checker.getPosition(), player);
        flipLeft(checker.getPosition(), player);
        flipUp(checker.getPosition(), player);
        flipDown(checker.getPosition(), player);
        flipUpLeft(checker.getPosition(), player);
        flipUpRight(checker.getPosition(), player);
        flipDownLeft(checker.getPosition(), player);
        flipDownRight(checker.getPosition(), player);
        return;
    }
}


void Logic::flipDownLeft(Checker::position pos, Player player) {

    // Decrement column position:
    int j = pos.col - 1;

    // A vector to store possible flips:
    vector<Checker::position> vec;
    bool enemyEncountered = false;

    // Increment the row by each loop:
    for (int i = pos.row + 1; i <= getBoardClass().getSize() - 1; i++) {
        Checker &nextChecker = getBoardClass().getBoard()[i][j];

        // If the next piece to check is empty, return:
        if (nextChecker.isEmpty()) {
            return;
        }

        // If the next piece to check is your own piece, check
        // if there were enemy pieces before. If so, flip them,
        // if not, return.
        if (player == Black && nextChecker.getVal() == 'X'
            || player == White && nextChecker.getVal() == 'O') {
            if (j == 0 && !enemyEncountered) {
                return;
            }
            if (enemyEncountered) {
                int a = 0;
                for (a = 0; a < vec.size(); a++) {
                    if (player == Black) {
                        getBoardClass().getBoard()[vec[a].row][vec[a].col].setX();
                    }
                    if (player == White) {
                        getBoardClass().getBoard()[vec[a].row][vec[a].col].setO();
                    }
                }
                return;
            } else {
                return;
            }
        }

        //If the next piece is an enemy piece, store it and continue:
        if (player == Black && nextChecker.getVal() == 'O'
            || player == White && nextChecker.getVal() == 'X') {
            enemyEncountered = true;
            Checker::position p;
            p.row = i;
            p.col = j;
            vec.push_back(p);
            if (j == 0) {
                return;
            }
            if (j > 0) {
                j--;
            }
            continue;
        }
    }
}


void Logic::flipDownRight(Checker::position pos, Player player) {
    int j = pos.col + 1;

    // A vector to store possible flips:
    vector<Checker::position> vec;
    bool enemyEncountered = false;

    for (int i = pos.row + 1; i <= getBoardClass().getSize() - 1; i++) {
        Checker &nextChecker = getBoardClass().getBoard()[i][j];

        // If the next piece is empty, return:
        if (nextChecker.isEmpty()) {
            return;
        }

        // If the next piece to check is your own piece, check
        // if there were enemy pieces before. If so, flip them,
        // if not, return.
        if (player == Black && nextChecker.getVal() == 'X'
            || player == White && nextChecker.getVal() == 'O') {
            if (j == 0 && !enemyEncountered) {
                return;
            }
            if (enemyEncountered) {
                int a = 0;
                for (a = 0; a < vec.size(); a++) {
                    if (player == Black) {
                        getBoardClass().getBoard()[vec[a].row][vec[a].col].setX();
                    }
                    if (player == White) {
                        getBoardClass().getBoard()[vec[a].row][vec[a].col].setO();
                    }
                }
                return;
            } else {
                return;
            }
        }

        // If the next piece is an enemy, store it and continue.
        if (player == Black && nextChecker.getVal() == 'O'
            || player == White && nextChecker.getVal() == 'X') {
            if (j == getBoardClass().getSize() - 1 && enemyEncountered) {
                return;
            }
            enemyEncountered = true;
            Checker::position p;
            p.row = i;
            p.col = j;
            vec.push_back(p);
            if (j < getBoardClass().getSize() - 1) {
                j++;
            }
            continue;
        }
    }
}

void Logic::flipUpRight(Checker::position pos, Player player) {
    int j = pos.col + 1;

    // A vector to store possible flips:
    vector<Checker::position> vec;
    bool enemyEncountered = false;

    for (int i = pos.row - 1; i >= 0; i--) {
        Checker &nextChecker = getBoardClass().getBoard()[i][j];

        // If the next piece to check is empty, return:
        if (nextChecker.isEmpty()) {
            return;
        }

        // If the next piece to check is your own piece, check
        // if there were enemy pieces before. If so, flip them,
        // if not, return.
        if (player == Black && nextChecker.getVal() == 'X'
            || player == White && nextChecker.getVal() == 'O') {
            if (j == 0 && !enemyEncountered) {
                return;
            }
            if (enemyEncountered) {
                int a = 0;
                for (a = 0; a < vec.size(); a++) {
                    if (player == Black) {
                        getBoardClass().getBoard()[vec[a].row][vec[a].col].setX();
                    }
                    if (player == White) {
                        getBoardClass().getBoard()[vec[a].row][vec[a].col].setO();
                    }
                }
                return;
            } else {
                return;
            }
        }

        // If the next piece to check is an enemy, store it and continue:
        if (player == Black && nextChecker.getVal() == 'O'
            || player == White && nextChecker.getVal() == 'X') {
            if (j == getBoardClass().getSize() - 1 && enemyEncountered) {
                return;
            }
            enemyEncountered = true;
            Checker::position p;
            p.row = i;
            p.col = j;
            vec.push_back(p);
            if (j < getBoardClass().getSize() - 1) {
                j++;
            }
            continue;
        }
    }
}

void Logic::flipUpLeft(Checker::position pos, Player player) {
    int j = pos.col - 1;

    // A vector to store possible flips:
    vector<Checker::position> vec;
    bool enemyEncountered = false;

    for (int i = pos.row - 1; i >= 0; i--) {
        Checker &nextChecker = getBoardClass().getBoard()[i][j];

        if (nextChecker.isEmpty()) {
            return;
        }

        // If the next piece to check is your own piece, check
        // if there were enemy pieces before. If so, flip them,
        // if not, return.
        if (player == Black && nextChecker.getVal() == 'X'
            || player == White && nextChecker.getVal() == 'O') {
            if (j == 0 && !enemyEncountered) {
                return;
            }
            if (enemyEncountered) {
                int a = 0;
                for (a = 0; a < vec.size(); a++) {
                    if (player == Black) {
                        getBoardClass().getBoard()[vec[a].row][vec[a].col].setX();
                    }
                    if (player == White) {
                        getBoardClass().getBoard()[vec[a].row][vec[a].col].setO();
                    }
                }
                return;
            } else {
                return;
            }
        }

        // If the next piece is an enemy, store it and continue:
        if (player == Black && nextChecker.getVal() == 'O'
            || player == White && nextChecker.getVal() == 'X') {
            enemyEncountered = true;
            Checker::position p;
            p.row = i;
            p.col = j;
            vec.push_back(p);
            if (j == 0) {
                return;
            }
            if (j > 0) {
                j--;
            }
            continue;
        }
    }
}

void Logic::flipLeft(Checker::position pos, Player player) {
    int i = 0;

    if (player == Black) {

        // A vector to store possible flips:
        vector<Checker::position> vec;
        bool enemyEncountered = false;

        for (i = pos.col - 1; i >= 0; i--) {

            // If the next piece to check is empty, return:
            if (getBoardClass().getBoard()[pos.row][i].isEmpty()) {
                return;
            }

            // If the next piece to check is your own piece, check
            // if there were enemy pieces before. If so, flip them,
            // if not, return.
            if (getBoardClass().getBoard()[pos.row][i].getVal() == 'X') {
                if (enemyEncountered) {
                    int a = 0;
                    for (a = 0; a < vec.size(); a++) {
                        getBoardClass().getBoard()[vec[a].row][vec[a].col].setX();
                    }
                    return;
                } else {
                    return;
                }
            }

            // If the next piece is an enemy, store it and continue:
            if (getBoardClass().getBoard()[pos.row][i].getVal() == 'O') {
                enemyEncountered = true;
                Checker::position p;
                p.row = pos.row;
                p.col = i;
                vec.push_back(p);
                continue;
            }
        }
    }

    // Similarly for white:
    if (player == White) {
        vector<Checker::position> vec;
        bool enemyEncountered = false;

        for (i = pos.col - 1; i >= 0; i--) {
            if (getBoardClass().getBoard()[pos.row][i].isEmpty()) {
                return;
            }

            if (getBoardClass().getBoard()[pos.row][i].getVal() == 'O') {
                if (enemyEncountered) {
                    int a = 0;
                    for (a = 0; a < vec.size(); a++) {
                        getBoardClass().getBoard()[vec[a].row][vec[a].col].setO();
                    }
                    return;
                } else {
                    return;
                }
            }

            if (getBoardClass().getBoard()[pos.row][i].getVal() == 'X') {
                enemyEncountered = true;
                Checker::position p;
                p.row = pos.row;
                p.col = i;
                vec.push_back(p);
                continue;
            }
        }
    }
}

void Logic::flipRight(Checker::position pos, Player player) {
    int i = 0;

    if (player == Black) {

        // A vector to store possible flips:
        vector<Checker::position> vec;
        bool enemyEncountered = false;

        for (i = pos.col + 1; i <= getBoardClass().getSize() - 1; i++) {

            // If the next piece to check is empty, return:
            if (getBoardClass().getBoard()[pos.row][i].isEmpty()) {
                return;
            }

            // If the next piece to check is your own piece, check
            // if there were enemy pieces before. If so, flip them,
            // if not, return.
            if (getBoardClass().getBoard()[pos.row][i].getVal() == 'X') {
                if (enemyEncountered) {
                    int a = 0;
                    for (a = 0; a < vec.size(); a++) {
                        getBoardClass().getBoard()[vec[a].row][vec[a].col].setX();
                    }
                    return;
                } else {
                    return;
                }
            }

            // If the next piece is an enemy, store it and continue.
            if (getBoardClass().getBoard()[pos.row][i].getVal() == 'O') {
                enemyEncountered = true;
                Checker::position p;
                p.row = pos.row;
                p.col = i;
                vec.push_back(p);
                continue;
            }
        }
    }

    // Similarly for white:
    if (player == White) {
        vector<Checker::position> vec;
        bool enemyEncountered = false;

        for (i = pos.col + 1; i <= getBoardClass().getSize() - 1; i++) {
            if (getBoardClass().getBoard()[pos.row][i].isEmpty()) {
                return;
            }

            if (getBoardClass().getBoard()[pos.row][i].getVal() == 'O') {
                if (enemyEncountered) {
                    int a = 0;
                    for (a = 0; a < vec.size(); a++) {
                        getBoardClass().getBoard()[vec[a].row][vec[a].col].setO();
                    }
                    return;
                } else {
                    return;
                }
            }

            if (getBoardClass().getBoard()[pos.row][i].getVal() == 'X') {
                enemyEncountered = true;
                Checker::position p;
                p.row = pos.row;
                p.col = i;
                vec.push_back(p);
                continue;
            }
        }
    }
}

void Logic::flipUp(Checker::position pos, Player player) {
    int i = 0;

    if (player == Black) {

        // A vector to store possible flips:
        vector<Checker::position> vec;
        bool enemyEncountered = false;

        for (i = pos.row - 1; i >= 0; i--) {

            // If the next piece is empty, return:
            if (getBoardClass().getBoard()[i][pos.col].isEmpty()) {
                return;
            }

            // If the next piece to check is your own piece, check
            // if there were enemy pieces before. If so, flip them,
            // if not, return.
            if (getBoardClass().getBoard()[i][pos.col].getVal() == 'X') {
                if (enemyEncountered) {
                    int a = 0;
                    for (a = 0; a < vec.size(); a++) {
                        getBoardClass().getBoard()[vec[a].row][vec[a].col].setX();
                    }
                    return;
                } else {
                    return;
                }
            }

            // If the next piece is an enemy, store it and continue.
            if (getBoardClass().getBoard()[i][pos.col].getVal() == 'O') {
                enemyEncountered = true;
                Checker::position p;
                p.row = i;
                p.col = pos.col;
                vec.push_back(p);
                continue;
            }
        }
    }

    // Similarly for white:
    if (player == White) {
        vector<Checker::position> vec;
        bool enemyEncountered = false;

        for (i = pos.row - 1; i >= 0; i--) {
            if (getBoardClass().getBoard()[i][pos.col].isEmpty()) {
                return;
            }

            if (getBoardClass().getBoard()[i][pos.col].getVal() == 'O') {
                if (enemyEncountered) {
                    int a = 0;
                    for (a = 0; a < vec.size(); a++) {
                        getBoardClass().getBoard()[vec[a].row][vec[a].col].setO();
                    }
                    return;
                } else {
                    return;
                }
            }

            if (getBoardClass().getBoard()[i][pos.col].getVal() == 'X') {
                enemyEncountered = true;
                Checker::position p;
                p.row = i;
                p.col = pos.col;
                vec.push_back(p);
                continue;
            }
        }
    }
}

void Logic::flipDown(Checker::position pos, Player player) {
    int i = 0;

    if (player == Black) {

        // A vector to store possible flips:
        vector<Checker::position> vec;
        bool enemyEncountered = false;

        for (i = pos.row + 1; i <= getBoardClass().getSize() - 1; i++) {

            // If the next piece to check is empty, return:
            if (getBoardClass().getBoard()[i][pos.col].isEmpty()) {
                return;
            }

            // If the next piece to check is your own piece, check
            // if there were enemy pieces before. If so, flip them,
            // if not, return.
            if (getBoardClass().getBoard()[i][pos.col].getVal() == 'X') {
                if (enemyEncountered) {
                    int a = 0;
                    for (a = 0; a < vec.size(); a++) {
                        getBoardClass().getBoard()[vec[a].row][vec[a].col].setX();
                    }
                    return;
                } else {
                    return;
                }
            }

            // If the next piece is an enemy, store it and continue.
            if (getBoardClass().getBoard()[i][pos.col].getVal() == 'O') {
                enemyEncountered = true;
                Checker::position p;
                p.row = i;
                p.col = pos.col;
                vec.push_back(p);
                continue;
            }
        }
    }

    // Similarly for white:
    if (player == White) {
        vector<Checker::position> vec;
        bool enemyEncountered = false;

        for (i = pos.row + 1; i <= getBoardClass().getSize() - 1; i++) {
            if (getBoardClass().getBoard()[i][pos.col].isEmpty()) {
                return;
            }

            if (getBoardClass().getBoard()[i][pos.col].getVal() == 'O') {
                if (enemyEncountered) {
                    int a = 0;
                    for (a = 0; a < vec.size(); a++) {
                        getBoardClass().getBoard()[vec[a].row][vec[a].col].setO();
                    }
                    return;
                } else {
                    return;
                }
            }

            if (getBoardClass().getBoard()[i][pos.col].getVal() == 'X') {
                enemyEncountered = true;
                Checker::position p;
                p.row = i;
                p.col = pos.col;
                vec.push_back(p);
                continue;
            }
        }
    }
}