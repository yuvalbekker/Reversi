
#ifndef REVERSISERVER_JOINCOMMAND_H
#define REVERSISERVER_JOINCOMMAND_H

#include "Command.h"

class JoinCommand : public Command {
public:
    virtual void
    execute(vector<string> args, vector<Game> *games, int playerSocket, pthread_mutex_t &gamesVector_mutex);
};

#endif //REVERSISERVER_JOINCOMMAND_H
