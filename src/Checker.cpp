#include <sstream>
#include "../include/Checker.h"

using namespace std;

Checker::Checker() {

    //Initialize the checker:
    this->setEmpty();
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

string Checker::getSringPosition() {
    string strPosition;
    stringstream ss;
    ss << this->getPosition().row;
    strPosition = ss.str();
    strPosition +=" ";
    ss << this->getPosition().col;
    strPosition = ss.str();
    return strPosition;

}
