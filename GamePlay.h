//Yuval Bekker
//311254585

#ifndef REVERSE_GAMEPLAY_H
#define REVERSE_GAMEPLAY_H


class GamePlay {
public:
    /**
    * The constructor.
     * @param ruwNumber
     * @param columnNumber
    */
    GamePlay(int ruwNumber, int columnNumber);

    /**
    * The constructor.
    */
    GamePlay();

    /**
    * The destructor.
    */
    ~GamePlay();

    /**
    * Returns the row number.
     * @return int
    */
    int row();

    /**
    * Returns the column number.
     * @return int
    */
    int column();

    /**
    * Updates the row number.
     * @param row
    */
    void setRow(int row);

    /**
    * Updates the column number.
     * @param column
    */
    void setColumn(int column);

    /**
    * == operator overload.
     * @param play
     * @return bool
    */
    bool operator==(GamePlay play);

private:
    int rowNum;
    int columnNum;
};


#endif //REVERSE_GAMEPLAY_H
