#ifndef REVERSI_NORMALRULESETTEST_H
#define REVERSI_NORMALRULESETTEST_H

#include <Checker.h>
#include <gtest/gtest.h>
#include <NormalRuleset.h>

class NormalRulesetTest : public testing::Test {

// C'tor:
public:

// SetUp and TearDown:
    virtual void SetUp() {

        // Create a new board with size 8 on the heap:
        b = new Board(8);

        // Create a Logic class with normal rules on the heap:
        rules = new NormalRuleset(b);
    }

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
