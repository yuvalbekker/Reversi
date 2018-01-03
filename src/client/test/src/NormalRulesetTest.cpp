#include <gmock/gmock-matchers.h>
#include "client/include/Board.h"
#include "client/include/NormalRuleset.h"
#include "client/test/include/NormalRulesetTest.h"

using namespace testing;

/**
* This test checks the calcPossibleMoves function straight
* at the first turn and makes sure they're correct.
*/
TEST_F(NormalRulesetTest, StartingPositionsPossibleMovesCalc) {
    NormalRuleset &rulesRef = *(rules);

    // This vector holds the correct possible moves
    // for black when starting the game:
    std::vector<Checker::position> correctPosVector;
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
    correctPosVector.push_back(pos1);
    correctPosVector.push_back(pos2);
    correctPosVector.push_back(pos3);
    correctPosVector.push_back(pos4);

    int i = 0;

    // Get possible moves from calcPossibleMoves and place it in the moves vector:
    std::vector<Checker::position> &moves = rulesRef.calcPossibleMoves(Logic::Black);

    ASSERT_THAT(moves, SizeIs(correctPosVector.size()));

    // Put the positions from the two vectors
    // in arrays, so we can compare them:
    std::vector<int> correctVector;
    std::vector<int> toTestVector;

    // Push the actual positions to a currentVector:
    for (i = 0; i < correctPosVector.size(); i++) {
        correctVector.push_back(correctPosVector[i].row);
        correctVector.push_back(correctPosVector[i].col);
    }

    // And to the toTestVector vector with what we got from calcPossibleMoves:
    for (i = 0; i < moves.size(); i++) {
        toTestVector.push_back(moves[i].row);
        toTestVector.push_back(moves[i].col);
    }

    // Check if correctVector and toTestVector have the same elements:
    EXPECT_THAT(correctVector, ContainerEq(toTestVector));
}

/**
* This test checks the calcPossibleMoves function throughout
* an entire game, and makes sure the result is correct.
*/
TEST_F(NormalRulesetTest, FullGamePossibleMovesCalc) {
    NormalRuleset &rulesRef = *(rules);

    // Declaring a temp position which will indicate
    // a certain move, and running an entire game,
    // while checking the possible moves are correct:
    Checker::position someMove;
    someMove.row = 5;
    someMove.col = 6;
    rulesRef.makeMove(someMove, Logic::Black);
    std::vector<Checker::position> &moves = rulesRef.calcPossibleMoves(Logic::White);
    ASSERT_THAT(moves, SizeIs(3));
    someMove.row = 4;
    someMove.col = 6;
    rulesRef.makeMove(someMove, Logic::White);
    moves = rulesRef.calcPossibleMoves(Logic::Black);
    ASSERT_THAT(moves, SizeIs(5));
    someMove.row = 3;
    someMove.col = 6;
    rulesRef.makeMove(someMove, Logic::Black);
    moves = rulesRef.calcPossibleMoves(Logic::White);
    ASSERT_THAT(moves, SizeIs(3));
    someMove.row = 6;
    someMove.col = 6;
    rulesRef.makeMove(someMove, Logic::White);
    moves = rulesRef.calcPossibleMoves(Logic::Black);
    ASSERT_THAT(moves, SizeIs(5));
    someMove.row = 7;
    someMove.col = 6;
    rulesRef.makeMove(someMove, Logic::Black);
    moves = rulesRef.calcPossibleMoves(Logic::White);
    ASSERT_THAT(moves, SizeIs(7));
    someMove.row = 7;
    someMove.col = 7;
    rulesRef.makeMove(someMove, Logic::White);
    moves = rulesRef.calcPossibleMoves(Logic::Black);
    ASSERT_THAT(moves, SizeIs(5));
    someMove.row = 7;
    someMove.col = 8;
    rulesRef.makeMove(someMove, Logic::Black);
    moves = rulesRef.calcPossibleMoves(Logic::White);
    ASSERT_THAT(moves, SizeIs(9));
    someMove.row = 8;
    someMove.col = 8;
    rulesRef.makeMove(someMove, Logic::White);
    moves = rulesRef.calcPossibleMoves(Logic::Black);
    ASSERT_THAT(moves, SizeIs(4));
    someMove.row = 4;
    someMove.col = 3;
    rulesRef.makeMove(someMove, Logic::Black);
    moves = rulesRef.calcPossibleMoves(Logic::White);
    ASSERT_THAT(moves, SizeIs(9));
    someMove.row = 8;
    someMove.col = 6;
    rulesRef.makeMove(someMove, Logic::White);
    moves = rulesRef.calcPossibleMoves(Logic::Black);
    ASSERT_THAT(moves, SizeIs(3));
    someMove.row = 7;
    someMove.col = 5;
    rulesRef.makeMove(someMove, Logic::Black);
    moves = rulesRef.calcPossibleMoves(Logic::White);
    ASSERT_THAT(moves, SizeIs(9));
    someMove.row = 8;
    someMove.col = 4;
    rulesRef.makeMove(someMove, Logic::White);
    moves = rulesRef.calcPossibleMoves(Logic::Black);
    ASSERT_THAT(moves, SizeIs(3));
    someMove.row = 7;
    someMove.col = 4;
    rulesRef.makeMove(someMove, Logic::Black);
    moves = rulesRef.calcPossibleMoves(Logic::White);
    ASSERT_THAT(moves, SizeIs(8));
    someMove.row = 2;
    someMove.col = 6;
    rulesRef.makeMove(someMove, Logic::White);
    moves = rulesRef.calcPossibleMoves(Logic::Black);
    ASSERT_THAT(moves, SizeIs(6));
    someMove.row = 1;
    someMove.col = 6;
    rulesRef.makeMove(someMove, Logic::Black);
    moves = rulesRef.calcPossibleMoves(Logic::White);
    ASSERT_THAT(moves, SizeIs(7));
    someMove.row = 3;
    someMove.col = 3;
    rulesRef.makeMove(someMove, Logic::White);
    moves = rulesRef.calcPossibleMoves(Logic::Black);
    ASSERT_THAT(moves, SizeIs(5));
    someMove.row = 2;
    someMove.col = 2;
    rulesRef.makeMove(someMove, Logic::Black);
    moves = rulesRef.calcPossibleMoves(Logic::White);
    ASSERT_THAT(moves, SizeIs(4));
    someMove.row = 1;
    someMove.col = 1;
    rulesRef.makeMove(someMove, Logic::White);
    moves = rulesRef.calcPossibleMoves(Logic::Black);
    ASSERT_THAT(moves, SizeIs(5));
    someMove.row = 2;
    someMove.col = 3;
    rulesRef.makeMove(someMove, Logic::Black);
    moves = rulesRef.calcPossibleMoves(Logic::White);
    ASSERT_THAT(moves, SizeIs(10));
    someMove.row = 7;
    someMove.col = 3;
    rulesRef.makeMove(someMove, Logic::White);
    moves = rulesRef.calcPossibleMoves(Logic::Black);
    ASSERT_THAT(moves, SizeIs(5));
    someMove.row = 7;
    someMove.col = 2;
    rulesRef.makeMove(someMove, Logic::Black);
    moves = rulesRef.calcPossibleMoves(Logic::White);
    ASSERT_THAT(moves, SizeIs(10));
    someMove.row = 6;
    someMove.col = 2;
    rulesRef.makeMove(someMove, Logic::White);
    moves = rulesRef.calcPossibleMoves(Logic::Black);
    ASSERT_THAT(moves, SizeIs(6));
    someMove.row = 2;
    someMove.col = 1;
    rulesRef.makeMove(someMove, Logic::Black);
    moves = rulesRef.calcPossibleMoves(Logic::White);
    ASSERT_THAT(moves, SizeIs(11));
    someMove.row = 8;
    someMove.col = 2;
    rulesRef.makeMove(someMove, Logic::White);
    moves = rulesRef.calcPossibleMoves(Logic::Black);
    ASSERT_THAT(moves, SizeIs(5));
    someMove.row = 7;
    someMove.col = 1;
    rulesRef.makeMove(someMove, Logic::Black);
    moves = rulesRef.calcPossibleMoves(Logic::White);
    ASSERT_THAT(moves, SizeIs(9));
    someMove.row = 3;
    someMove.col = 1;
    rulesRef.makeMove(someMove, Logic::White);
    moves = rulesRef.calcPossibleMoves(Logic::Black);
    ASSERT_THAT(moves, SizeIs(7));
    someMove.row = 5;
    someMove.col = 1;
    rulesRef.makeMove(someMove, Logic::Black);
    moves = rulesRef.calcPossibleMoves(Logic::White);
    ASSERT_THAT(moves, SizeIs(11));
    someMove.row = 1;
    someMove.col = 3;
    rulesRef.makeMove(someMove, Logic::White);
    moves = rulesRef.calcPossibleMoves(Logic::Black);
    ASSERT_THAT(moves, SizeIs(4));
    someMove.row = 5;
    someMove.col = 7;
    rulesRef.makeMove(someMove, Logic::Black);
    moves = rulesRef.calcPossibleMoves(Logic::White);
    ASSERT_THAT(moves, SizeIs(11));
    someMove.row = 6;
    someMove.col = 8;
    rulesRef.makeMove(someMove, Logic::White);
    moves = rulesRef.calcPossibleMoves(Logic::Black);
    ASSERT_THAT(moves, SizeIs(3));
    someMove.row = 3;
    someMove.col = 4;
    rulesRef.makeMove(someMove, Logic::Black);
    moves = rulesRef.calcPossibleMoves(Logic::White);
    ASSERT_THAT(moves, SizeIs(8));
    someMove.row = 2;
    someMove.col = 4;
    rulesRef.makeMove(someMove, Logic::White);
    moves = rulesRef.calcPossibleMoves(Logic::Black);
    ASSERT_THAT(moves, SizeIs(5));
    someMove.row = 1;
    someMove.col = 2;
    rulesRef.makeMove(someMove, Logic::Black);
    moves = rulesRef.calcPossibleMoves(Logic::White);
    ASSERT_THAT(moves, SizeIs(8));
    someMove.row = 3;
    someMove.col = 5;
    rulesRef.makeMove(someMove, Logic::White);
    moves = rulesRef.calcPossibleMoves(Logic::Black);
    ASSERT_THAT(moves, SizeIs(7));
    someMove.row = 1;
    someMove.col = 4;
    rulesRef.makeMove(someMove, Logic::Black);
    moves = rulesRef.calcPossibleMoves(Logic::White);
    ASSERT_THAT(moves, SizeIs(12));
    someMove.row = 1;
    someMove.col = 5;
    rulesRef.makeMove(someMove, Logic::White);
    moves = rulesRef.calcPossibleMoves(Logic::Black);
    ASSERT_THAT(moves, SizeIs(3));
    someMove.row = 5;
    someMove.col = 8;
    rulesRef.makeMove(someMove, Logic::Black);
    moves = rulesRef.calcPossibleMoves(Logic::White);
    ASSERT_THAT(moves, SizeIs(12));
    someMove.row = 1;
    someMove.col = 7;
    rulesRef.makeMove(someMove, Logic::White);
    moves = rulesRef.calcPossibleMoves(Logic::Black);
    ASSERT_THAT(moves, SizeIs(1));
    someMove.row = 4;
    someMove.col = 7;
    rulesRef.makeMove(someMove, Logic::Black);
    moves = rulesRef.calcPossibleMoves(Logic::White);
    ASSERT_THAT(moves, SizeIs(9));
    someMove.row = 2;
    someMove.col = 5;
    rulesRef.makeMove(someMove, Logic::White);
    moves = rulesRef.calcPossibleMoves(Logic::Black);
    someMove.row = 6;
    someMove.col = 4;
    rulesRef.makeMove(someMove, Logic::Black);
    moves = rulesRef.calcPossibleMoves(Logic::White);
    ASSERT_THAT(moves, SizeIs(8));
    someMove.row = 3;
    someMove.col = 2;
    rulesRef.makeMove(someMove, Logic::White);
    moves = rulesRef.calcPossibleMoves(Logic::Black);
    ASSERT_THAT(moves, SizeIs(0));
    moves = rulesRef.calcPossibleMoves(Logic::White);
    ASSERT_THAT(moves, SizeIs(6));
    someMove.row = 3;
    someMove.col = 7;
    rulesRef.makeMove(someMove, Logic::White);
    moves = rulesRef.calcPossibleMoves(Logic::Black);
    ASSERT_THAT(moves, SizeIs(3));
    someMove.row = 6;
    someMove.col = 5;
    rulesRef.makeMove(someMove, Logic::Black);
    moves = rulesRef.calcPossibleMoves(Logic::White);
    ASSERT_THAT(moves, SizeIs(8));
    someMove.row = 8;
    someMove.col = 5;
    rulesRef.makeMove(someMove, Logic::White);
    moves = rulesRef.calcPossibleMoves(Logic::Black);
    ASSERT_THAT(moves, SizeIs(2));
    someMove.row = 6;
    someMove.col = 3;
    rulesRef.makeMove(someMove, Logic::Black);
    moves = rulesRef.calcPossibleMoves(Logic::White);
    ASSERT_THAT(moves, SizeIs(7));
    someMove.row = 4;
    someMove.col = 8;
    rulesRef.makeMove(someMove, Logic::White);
    moves = rulesRef.calcPossibleMoves(Logic::Black);
    ASSERT_THAT(moves, SizeIs(5));
    someMove.row = 2;
    someMove.col = 8;
    rulesRef.makeMove(someMove, Logic::Black);
    moves = rulesRef.calcPossibleMoves(Logic::White);
    ASSERT_THAT(moves, SizeIs(10));
    someMove.row = 5;
    someMove.col = 3;
    rulesRef.makeMove(someMove, Logic::White);
    moves = rulesRef.calcPossibleMoves(Logic::Black);
    ASSERT_THAT(moves, SizeIs(5));
    someMove.row = 2;
    someMove.col = 7;
    rulesRef.makeMove(someMove, Logic::Black);
    moves = rulesRef.calcPossibleMoves(Logic::White);
    ASSERT_THAT(moves, SizeIs(6));
    someMove.row = 3;
    someMove.col = 8;
    rulesRef.makeMove(someMove, Logic::White);
    moves = rulesRef.calcPossibleMoves(Logic::Black);
    ASSERT_THAT(moves, SizeIs(5));
    someMove.row = 1;
    someMove.col = 8;
    rulesRef.makeMove(someMove, Logic::Black);
    moves = rulesRef.calcPossibleMoves(Logic::White);
    ASSERT_THAT(moves, SizeIs(5));
    someMove.row = 6;
    someMove.col = 1;
    rulesRef.makeMove(someMove, Logic::White);
    moves = rulesRef.calcPossibleMoves(Logic::Black);
    ASSERT_THAT(moves, SizeIs(3));
    someMove.row = 6;
    someMove.col = 7;
    rulesRef.makeMove(someMove, Logic::Black);
    moves = rulesRef.calcPossibleMoves(Logic::White);
    ASSERT_THAT(moves, SizeIs(4));
    someMove.row = 8;
    someMove.col = 1;
    rulesRef.makeMove(someMove, Logic::White);
    moves = rulesRef.calcPossibleMoves(Logic::Black);
    ASSERT_THAT(moves, SizeIs(3));
    someMove.row = 8;
    someMove.col = 7;
    rulesRef.makeMove(someMove, Logic::Black);
    moves = rulesRef.calcPossibleMoves(Logic::White);
    ASSERT_THAT(moves, SizeIs(2));
    someMove.row = 8;
    someMove.col = 3;
    rulesRef.makeMove(someMove, Logic::White);
    moves = rulesRef.calcPossibleMoves(Logic::Black);
    ASSERT_THAT(moves, SizeIs(2));
    someMove.row = 4;
    someMove.col = 2;
    rulesRef.makeMove(someMove, Logic::Black);
    moves = rulesRef.calcPossibleMoves(Logic::White);
    ASSERT_THAT(moves, SizeIs(2));
    someMove.row = 5;
    someMove.col = 2;
    rulesRef.makeMove(someMove, Logic::White);
    moves = rulesRef.calcPossibleMoves(Logic::Black);
    ASSERT_THAT(moves, SizeIs(1));
    someMove.row = 4;
    someMove.col = 1;
    rulesRef.makeMove(someMove, Logic::Black);

    // Both players should be out of moves:
    moves = rulesRef.calcPossibleMoves(Logic::White);
    ASSERT_THAT(moves, SizeIs(0));
    moves = rulesRef.calcPossibleMoves(Logic::Black);
    ASSERT_THAT(moves, SizeIs(0));

    // Count the score for white & black:
    int i = 0, j = 0, whiteCount = 0;
    for (i = 0; i < rulesRef.getBoardClass().getSize(); i++) {
        for (j = 0; j < rulesRef.getBoardClass().getSize(); j++) {
            if (rulesRef.getBoardClass().getBoard()[i][j].getVal() == 'O') {
                whiteCount++;
            }
        }
    }

    i = 0, j = 0;
    int blackCount = 0;
    for (i = 0; i < rulesRef.getBoardClass().getSize(); i++) {
        for (j = 0; j < rulesRef.getBoardClass().getSize(); j++) {
            if (rulesRef.getBoardClass().getBoard()[i][j].getVal() == 'X') {
                blackCount++;
            }
        }
    }

    // Make sure white wins:
    EXPECT_GT(whiteCount, blackCount);
}

/**
* This test checks the state of the board mid-game
* to see if it fits the moves that were played.
*/
TEST_F(NormalRulesetTest, MidgameBoardState) {
    NormalRuleset &rulesRef = *(rules);
    Checker::position someMove;
    someMove.row = 4;
    someMove.col = 3;
    rulesRef.makeMove(someMove, Logic::Black);
    std::vector<Checker::position> &moves = rulesRef.calcPossibleMoves(Logic::White);
    ASSERT_THAT(moves, SizeIs(3));
    someMove.row = 3;
    someMove.col = 3;
    rulesRef.makeMove(someMove, Logic::White);
    moves = rulesRef.calcPossibleMoves(Logic::Black);
    ASSERT_THAT(moves, SizeIs(4));
    someMove.row = 2;
    someMove.col = 3;
    rulesRef.makeMove(someMove, Logic::Black);
    moves = rulesRef.calcPossibleMoves(Logic::White);
    ASSERT_THAT(moves, SizeIs(6));
    someMove.row = 6;
    someMove.col = 4;
    rulesRef.makeMove(someMove, Logic::White);
    moves = rulesRef.calcPossibleMoves(Logic::Black);
    ASSERT_THAT(moves, SizeIs(3));
    someMove.row = 6;
    someMove.col = 3;
    rulesRef.makeMove(someMove, Logic::Black);
    moves = rulesRef.calcPossibleMoves(Logic::White);
    ASSERT_THAT(moves, SizeIs(6));
    someMove.row = 2;
    someMove.col = 2;
    rulesRef.makeMove(someMove, Logic::White);
    moves = rulesRef.calcPossibleMoves(Logic::Black);
    ASSERT_THAT(moves, SizeIs(5));
    someMove.row = 7;
    someMove.col = 4;
    rulesRef.makeMove(someMove, Logic::Black);
    moves = rulesRef.calcPossibleMoves(Logic::White);
    ASSERT_THAT(moves, SizeIs(8));
    someMove.row = 3;
    someMove.col = 5;
    rulesRef.makeMove(someMove, Logic::White);
    moves = rulesRef.calcPossibleMoves(Logic::Black);
    ASSERT_THAT(moves, SizeIs(5));
    someMove.row = 2;
    someMove.col = 1;
    rulesRef.makeMove(someMove, Logic::Black);
    moves = rulesRef.calcPossibleMoves(Logic::White);
    ASSERT_THAT(moves, SizeIs(7));
    someMove.row = 1;
    someMove.col = 1;
    rulesRef.makeMove(someMove, Logic::White);
    moves = rulesRef.calcPossibleMoves(Logic::Black);
    ASSERT_THAT(moves, SizeIs(4));
    someMove.row = 5;
    someMove.col = 6;
    rulesRef.makeMove(someMove, Logic::Black);
    moves = rulesRef.calcPossibleMoves(Logic::White);
    ASSERT_THAT(moves, SizeIs(10));
    someMove.row = 6;
    someMove.col = 7;
    rulesRef.makeMove(someMove, Logic::White);
    moves = rulesRef.calcPossibleMoves(Logic::Black);
    ASSERT_THAT(moves, SizeIs(5));

    // Create a board to check:
    Board *correct = new Board(8);
    correct->getBoard()[0][0].setO();
    correct->getBoard()[1][0].setX();
    correct->getBoard()[1][1].setO();
    correct->getBoard()[1][2].setX();
    correct->getBoard()[2][2].setO();
    correct->getBoard()[2][4].setO();
    correct->getBoard()[3][2].setX();
    correct->getBoard()[3][3].setO();
    correct->getBoard()[3][4].setO();
    correct->getBoard()[4][3].setX();
    correct->getBoard()[4][4].setX();
    correct->getBoard()[4][5].setO();
    correct->getBoard()[5][2].setX();
    correct->getBoard()[5][3].setX();
    correct->getBoard()[5][6].setO();
    correct->getBoard()[6][3].setX();

    // Compare the board to test and the correct board:
    int i = 0, j = 0;
    for (i = 0; i < b->getSize(); i++) {
        for (j = 0; j < b->getSize(); j++) {
         EXPECT_EQ(b->getBoard()[i][j].getVal(), correct->getBoard()[i][j].getVal());
        }
    }

    delete correct;
}