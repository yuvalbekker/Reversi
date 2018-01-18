package logic;

import javafx.scene.layout.GridPane;
import javafx.scene.paint.Color;
import javafx.scene.shape.Circle;
import javafx.scene.shape.Rectangle;

public class Board extends GridPane {
    private int size;
    private Checker[][] board;
    private Color firstPlayerColor;
    private Color secondPlayerColor;
    private Color cellColor;

    public Board(int size, Color firstPlayer, Color secondPlayer) {
        firstPlayerColor = firstPlayer;
        secondPlayerColor = secondPlayer;
        String color = "#F5F6CE";
        cellColor = Color.web(color);
        this.size = size;
        int i = 0, j = 0;

        // Initialize the board:
        board = new Checker[size][size];
        for (i = 0; i < size; i++) {
            for (j = 0; j < size; j++) {
                board[i][j] = new Checker();
                board[i][j].setPosition(i, j);
            }
        }

        // Initialize B&W positions:
        board[(getSize() / 2) - 1][(getSize() / 2) - 1].setX();
        board[getSize() / 2][getSize() / 2].setX();
        board[(getSize() / 2) - 1][getSize() / 2].setO();
        board[getSize() / 2][(getSize() / 2) - 1].setO();
        drawEmptyBoard();
    }


    // Getters

    public Checker[][] getBoard() {
        return this.board;
    }

    public char getCheckerValueByIndices(int row, int col) {
        return this.board[row][col].getVal();
    }

    public int getSize() {
        return this.size;
    }

    // Methods

    public int countPlayersCheckers(char playerType) {
        int count = 0;

        // Go over the board and get the score count:
        for (int i = 0; i < this.size; i++) {
            for (int j = 0; j < this.size; j++) {
                if (this.board[i][j].getVal() == playerType) {
                    count++;
                }
            }
        }
        return count;
    }

    public char getColorSymbol(Color c) {
        if (c == this.firstPlayerColor) {
            return 'O';
        } else if (c == this.secondPlayerColor) {
            return 'X';
        }
        return ' ';
    }

    public void draw() {
        this.getChildren().clear();
        drawEmptyBoard();
        int height = (int) this.getPrefHeight();
        int width = (int) this.getPrefWidth();
        int cellHeight = height / this.size;
        int cellWidth = width / this.size;

        for (int i = 0; i < this.size; i++) {
            for (int j = 0; j < this.size; j++) {
                int cellValue = getCheckerValueByIndices(i, j);
                int minVal = Math.min(cellHeight, cellWidth);
                int circleRadius = minVal / 2;

                if (cellValue == 'X') {
                    this.add(new Circle(cellWidth, cellHeight, circleRadius, secondPlayerColor),j,i);
                } else if (cellValue == 'O') {
                    this.add(new Circle(cellWidth, cellHeight, circleRadius, firstPlayerColor), j, i);
                }
            }
        }
    }

    public void updateBoardDraw(int row, int col) {
        int height = (int) this.getPrefHeight();
        int width = (int) this.getPrefWidth();
        int cellHeight = height / this.size;
        int cellWidth = width / this.size;
        int cellValue = getCheckerValueByIndices(row, col);
        int minVal = Math.min(cellHeight, cellWidth);
        int circleRadius = minVal / 2;
        if (cellValue == 'X') {
            this.add(new Circle(cellWidth, cellHeight, circleRadius, secondPlayerColor), col, row);
        } else if (cellValue == 'O') {
            this.add(new Circle(cellWidth, cellHeight, circleRadius, firstPlayerColor), col, row);
        }
    }

    public void drawEmptyBoard() {
        this.getChildren().clear();
        int height = (int) this.getPrefHeight();
        int width = (int) this.getPrefWidth();
        int cellHeight = height / this.size;
        int cellWidth = width / this.size;
        for (int i = 0; i < this.size; i++) {
            for (int j = 0; j < this.size; j++) {
                Rectangle rectangle = new Rectangle(cellWidth - 1, cellHeight - 1, cellColor);
                rectangle.setStroke(Color.BLACK);
                this.add(rectangle, j, i);
            }
        }
    }
}
