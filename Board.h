//Yuval Bekker
//311254585


#ifndef REVERSE_BOARD_H
#define REVERSE_BOARD_H

#include <vector>
#include "GamePlay.h"
#include "RowOccupationContainer.h"

using namespace std;

class Board {

public:
    //static const int rows = 8;
    //static const int columns = 8;
#ifndef ENUMAPPSTATE_H
#define ENUMAPPSTATE_H
    /**
 * Types of players enum.
*/
    enum PlayersType {
        Black, White, None
    };
#endif

    /**
    * Board Class Constructor.
     * @param numberOfRows
     * @param numberOfColumns
    */
    Board(int numberOfRows, int numberOfColumns);

    /**
    * Board Class Destructor.
    */
    ~Board();

    /**
    * Returns the player type of the input cell.
     * @return PlayersType
    */
    PlayersType getBoardCellContent(int rowNumber, int columnNumber);

    /**
    * Calculates the standard possible plays.
     * @param type
     * @return vector<RowOccupationContainer>
    */
    vector<RowOccupationContainer> *getStandardPossibleGamePlays(PlayersType type);

    /**
    * Returns true if the board is full, otherwise false.
     * @return bool
    */
    bool isFullBoard();

    /**
    * Returns true if the input type player has possible moves, otherwise false.
     * @param type
     * @return bool
    */
    bool hasStandardPossibleGamePlays(PlayersType type);

    /**
    * Applies int input play on the board.
     * @param type
     * @param play
     * @return bool
    */
    void makePlay(PlayersType type, RowOccupationContainer play);

    /**
    * Returns the number of disks ogf the input player type.
     * @param type
     * @return int
    */
    int getNumberOfDisks(PlayersType type);

    /**
    * Returns true if the input game play is out of the bounds of the board, otherwise false.
     * @param play
     * @return bool
    */
    bool isOutOfBounds(GamePlay play);

    int rows;
    int columns;

private:
    PlayersType **boardMatrix;

    /**
    * Initializes the Board.
    */
    void initializeBoard();

    vector<GamePlay> *whitePlayerPositions;
    vector<GamePlay> *blackPlayerPositions;

    /**
    * Update the two players type vectors.
    */
    void updateBoardOccupationStatus();
};

#endif //REVERSE_BOARD_H
