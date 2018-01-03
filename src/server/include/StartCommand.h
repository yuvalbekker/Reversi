#include "Command.h"

#ifndef REVERSISERVER_STARTCOMMAND_H
#define REVERSISERVER_STARTCOMMAND_H

class StartCommand : public Command {
public:
    virtual void
    execute(vector<string> args, vector<Game> *games, int playerSocket, pthread_mutex_t &gamesVector_mutex);
};

#endif //REVERSISERVER_STARTCOMMAND_H
