#include <vector>
#include <string>
#include "Game.h"

#ifndef REVERSISERVER_COMMAND_H
#define REVERSISERVER_COMMAND_H

using namespace std;
#define MAX_RESULT_LEN 50

class Command {
public:

    /**
     * Executes the specific according to the input parameters.
     * @param args
     * @param games
     * @param playerSocket
     * @param gamesVector_mutex
     */
    virtual void
    execute(vector<string> args, vector<Game> *games, int playerSocket, pthread_mutex_t &gamesVector_mutex) = 0;

    /**
     * The d'tor of the class
     */
    virtual ~Command() {}
};


#endif //REVERSISERVER_COMMAND_H
