// Name: Eyal Lantzman ID: 205502818

#ifndef FLOW_H
#define FLOW_H

#include "Logic.h"

class Flow {
public:

//Constructor:

    /**
    * A constructor for flow. It gets a reference to a Logic instance.
    */
    Flow(Logic &l);


// Members:

private:
    Logic &logic;
    bool blackMovesEnded;
    bool whiteMovesEnded;

// Functions:

private:

    /**
    * This function returns the # of white
    * checkers on the board.
    */
    int countWhite() const;

    /**
    * This function returns the # of black
    * checkers on the board.
    */
    int countBlack() const;

    /**
    * This function initiates a turn for Black.
    */
    void playBlack();

    /**
    * This function initiates a turn for White.
    */
    void playWhite();

public:

    /**
    * This function runs the game flow.
    */
    void play();
};


#endif //EX1_FLOW_H
