#ifndef REVERSI_LOGICFLIPTEST_H
#define REVERSI_LOGICFLIPTEST_H

#include "../../include/Checker.h"
#include <gtest/gtest.h>
#include "../../include/NormalRuleset.h"

// This text fixture tests the Logic interface's flipping functions.
class LogicFlipTest : public testing::Test {

public:

    /**
    * A SetUp routine for LogicFlipTest.
    */
    virtual void SetUp() {

        // Create a new board with size 8 on the heap:
        b = new Board(8);

        // Empty the board:
        b->getBoard()[(b->getSize()/2) - 1][(b->getSize()/2) - 1].setEmpty();
        b->getBoard()[b->getSize()/2][b->getSize()/2].setEmpty();
        b->getBoard()[(b->getSize()/2) - 1][b->getSize()/2].setEmpty();
        b->getBoard()[b->getSize()/2][(b->getSize()/2) - 1].setEmpty();

        // Create a Logic class with normal rules on the heap:
        rules = new NormalRuleset(b);
    }

    /**
    * A TearDown routine for LogicFlipTest.
    */
    virtual void TearDown() {

        // Free the board and Logic classes:
        delete b;
        delete rules;
    }

// Members:
protected:
    Board *b;
    NormalRuleset *rules;
};

#endif //REVERSI_LOGICFLIPTEST_H