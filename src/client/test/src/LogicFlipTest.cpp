#include <gmock/gmock-matchers.h>
#include "client/include/Board.h"
#include "client/include/NormalRuleset.h"
#include "client/test/include/LogicFlipTest.h"

using namespace testing;

/**
* This test checks the flipping function on the left
* direction.
*/
TEST_F(LogicFlipTest, FlipLeft) {
    NormalRuleset &rulesRef = *(rules);

    // Declare two vectors:
    std::vector<char> correct, toCheck;
    int i = 0;

    // Place the pieces for the test:
    b->getBoard()[0][0].setX();
    for (i = 1; i < b->getSize() - 1; i++) {
        b->getBoard()[0][i].setO();
    }

    // Make a move:
    Checker::position someMove;
    someMove.row = 1;
    someMove.col = b->getSize();
    rulesRef.makeMove(someMove, Logic::Black);

    for (i = 0; i < b->getSize(); i++) {
         toCheck.push_back(b->getBoard()[0][i].getVal());
    }

    for (i = 0; i < b->getSize(); i++) {
        correct.push_back('X');
    }

    // Check if the pieces were flipped:
    EXPECT_THAT(correct, ContainerEq(toCheck));
}

/**
* This test checks the flipping function on the right
* direction.
*/
TEST_F(LogicFlipTest, FlipRight) {
    NormalRuleset &rulesRef = *(rules);

    // Declare two vectors:
    std::vector<char> correct, toCheck;
    int i = 0;

    // Place the pieces for the test:
    b->getBoard()[0][b->getSize() - 1].setX();
    for (i = 0; i < b->getSize() - 1; i++) {
        b->getBoard()[0][i].setO();
    }

    // Make a move:
    Checker::position someMove;
    someMove.row = 1;
    someMove.col = 1;
    rulesRef.makeMove(someMove, Logic::Black);

    for (i = 0; i < b->getSize(); i++) {
        toCheck.push_back(b->getBoard()[0][i].getVal());
    }

    for (i = 0; i < b->getSize(); i++) {
        correct.push_back('X');
    }

    // Check if the pieces were flipped:
    EXPECT_THAT(correct, ContainerEq(toCheck));
}

/**
* This test checks the flipping function on the down
* direction.
*/
TEST_F(LogicFlipTest, FlipDown) {
    NormalRuleset &rulesRef = *(rules);

    // Declare two vectors:
    std::vector<char> correct, toCheck;
    int i = 0;

    // Place the pieces for the test:
    b->getBoard()[b->getSize() - 1][3].setX();
    for (i = 1; i < b->getSize() - 1; i++) {
        b->getBoard()[i][3].setO();
    }

    // Make a move:
    Checker::position someMove;
    someMove.row = 1;
    someMove.col = 4;
    rulesRef.makeMove(someMove, Logic::Black);

    for (i = 0; i < b->getSize(); i++) {
        toCheck.push_back(b->getBoard()[i][3].getVal());
    }

    for (i = 0; i < b->getSize(); i++) {
        correct.push_back('X');
    }

    // Check if the pieces were flipped:
    EXPECT_THAT(correct, ContainerEq(toCheck));
}

/**
* This test checks the flipping function on the up
* direction.
*/
TEST_F(LogicFlipTest, FlipUp) {
    NormalRuleset &rulesRef = *(rules);

    // Declare two vectors:
    std::vector<char> correct, toCheck;
    int i = 0;

    // Place the pieces for the test:
    b->getBoard()[0][0].setX();
    for (i = 1; i < b->getSize() - 1; i++) {
        b->getBoard()[i][0].setO();
    }

    // Make a move:
    Checker::position someMove;
    someMove.row = b->getSize();
    someMove.col = 1;
    rulesRef.makeMove(someMove, Logic::Black);

    for (i = 0; i < b->getSize(); i++) {
        toCheck.push_back(b->getBoard()[i][0].getVal());
    }

    for (i = 0; i < b->getSize(); i++) {
        correct.push_back('X');
    }

    // Check if the pieces were flipped:
    EXPECT_THAT(correct, ContainerEq(toCheck));
}

/**
* This test checks the flipping function on the down-right
* direction.
*/
TEST_F(LogicFlipTest, FlipDownRight) {
    NormalRuleset &rulesRef = *(rules);

    // Declare two vectors:
    std::vector<char> correct, toCheck;
    int i = 0, j = 0;

    // Place the pieces for the test:
    for (i = b->getSize() - 1; i > 0; i--) {
        if (j == b->getSize() - 1) {
            break;
        }
        b->getBoard()[i][j].setO();
        j++;
    }
    b->getBoard()[b->getSize() - 1][0].setX();

    // Make a move:
    Checker::position someMove;
    someMove.row = 1;
    someMove.col = b->getSize();
    rulesRef.makeMove(someMove, Logic::Black);

    j = 0;
    for (i = b->getSize() - 1; i >= 0; i--) {
        if (j == b->getSize()) {
            break;
        }
        toCheck.push_back(b->getBoard()[i][j].getVal());
        j++;
    }

    for (i = 0; i < b->getSize(); i++) {
        correct.push_back('X');
    }

    // Check if the pieces were flipped:
    EXPECT_THAT(correct, ContainerEq(toCheck));
}

/**
* This test checks the flipping function on the up-right
* direction.
*/
TEST_F(LogicFlipTest, FlipUpRight) {
    NormalRuleset &rulesRef = *(rules);

    // Declare two vectors:
    std::vector<char> correct, toCheck;
    int i = 0, j = b->getSize() - 1;

    // Place the pieces for the test:
    for (i = 0; i < b->getSize() - 1; i++) {
        if (j == 0) {
            break;
        }
        b->getBoard()[i][j].setO();
        j--;
    }
    b->getBoard()[0][b->getSize() - 1].setX();

    // Make a move:
    Checker::position someMove;
    someMove.row = b->getSize();
    someMove.col = 1;
    rulesRef.makeMove(someMove, Logic::Black);

    j = b->getSize() - 1;
    for (i = 0; i <= b->getSize() - 1; i++) {
        if (j == -1) {
            break;
        }
        toCheck.push_back(b->getBoard()[i][j].getVal());
        j--;
    }

    for (i = 0; i < b->getSize(); i++) {
        correct.push_back('X');
    }

    // Check if the pieces were flipped:
    EXPECT_THAT(correct, ContainerEq(toCheck));
}

/**
* This test checks the flipping function on the down-left
* direction.
*/
TEST_F(LogicFlipTest, FlipDownLeft) {
    NormalRuleset &rulesRef = *(rules);

    // Declare two vectors:
    std::vector<char> correct, toCheck;
    int i = 0, j = b->getSize() - 1;

    // Place the pieces for the test:
    for (i = b->getSize() - 1; i > 0; i--) {
        if (j == 0) {
            break;
        }
        b->getBoard()[i][j].setO();
        j--;
    }
    b->getBoard()[b->getSize() - 1][b->getSize() - 1].setX();

    // Make a move:
    Checker::position someMove;
    someMove.row = 1;
    someMove.col = 1;
    rulesRef.makeMove(someMove, Logic::Black);

    j = b->getSize() - 1;
    for (i = b->getSize() - 1; i >= 0; i--) {
        if (j == -1) {
            break;
        }
        toCheck.push_back(b->getBoard()[i][j].getVal());
        j--;
    }

    for (i = 0; i < b->getSize(); i++) {
        correct.push_back('X');
    }

    // Check if the pieces were flipped:
    EXPECT_THAT(correct, ContainerEq(toCheck));
}

/**
* This test checks the flipping function on the up-left
* direction.
*/
TEST_F(LogicFlipTest, FlipUpLeft) {
    NormalRuleset &rulesRef = *(rules);

    // Declare two vectors:
    std::vector<char> correct, toCheck;
    int i = 0, j = 0;

    // Place the pieces for the test:
    for (i = 0; i < b->getSize() - 1; i++) {
        if (j == b->getSize() - 1) {
            break;
        }
        b->getBoard()[i][j].setO();
        j++;
    }
    b->getBoard()[0][0].setX();

    // Make a move:
    Checker::position someMove;
    someMove.row = b->getSize();
    someMove.col = b->getSize();
    rulesRef.makeMove(someMove, Logic::Black);

    j = 0;
    for (i = 0; i <= b->getSize() - 1; i++) {
        if (j == b->getSize()) {
            break;
        }
        toCheck.push_back(b->getBoard()[i][j].getVal());
        j++;
    }

    for (i = 0; i < b->getSize(); i++) {
        correct.push_back('X');
    }

    // Check if the pieces were flipped:
    EXPECT_THAT(correct, ContainerEq(toCheck));
}