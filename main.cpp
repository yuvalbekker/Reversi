// Name: Eyal Lantzman ID: 205502818

#include <iostream>
#include "Board.h"
#include "Logic.h"
#include "Flow.h"
#include "NormalRuleset.h"

using namespace std;

/**
 * The main function which initializes and runs a game.
 */
int main() {

    // Create a new board with size 8 on the heap:
    Board *b = new Board(8);

    // Create a Logic class with normal rules on the heap:
    NormalRuleset *rules = new NormalRuleset(b);
    NormalRuleset &rulesRef = *(rules);

    // Pass it by reference to a new game Flow class:
    Flow f(rulesRef);

    // Play the game:
    f.play();

    // Free the board and Logic classes:
    delete b;
    delete rules;
}