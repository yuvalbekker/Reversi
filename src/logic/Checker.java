package logic;

public class Checker {
    private Position pos;
    private char val;

    public Checker() {
        this.pos = new Position(0, 0);
        this.setEmpty();
    }

    // Methods

    public char getVal() {
        return this.val;
    }

    public void setX() {
        this.val = 'X';
    }

    public void setO() {
        this.val = 'O';
    }

    private void setEmpty() {
        val = ' ';
    }

    public boolean isEmpty() {
        return (this.val == ' ');
    }

    public void setPosition(int row, int col) {
        this.pos.row = row;
        this.pos.col = col;
    }

    public Position getPosition() {
        return this.pos;
    }
}
