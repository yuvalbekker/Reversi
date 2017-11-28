// Name: Eyal Lantzman ID: 205502818

#include "Checker.h"

using namespace std;

Checker::Checker() {

    //Initialize the checker:

    this->setEmpty();
}

void Checker::print() const {
    cout << " " << val << " |";
}

char Checker::getVal() const {
    return val;
}

void Checker::setX() {
    val = 'X';
}

void Checker::setO() {
    val = 'O';
}

void Checker::setEmpty() {
    val = ' ';
}

bool Checker::isEmpty() const {
    return (val == ' ');
}

void Checker::setPosition(int row, int col) {
    pos.row = row;
    pos.col = col;
}

struct Checker::position Checker::getPosition() const {
    return pos;
}