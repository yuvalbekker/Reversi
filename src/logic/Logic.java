package logic;

import logic.Board;
import logic.Checker;
import logic.Position;

import java.util.ArrayList;

public abstract class Logic {

    public enum Player {
        White, Black
    }

    ;

    protected Player p;
    protected Board boardClass;
    protected ArrayList<Position> moves;

    public Logic(Board b) {
        this.boardClass = b;
        this.moves = new ArrayList<Position>();
    }

    // Methods

    public Board getBoardClass() {
        return boardClass;
    }

    public abstract ArrayList<Position> calcPossibleMoves(Player player);

    public abstract boolean checkRight(Position pos, Player player);

    public abstract boolean checkLeft(Position pos, Player player);

    public abstract boolean checkUp(Position pos, Player player);

    public abstract boolean checkDown(Position pos, Player player);

    public abstract boolean checkUpRight(Position pos, Player player);

    public abstract boolean checkUpLeft(Position pos, Player player);

    public abstract boolean checkDownRight(Position pos, Player player);

    public abstract boolean checkDownLeft(Position pos, Player player);

    public void makeMove(Position pos, Player player) {

        // Decrement the given position to fit the array (index starting from 0):
        pos.row--;
        pos.col--;

        // Get the piece in this position:
        Checker checker = boardClass.getBoard()[pos.row][pos.col];

        // Place the piece in the given position:

        if (player == Player.Black) {
            checker.setX();
        }

        if (player == Player.White) {
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
        if (pos.row == boardClass.getSize() - 1 && pos.col == 0) {
            flipRight(checker.getPosition(), player);
            flipUp(checker.getPosition(), player);
            flipUpRight(checker.getPosition(), player);
            return;
        }

        // If piece is in corner #3, flip these directions
        if (pos.row == 0 && pos.col == boardClass.getSize() - 1) {
            flipLeft(checker.getPosition(), player);
            flipDown(checker.getPosition(), player);
            flipDownLeft(checker.getPosition(), player);
            return;
        }

        // If piece is in corner #4, flip these directions
        if (pos.row == boardClass.getSize() - 1 && pos.col == boardClass.getSize() - 1) {
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
        if (pos.row != 0 && pos.col == boardClass.getSize() - 1) {
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

    public void flipRight(Position pos, Player player) {
        int i = 0;

        if (player == Player.Black) {

            // A vector to store possible flips:
            ArrayList<Position> vec = new ArrayList<Position>();
            boolean enemyEncountered = false;

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
                            getBoardClass().getBoard()[vec.get(a).row][vec.get(a).col].setX();
                        }
                        return;
                    } else {
                        return;
                    }
                }

                // If the next piece is an enemy, store it and continue.
                if (getBoardClass().getBoard()[pos.row][i].getVal() == 'O') {
                    enemyEncountered = true;
                    Position p = new Position(0, 0);
                    p.row = pos.row;
                    p.col = i;
                    vec.add(p);
                    continue;
                }
            }
        }

        // Similarly for white:
        if (player == Player.White) {
            ArrayList<Position> vec = new ArrayList<Position>();
            boolean enemyEncountered = false;

            for (i = pos.col + 1; i <= getBoardClass().getSize() - 1; i++) {
                if (getBoardClass().getBoard()[pos.row][i].isEmpty()) {
                    return;
                }

                if (getBoardClass().getBoard()[pos.row][i].getVal() == 'O') {
                    if (enemyEncountered) {
                        int a = 0;
                        for (a = 0; a < vec.size(); a++) {
                            getBoardClass().getBoard()[vec.get(a).row][vec.get(a).col].setO();
                        }
                        return;
                    } else {
                        return;
                    }
                }

                if (getBoardClass().getBoard()[pos.row][i].getVal() == 'X') {
                    enemyEncountered = true;
                    Position p = new Position(0, 0);
                    p.row = pos.row;
                    p.col = i;
                    vec.add(p);
                    continue;
                }
            }
        }
    }

    public void flipDown(Position pos, Player player) {
        int i = 0;

        if (player == Player.Black) {

            // A vector to store possible flips:
            ArrayList<Position> vec = new ArrayList<Position>();
            boolean enemyEncountered = false;

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
                            getBoardClass().getBoard()[vec.get(a).row][vec.get(a).col].setX();
                        }
                        return;
                    } else {
                        return;
                    }
                }

                // If the next piece is an enemy, store it and continue.
                if (getBoardClass().getBoard()[i][pos.col].getVal() == 'O') {
                    enemyEncountered = true;
                    Position p = new Position(0, 0);
                    p.row = i;
                    p.col = pos.col;
                    vec.add(p);
                    continue;
                }
            }
        }

        // Similarly for white:
        if (player == Player.White) {
            ArrayList<Position> vec = new ArrayList<Position>();
            boolean enemyEncountered = false;

            for (i = pos.row + 1; i <= getBoardClass().getSize() - 1; i++) {
                if (getBoardClass().getBoard()[i][pos.col].isEmpty()) {
                    return;
                }

                if (getBoardClass().getBoard()[i][pos.col].getVal() == 'O') {
                    if (enemyEncountered) {
                        int a = 0;
                        for (a = 0; a < vec.size(); a++) {
                            getBoardClass().getBoard()[vec.get(a).row][vec.get(a).col].setO();
                        }
                        return;
                    } else {
                        return;
                    }
                }

                if (getBoardClass().getBoard()[i][pos.col].getVal() == 'X') {
                    enemyEncountered = true;
                    Position p = new Position(0, 0);
                    p.row = i;
                    p.col = pos.col;
                    vec.add(p);
                    continue;
                }
            }
        }
    }

    public void flipUp(Position pos, Player player) {
        int i = 0;

        if (player == Player.Black) {

            // A vector to store possible flips:
            ArrayList<Position> vec = new ArrayList<Position>();
            boolean enemyEncountered = false;

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
                            getBoardClass().getBoard()[vec.get(a).row][vec.get(a).col].setX();
                        }
                        return;
                    } else {
                        return;
                    }
                }

                // If the next piece is an enemy, store it and continue.
                if (getBoardClass().getBoard()[i][pos.col].getVal() == 'O') {
                    enemyEncountered = true;
                    Position p = new Position(0, 0);
                    p.row = i;
                    p.col = pos.col;
                    vec.add(p);
                    continue;
                }
            }
        }

        // Similarly for white:
        if (player == Player.White) {
            ArrayList<Position> vec = new ArrayList<Position>();
            boolean enemyEncountered = false;

            for (i = pos.row - 1; i >= 0; i--) {
                if (getBoardClass().getBoard()[i][pos.col].isEmpty()) {
                    return;
                }

                if (getBoardClass().getBoard()[i][pos.col].getVal() == 'O') {
                    if (enemyEncountered) {
                        int a = 0;
                        for (a = 0; a < vec.size(); a++) {
                            getBoardClass().getBoard()[vec.get(a).row][vec.get(a).col].setO();
                        }
                        return;
                    } else {
                        return;
                    }
                }

                if (getBoardClass().getBoard()[i][pos.col].getVal() == 'X') {
                    enemyEncountered = true;
                    Position p = new Position(0, 0);
                    p.row = i;
                    p.col = pos.col;
                    vec.add(p);
                    continue;
                }
            }
        }
    }

    public void flipLeft(Position pos, Player player) {
        int i = 0;

        if (player == Player.Black) {

            // A vector to store possible flips:
            ArrayList<Position> vec = new ArrayList<Position>();
            boolean enemyEncountered = false;

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
                            getBoardClass().getBoard()[vec.get(a).row][vec.get(a).col].setX();
                        }
                        return;
                    } else {
                        return;
                    }
                }

                // If the next piece is an enemy, store it and continue:
                if (getBoardClass().getBoard()[pos.row][i].getVal() == 'O') {
                    enemyEncountered = true;
                    Position p = new Position(0,0);
                    p.row = pos.row;
                    p.col = i;
                    vec.add(p);
                    continue;
                }
            }
        }

        // Similarly for white:
        if (player == Player.White) {
            ArrayList<Position> vec = new ArrayList<Position>();
            boolean enemyEncountered = false;

            for (i = pos.col - 1; i >= 0; i--) {
                if (getBoardClass().getBoard()[pos.row][i].isEmpty()) {
                    return;
                }

                if (getBoardClass().getBoard()[pos.row][i].getVal() == 'O') {
                    if (enemyEncountered) {
                        int a = 0;
                        for (a = 0; a < vec.size(); a++) {
                            getBoardClass().getBoard()[vec.get(a).row][vec.get(a).col].setO();
                        }
                        return;
                    } else {
                        return;
                    }
                }

                if (getBoardClass().getBoard()[pos.row][i].getVal() == 'X') {
                    enemyEncountered = true;
                    Position p = new Position(0,0);
                    p.row = pos.row;
                    p.col = i;
                    vec.add(p);
                    continue;
                }
            }
        }
    }

    public void flipUpLeft(Position pos, Player player) {
        int j = pos.col - 1;

        // A vector to store possible flips:
        ArrayList<Position> vec = new ArrayList<Position>();
        boolean enemyEncountered = false;

        for (int i = pos.row - 1; i >= 0; i--) {
            Checker nextChecker = getBoardClass().getBoard()[i][j];

            if (nextChecker.isEmpty()) {
                return;
            }

            // If the next piece to check is your own piece, check
            // if there were enemy pieces before. If so, flip them,
            // if not, return.
            if (player == Player.Black && nextChecker.getVal() == 'X'
                    || player == Player.White && nextChecker.getVal() == 'O') {
                if (j == 0 && !enemyEncountered) {
                    return;
                }
                if (enemyEncountered) {
                    int a = 0;
                    for (a = 0; a < vec.size(); a++) {
                        if (player == Player.Black) {
                            getBoardClass().getBoard()[vec.get(a).row][vec.get(a).col].setX();
                        }
                        if (player == Player.White) {
                            getBoardClass().getBoard()[vec.get(a).row][vec.get(a).col].setO();
                        }
                    }
                    return;
                } else {
                    return;
                }
            }

            // If the next piece is an enemy, store it and continue:
            if (player == Player.Black && nextChecker.getVal() == 'O'
                    || player == Player.White && nextChecker.getVal() == 'X') {
                enemyEncountered = true;
                Position p = new Position(0, 0);
                p.row = i;
                p.col = j;
                vec.add(p);
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

    public void flipUpRight(Position pos, Player player) {
        int j = pos.col + 1;

        // A vector to store possible flips:
        ArrayList<Position> vec = new ArrayList<Position>();
        boolean enemyEncountered = false;

        for (int i = pos.row - 1; i >= 0; i--) {
            Checker nextChecker = getBoardClass().getBoard()[i][j];

            // If the next piece to check is empty, return:
            if (nextChecker.isEmpty()) {
                return;
            }

            // If the next piece to check is your own piece, check
            // if there were enemy pieces before. If so, flip them,
            // if not, return.
            if (player == Player.Black && nextChecker.getVal() == 'X'
                    || player == Player.White && nextChecker.getVal() == 'O') {
                if (j == 0 && !enemyEncountered) {
                    return;
                }
                if (enemyEncountered) {
                    int a = 0;
                    for (a = 0; a < vec.size(); a++) {
                        if (player == Player.Black) {
                            getBoardClass().getBoard()[vec.get(a).row][vec.get(a).col].setX();
                        }
                        if (player == Player.White) {
                            getBoardClass().getBoard()[vec.get(a).row][vec.get(a).col].setO();
                        }
                    }
                    return;
                } else {
                    return;
                }
            }

            // If the next piece to check is an enemy, store it and continue:
            if (player == Player.Black && nextChecker.getVal() == 'O'
                    || player == Player.White && nextChecker.getVal() == 'X') {
                if (j == getBoardClass().getSize() - 1 && enemyEncountered) {
                    return;
                }
                enemyEncountered = true;
                Position p = new Position(0, 0);
                p.row = i;
                p.col = j;
                vec.add(p);
                if (j < getBoardClass().getSize() - 1) {
                    j++;
                }
                continue;
            }
        }
    }

    public void flipDownLeft(Position pos, Player player) {

        // Decrement column position:
        int j = pos.col - 1;

        // A vector to store possible flips:
        ArrayList<Position> vec = new ArrayList<Position>();
        boolean enemyEncountered = false;

        // Increment the row by each loop:
        for (int i = pos.row + 1; i <= getBoardClass().getSize() - 1; i++) {
            Checker nextChecker = getBoardClass().getBoard()[i][j];

            // If the next piece to check is empty, return:
            if (nextChecker.isEmpty()) {
                return;
            }

            // If the next piece to check is your own piece, check
            // if there were enemy pieces before. If so, flip them,
            // if not, return.
            if (player == Player.Black && nextChecker.getVal() == 'X'
                    || player == Player.White && nextChecker.getVal() == 'O') {
                if (j == 0 && !enemyEncountered) {
                    return;
                }
                if (enemyEncountered) {
                    int a = 0;
                    for (a = 0; a < vec.size(); a++) {
                        if (player == Player.Black) {
                            getBoardClass().getBoard()[vec.get(a).row][vec.get(a).col].setX();
                        }
                        if (player == Player.White) {
                            getBoardClass().getBoard()[vec.get(a).row][vec.get(a).col].setO();
                        }
                    }
                    return;
                } else {
                    return;
                }
            }

            //If the next piece is an enemy piece, store it and continue:
            if (player == Player.Black && nextChecker.getVal() == 'O'
                    || player == Player.White && nextChecker.getVal() == 'X') {
                enemyEncountered = true;
                Position p = new Position(0, 0);
                p.row = i;
                p.col = j;
                vec.add(p);
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

    public void flipDownRight(Position pos, Player player) {
        int j = pos.col + 1;

        // A vector to store possible flips:
        ArrayList<Position> vec = new ArrayList<Position>();
        boolean enemyEncountered = false;

        for (int i = pos.row + 1; i <= getBoardClass().getSize() - 1; i++) {
            Checker nextChecker = getBoardClass().getBoard()[i][j];

            // If the next piece is empty, return:
            if (nextChecker.isEmpty()) {
                return;
            }

            // If the next piece to check is your own piece, check
            // if there were enemy pieces before. If so, flip them,
            // if not, return.
            if (player == Player.Black && nextChecker.getVal() == 'X'
                    || player == Player.White && nextChecker.getVal() == 'O') {
                if (j == 0 && !enemyEncountered) {
                    return;
                }
                if (enemyEncountered) {
                    int a = 0;
                    for (a = 0; a < vec.size(); a++) {
                        if (player == Player.Black) {
                            getBoardClass().getBoard()[vec.get(a).row][vec.get(a).col].setX();
                        }
                        if (player == Player.White) {
                            getBoardClass().getBoard()[vec.get(a).row][vec.get(a).col].setO();
                        }
                    }
                    return;
                } else {
                    return;
                }
            }

            // If the next piece is an enemy, store it and continue.
            if (player == Player.Black && nextChecker.getVal() == 'O'
                    || player == Player.White && nextChecker.getVal() == 'X') {
                if (j == getBoardClass().getSize() - 1 && enemyEncountered) {
                    return;
                }
                enemyEncountered = true;
                Position p = new Position(0, 0);
                p.row = i;
                p.col = j;
                vec.add(p);
                if (j < getBoardClass().getSize() - 1) {
                    j++;
                }
                continue;
            }
        }
    }
}
