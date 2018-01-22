#include <iostream>
#include <sstream>
#include "../include/Board.h"
#include "../include/Logic.h"
#include "../include/Flow.h"
#include "../include/NormalRuleset.h"
#include "../include/RegularPlayer.h"
#include "../include/AIPlayer.h"
#include "../include/ConsoleGui.h"
#include "../include/LocalOnlinePlayer.h"
#include "../include/RemoteOnlinePlayer.h"
#include "../include/OnlineFlow.h"

using namespace std;

IPlayer *createCurrentIPlayerInstance(int type) {
    if (type == 1 || type == 2) {
        return new RegularPlayer('X');
    } else {
        return new LocalOnlinePlayer();
    }
}

IPlayer *createOpponentIPlayerInstance(int type) {
    if (type == 1) {
        return new RegularPlayer('O');
    } else if (type == 2) {
        return new AIPlayer('O');
    }
}

/**
 * The main function which initializes and runs a game.
 */
int main() {
    //Create a console GUI instance.
    IGui *gui = new ConsoleGui();
    IGui &guiRef = *(gui);
    LocalOnlinePlayer *first = NULL;
    RemoteOnlinePlayer *second = NULL;
    GameResult result(GameResult::None, 0);
    bool playerTypeChosen = false;
    bool exitGame = false;
    while (!playerTypeChosen) {
        // Create a new board with size 8 on the heap:
        Board *b = new Board(8);

        // Create a Logic class with normal rules on the heap:

        NormalRuleset *rules = new NormalRuleset(b);
        NormalRuleset &rulesRef = *(rules);

        int opponentType = gui->scanPlayerType();
        if (opponentType == 0 && !exitGame) {
            exitGame = true;
            delete b;
            delete rules;
            break;
        }
        if (opponentType == 3) {
            //Create players.
            try {
                first = new LocalOnlinePlayer();
                second = new RemoteOnlinePlayer(first->getClient());
                bool stayConnected = true;
                while (stayConnected) {
                    bool reslult = first->initializeGame();
                    if (reslult) {
                        // Pass it by reference to a new game Flow class:
                        OnlineFlow f(rulesRef, guiRef, first, second);
                        playerTypeChosen = true;
                        // Play the game:
                        result = f.play();
                        if (result.getResult() == GameResult::None && result.getScore() == 0) {
                            delete b;
                            b = new Board(8);
                            delete rules;
                            rules = new NormalRuleset(b);
                            rulesRef = *(rules);
                            continue;
                        } else {
                            stayConnected = false;
                            gui->printGameResult(result);
                        }
                        //b->resetBoard();
                        // Free the board and Logic classes:
                        //delete b;
                        //delete rules;
                    } else {
                        playerTypeChosen = false;
                        stayConnected = false;
                    }
                }
                delete first;
                delete second;
            }
            catch (const char *msg) {
                cout << msg << ", Please try again later." << "\n\n";
            }
        } else {
            //Create players.
            IPlayer *first = createCurrentIPlayerInstance(opponentType);
            IPlayer *second = createOpponentIPlayerInstance(opponentType);
            playerTypeChosen = true;
            // Pass it by reference to a new game Flow class:
            Flow f(rulesRef, guiRef, first, second);
            result = f.play();
            delete first;
            delete second;
            gui->printGameResult(result);
        }
        // Free the board and Logic classes:
        delete b;
        delete rules;
    }
    delete gui;
}
