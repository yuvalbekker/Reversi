// Name: Eyal Lantzman ID: 205502818

#include <iostream>
#include <sstream>
#include "Board.h"
#include "Logic.h"
#include "Flow.h"
#include "NormalRuleset.h"
#include "RegularPlayer.h"
#include "AIPlayer.h"
#include "ConsoleGui.h"

using namespace std;

IPlayer *getPlayerType() {
    cout << "Choose your opponent: \n";
    cout << "Press 1 for Human player: \n";
    cout << "Press 2 for AI player: \n";
    int playerTypeInput = -1;
    string input;
    while (playerTypeInput != 1 && playerTypeInput != 2) {
        cin >> input;
        try {
            stringstream ss(input);
            ss >> playerTypeInput;
            if (playerTypeInput != 1 && playerTypeInput != 2) {
                cout << "Wrong input! try again: \n";
            }
        }
        catch (exception e) {
            cout << "Wrong input! try again: \n";
        }
    }
    if (playerTypeInput == 1) {
        return new RegularPlayer('O');
    } else if (playerTypeInput == 2) {
        return new AIPlayer('O');
    }

}


/**
 * The main function which initializes and runs a game.
 */
int main() {
    IPlayer *first = new RegularPlayer('X');
    IPlayer *second = getPlayerType();
    // Create a new board with size 8 on the heap:
    Board *b = new Board(8);

    // Create a Logic class with normal rules on the heap:
    NormalRuleset *rules = new NormalRuleset(b);
    NormalRuleset &rulesRef = *(rules);

    IGui *gui = new ConsoleGui();
    IGui &guiRef = *(gui);


    // Pass it by reference to a new game Flow class:
    Flow f(rulesRef, guiRef, first, second);

    // Play the game:
    f.play();

    // Free the board and Logic classes:
    delete b;
    delete rules;
    delete first;
    delete second;
    delete gui;
}