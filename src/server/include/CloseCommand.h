#ifndef REVERSISERVER_CLOSECOMMAND_H
#define REVERSISERVER_CLOSECOMMAND_H

#include "Command.h"

class CloseCommand : public Command {
public:
    virtual void
    execute(vector<string> args, vector<Game> *games, int playerSocket, pthread_mutex_t &gamesVector_mutex);
};

#endif //REVERSISERVER_CLOSECOMMAND_H
