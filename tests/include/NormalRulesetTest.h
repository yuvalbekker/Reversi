#ifndef REVERSI_NORMALRULESETTEST_H
#define REVERSI_NORMALRULESETTEST_H

#include "../../include/Checker.h"
#include <gtest/gtest.h>
#include "../../include/NormalRuleset.h"

// This test fixture tests the NormalRuleset class, especially
// calculating the right moves for a player.
class NormalRulesetTest : public testing::Test {

public:

    /**
    * A SetUp routine for NormalRulesetTest.
    */
    virtual void SetUp() {

        // Create a new board with size 8 on the heap:
        b = new Board(8);

        // Create a Logic class with normal rules on the heap:
        rules = new NormalRuleset(b);
    }

    /**
    * A TearDown routine for NormalRulesetTest.
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

#endif //REVERSI_NORMALRULESETTEST_H
