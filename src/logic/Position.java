package logic;

public class Position {
    public int row;
    public int col;

    /**
     * This is a c'tor for a position class.
     */
    public Position(int row, int col) {
        this.row = row;
        this.col = col;
    }

    public void setPosition(int row, int col) {
        this.row = row;
        this.col = col;
    }

    public Position getPosition() {
        return this;
    }
}