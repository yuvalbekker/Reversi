#ifndef CHECKER_H
#define CHECKER_H

#include <iostream>

class Checker {

public:

// Definitions:
    struct position {
        int row;
        int col;
    };

// Constructor:
public:

    /**
    * This is a c'tor for checker.
    */
    Checker();

// Members:
private:
    char val;
    struct position pos;

// Functions:
public:
    /**
     * This is a getter for the checker's value.
     * @return char
     */
    char getVal() const;

    /**
     * This function sets the val to 'X' (Black).
     */
    void setX();

    /**
    * This function sets the val to 'O' (White).
    */
    void setO();

    /**
    * This functions sets an empty checker (for initialization).
    */
    void setEmpty();

    /**
     * This functions checks if the checker is empty.
     * @return bool
     */
    bool isEmpty() const;

    /**
     * This functions gets two integers as a position and sets the checkers'
     * position accordingly.
     * @param row
     * @param col
     */
    void setPosition(int row, int col);

    /**
     * This is a getter for the checker's position.
     * @return struct position
     */
    struct position getPosition() const;
};


#endif //CHECKER_H
