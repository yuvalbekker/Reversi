//Yuval Bekker
//311254585

#include "RowOccupationContainer.h"

RowOccupationContainer::RowOccupationContainer() {

}

RowOccupationContainer::RowOccupationContainer(GamePlay occupationCell) {
    this->occupationPlayCell = occupationCell;
    this->cellsToOccupy = new vector<GamePlay>;
}

vector<GamePlay> *RowOccupationContainer::getCells() {
    return this->cellsToOccupy;
}

GamePlay RowOccupationContainer::getOccupaiedCell() {
    return this->occupationPlayCell;
}

void RowOccupationContainer::addCellToOccupy(GamePlay play) {
    this->getCells()->push_back(play);
}