//Yuval Bekker
//311254585

#include <vector>
#include "GamePlay.h"

using namespace std;

#ifndef REVERSE_ROWOCCUPATIONCONTAINER_H
#define REVERSE_ROWOCCUPATIONCONTAINER_H


class RowOccupationContainer {
public:
    /**
     * The constructor.
    */
    RowOccupationContainer();

    /**
     * The constructor.
     * @param occupationCell
    */
    RowOccupationContainer(GamePlay occupationCell);

    /**
     * Returns the occupied cell.
     * @return GamePlay
    */
    GamePlay getOccupaiedCell();

    /**
     * Returns vector of the cells to occupy.
     * @return vector<GamePlay> *
    */
    vector<GamePlay> *getCells();
    /**
     * Adds a new cell to occupy.
     * @par play
    */
    void addCellToOccupy(GamePlay play);

private:
    GamePlay occupationPlayCell;
    vector<GamePlay> *cellsToOccupy;

};


#endif //REVERSE_ROWOCCUPATIONCONTAINER_H
