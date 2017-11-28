// Name: Eyal Lantzman ID: 205502818

#include "NormalRuleset.h"

using namespace std;

NormalRuleset::NormalRuleset(Board *b) : Logic::Logic(b) {
}

std::vector<struct Checker::position> &NormalRuleset::calcPossibleMoves(Player player) {
    int i = 0;
    int j = 0;

    moves.clear();

    // Go over each checker in the board:
    for (i = 0; i < getBoardClass().getSize(); i++) {
        for (j = 0; j < getBoardClass().getSize(); j++) {
            Checker checker = getBoardClass().getBoard()[i][j];

            // If the checker isn't empty, continue searching.
            if (!getBoardClass().getBoard()[i][j].isEmpty()) {
                continue;
            }

            // If the checker is in corner #1, check these directions:
            if (i == 0 && j == 0) {

                if (checkRight(checker.getPosition(), player)
                    || checkDown(checker.getPosition(), player)
                    || checkDownRight(checker.getPosition(), player)) {
                    moves.push_back(checker.getPosition());
                }
                continue;
            }

            // If the checker is in corner #2, check these directions:
            if (i == getBoardClass().getSize() - 1 && j == 0) {
                if (checkRight(checker.getPosition(), player)
                    || checkUp(checker.getPosition(), player)
                    || checkUpRight(checker.getPosition(), player)) {
                    moves.push_back(checker.getPosition());
                }
                continue;
            }

            // If the checker is in corner #3, check these directions:
            if (i == 0 && j == getBoardClass().getSize() - 1) {
                if (checkLeft(checker.getPosition(), player)
                    || checkDown(checker.getPosition(), player)
                    || checkDownLeft(checker.getPosition(), player)) {
                    moves.push_back(checker.getPosition());
                }
                continue;
            }

            // If the checker is in corner #4, check these directions:
            if (i == getBoardClass().getSize() - 1 && j == getBoardClass().getSize() - 1) {
                if (checkUp(checker.getPosition(), player)
                    || checkLeft(checker.getPosition(), player)
                    || checkUpLeft(checker.getPosition(), player)) {
                    moves.push_back(checker.getPosition());
                }
                continue;
            }

            // If the checker is in frame-row #1, check these directions:
            if (i == 0 && j != 0) {
                if (checkDown(checker.getPosition(), player)
                    || checkLeft(checker.getPosition(), player)
                    || checkRight(checker.getPosition(), player)
                    || checkDownRight(checker.getPosition(), player)
                    || checkDownLeft(checker.getPosition(), player)) {
                    moves.push_back(checker.getPosition());
                }
                continue;
            }

            // If the checker is in frame-row #2, check these directions:
            if (i == getBoardClass().getSize() - 1 && j != 0) {
                if (checkUp(checker.getPosition(), player)
                    || checkLeft(checker.getPosition(), player)
                    || checkRight(checker.getPosition(), player)
                    || checkUpRight(checker.getPosition(), player)
                    || checkUpLeft(checker.getPosition(), player)) {
                    moves.push_back(getBoardClass().getBoard()[i][j].getPosition());
                }
                continue;
            }

            // If the checker is in frame-row #3, check these directions:
            if (i != 0 && j == getBoardClass().getSize() - 1) {
                if (checkUp(checker.getPosition(), player)
                    || checkLeft(checker.getPosition(), player)
                    || checkDown(checker.getPosition(), player)
                    || checkUpLeft(checker.getPosition(), player)
                    || checkDownLeft(checker.getPosition(), player)) {
                    moves.push_back(checker.getPosition());
                }
                continue;
            }

            // If the checker is in frame-row #4, check these directions:
            if (i != 0 && j == 0) {
                if (checkUpRight(checker.getPosition(), player)
                    || checkUp(checker.getPosition(), player)
                    || checkRight(checker.getPosition(), player)
                    || checkDownRight(checker.getPosition(), player)
                    || checkDown(checker.getPosition(), player)) {
                    moves.push_back(checker.getPosition());
                }
                continue;
            }

            // If the checker is in open space, check all directions:
            if (checkRight(checker.getPosition(), player)
                || checkLeft(checker.getPosition(), player)
                || checkUp(checker.getPosition(), player)
                || checkDown(checker.getPosition(), player)
                || checkUpLeft(checker.getPosition(), player)
                || checkUpRight(checker.getPosition(), player)
                || checkDownLeft(checker.getPosition(), player)
                || checkDownRight(checker.getPosition(), player)) {
                moves.push_back(checker.getPosition());
                continue;
            }
        }
    }
    return moves;
};

bool NormalRuleset::checkRight(Checker::position pos, Player player) {
    bool enemyEncountered = false;

    for (int i = pos.col + 1; i <= getBoardClass().getSize() - 1; i++) {

        Checker nextChecker = getBoardClass().getBoard()[pos.row][i];

        // If the next checker to check is empty, return false:
        if (nextChecker.isEmpty()) {
            return false;
        }

        // If the next checker to check is an enemy, mark it and continue:
        if (player == Black && nextChecker.getVal() == 'O'
            || player == White && nextChecker.getVal() == 'X') {
            enemyEncountered = true;
            continue;
        }

        // If the next checker to check is yours, return yes if there
        // was an encounter with an enemy beforehand.
        if (player == Black && nextChecker.getVal() == 'X'
            || player == White && nextChecker.getVal() == 'O') {
            return enemyEncountered;
        }
    }

    return false;
}

bool NormalRuleset::checkDown(Checker::position pos, Player player) {
    bool enemyEncountered = false;

    for (int i = pos.row + 1; i <= getBoardClass().getSize() - 1; i++) {

        Checker nextChecker = getBoardClass().getBoard()[i][pos.col];

        // If the next checker to check is empty, return false:
        if (nextChecker.isEmpty()) {
            return false;
        }

        // If the next checker to check is an enemy, mark it and continue:
        if (player == Black && nextChecker.getVal() == 'O'
            || player == White && nextChecker.getVal() == 'X') {
            enemyEncountered = true;
            continue;
        }

        // If the next checker to check is yours, return yes if there
        // was an encounter with an enemy beforehand.
        if (player == Black && nextChecker.getVal() == 'X'
            || player == White && nextChecker.getVal() == 'O') {
            return enemyEncountered;
        }
    }

    return false;
}

bool NormalRuleset::checkUp(Checker::position pos, Player player) {
    bool enemyEncountered = false;

    for (int i = pos.row - 1; i >= 0; i--) {
        Checker nextChecker = getBoardClass().getBoard()[i][pos.col];

        // If the next checker to check is empty, return false:
        if (nextChecker.isEmpty()) {
            return false;
        }

        // If the next checker to check is an enemy, mark it and continue.
        if (player == Black && nextChecker.getVal() == 'O'
            || player == White && nextChecker.getVal() == 'X') {
            enemyEncountered = true;
            continue;
        }

        // If the next checker to check is yours, return yes if there
        // was an encounter with an enemy beforehand.
        if (player == Black && nextChecker.getVal() == 'X'
            || player == White && nextChecker.getVal() == 'O') {
            return enemyEncountered;
        }
    }

    return false;
}

bool NormalRuleset::checkLeft(Checker::position pos, Player player) {
    bool enemyEncountered = false;

    for (int i = pos.col - 1; i >= 0; i--) {
        Checker nextChecker = getBoardClass().getBoard()[pos.row][i];

        // If the next checker to check is empty, return false:
        if (nextChecker.isEmpty()) {
            return false;
        }

        // If the next checker to check is an enemy, mark it and
        // continue:
        if (player == Black && nextChecker.getVal() == 'O'
            || player == White && nextChecker.getVal() == 'X') {
            enemyEncountered = true;
            continue;
        }

        // If the next checker to check is yours, return yes if there
        // was an encounter with an enemy beforehand.
        if (player == Black && nextChecker.getVal() == 'X'
            || player == White && nextChecker.getVal() == 'O') {
            return enemyEncountered;
        }
    }

    return false;
}

bool NormalRuleset::checkUpLeft(Checker::position pos, Player player) {
    int j = pos.col - 1;
    bool enemyEncountered = false;

    for (int i = pos.row - 1; i >= 0; i--) {
        Checker nextChecker = getBoardClass().getBoard()[i][j];

        // If the next checker to check is empty, return false:
        if (nextChecker.isEmpty()) {
            return false;
        }

        // If the next checker to check is an enemy, mark it and continue:
        if (player == Black && nextChecker.getVal() == 'O'
            || player == White && nextChecker.getVal() == 'X') {
            enemyEncountered = true;
            if (j == 0) {
                return false;
            }
            if (j > 0) {
                j--;
            }
            continue;
        }

        // If the next checker to check is yours, return yes if there
        // was an encounter with an enemy beforehand.
        if (player == Black && nextChecker.getVal() == 'X'
            || player == White && nextChecker.getVal() == 'O') {
            return enemyEncountered;
        }
    }

    return false;
}

bool NormalRuleset::checkUpRight(Checker::position pos, Player player) {
    int j = pos.col + 1;
    bool enemyEncountered = false;

    for (int i = pos.row - 1; i >= 0; i--) {
        Checker nextChecker = getBoardClass().getBoard()[i][j];

        // If the next checker to check is empty, return false:
        if (nextChecker.isEmpty()) {
            return false;
        }

        // If the next checker to check is an enemy, mark it and continue:
        if (player == Black && nextChecker.getVal() == 'O'
            || player == White && nextChecker.getVal() == 'X') {
            enemyEncountered = true;
            if (j == getBoardClass().getSize() - 1) {
                return false;
            }
            if (j < getBoardClass().getSize() - 1) {
                j++;
            }
            continue;
        }

        // If the next checker to check is yours, return yes if there
        // was an encounter with an enemy beforehand.
        if (player == Black && nextChecker.getVal() == 'X'
            || player == White && nextChecker.getVal() == 'O') {
            return enemyEncountered;
        }
    }

    return false;
}

bool NormalRuleset::checkDownLeft(Checker::position pos, Player player) {
    int j = pos.col - 1;
    bool enemyEncountered = false;

    for (int i = pos.row + 1; i <= getBoardClass().getSize() - 1; i++) {
        Checker nextChecker = getBoardClass().getBoard()[i][j];

        if (j == 0 && !enemyEncountered) {
            break;
        }

        // If the next checker to check is empty, return false:
        if (nextChecker.isEmpty()) {
            return false;
        }

        // If the next checker to check is an enemy, mark it and continue:
        if (player == Black && nextChecker.getVal() == 'O'
            || player == White && nextChecker.getVal() == 'X') {
            enemyEncountered = true;
            if (j == 0) {
                return false;
            }
            if (j > 0) {
                j--;
            }
            continue;
        }

        // If the next checker to check is yours, return yes if there
        // was an encounter with an enemy beforehand.
        if (player == Black && nextChecker.getVal() == 'X'
            || player == White && nextChecker.getVal() == 'O') {
            return enemyEncountered;
        }
    }

    return false;
}

bool NormalRuleset::checkDownRight(Checker::position pos, Player player) {
    int j = pos.col + 1;
    bool enemyEncountered = false;

    for (int i = pos.row + 1; i <= getBoardClass().getSize() - 1; i++) {
        Checker nextChecker = getBoardClass().getBoard()[i][j];

        if (j == getBoardClass().getSize() - 1 && !enemyEncountered) {
            break;
        }

        // If the next checker to check is empty, return false:
        if (nextChecker.isEmpty()) {
            return false;
        }

        // If the next checker to check is an enemy, mark it and continue:
        if (player == Black && nextChecker.getVal() == 'O'
            || player == White && nextChecker.getVal() == 'X') {
            enemyEncountered = true;
            if (j == 0) {
                return false;
            }
            if (j < getBoardClass().getSize() - 1) {
                j++;
            }
            continue;
        }

        // If the next checker to check is yours, return yes if there
        // was an encounter with an enemy beforehand.
        if (player == Black && nextChecker.getVal() == 'X'
            || player == White && nextChecker.getVal() == 'O') {
            return enemyEncountered;
        }
    }

    return false;
}
