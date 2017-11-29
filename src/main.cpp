#include <iostream>
#include <sstream>
#include "../include/Board.h"
#include "../include/Logic.h"
#include "../include/Flow.h"
#include "../include/NormalRuleset.h"
#include "../include/RegularPlayer.h"
#include "../include/AIPlayer.h"
#include "../include/ConsoleGui.h"

using namespace std;

/**
 * The main function which initializes and runs a game.
 * @return int
 */
int main() {

    //Create a console GUI instance.
    IGui *gui = new ConsoleGui();
    IGui &guiRef = *(gui);

    //Create players.
    IPlayer *first = new RegularPlayer('X');
    IPlayer *second = gui->scanPlayerType();

    // Create a new board with size 8 on the heap:
    Board *b = new Board(8);

    // Create a Logic class with normal rules on the heap:
    NormalRuleset *rules = new NormalRuleset(b);
    NormalRuleset &rulesRef = *(rules);


    // Pass it by reference to a new game Flow class:
    Flow f(rulesRef, guiRef, first, second);

    // Play the game and print the result:
    GameResult result = f.play();
    gui->printGameResult(result);

    // Free the allocated objects:
    delete b;
    delete rules;
    delete first;
    delete second;
    delete gui;
}