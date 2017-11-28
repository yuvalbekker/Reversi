#include <gmock/gmock-matchers.h>
#include "gtest/gtest.h"
#include "Board.h"
#include "NormalRuleset.h"
#include "include/NormalRulesetTest.h"

using namespace testing;

TEST_F(NormalRulesetTest, StartingPositions) {
    NormalRuleset &rulesRef = *(rules);
    std::vector<Checker::position> correct;
    Checker::position pos1;
    pos1.row = 2;
    pos1.col = 3;
    Checker::position pos2;
    pos2.row = 3;
    pos2.col = 2;
    Checker::position pos3;
    pos3.row = 4;
    pos3.col = 5;
    Checker::position pos4;
    pos4.row = 5;
    pos4.col = 4;
    correct.push_back(pos1);
    correct.push_back(pos2);
    correct.push_back(pos3);
    correct.push_back(pos4);

    int i = 0;

    // Get possible moves:
    std::vector<Checker::position> &moves = rulesRef.calcPossibleMoves(Logic::Black);

    ASSERT_THAT(moves, SizeIs(correct.size()));

    // Put the positions in an array:
    std::vector<int> correctVector;
    std::vector<int> toTestVector;

    for (i = 0; i < correct.size(); i++) {
        correctVector.push_back(correct[i].row);
        correctVector.push_back(correct[i].col);
    }

    for (i = 0; i < moves.size(); i++) {
        toTestVector.push_back(moves[i].row);
        toTestVector.push_back(moves[i].col);
    }

    EXPECT_THAT(correctVector, ContainerEq(toTestVector));
}

/* Suggestions for more:
 * - Check possible moves after a few moves
 * - Check size of possible moves for the entire game
 * - Check the board itself and how it looks after a few plays
 * - Maybe run a whole game and see if the outcome matches.
 */