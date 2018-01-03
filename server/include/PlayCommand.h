#ifndef REVERSISERVER_PLAYCOMMAND_H
#define REVERSISERVER_PLAYCOMMAND_H

#include "Command.h"

class PlayCommand : public Command {
public:
    virtual void
    execute(vector<string> args, vector<Game> *games, int playerSocket, pthread_mutex_t &gamesVector_mutex);
};

#endif //REVERSISERVER_PLAYCOMMAND_H
