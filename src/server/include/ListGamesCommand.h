#ifndef REVERSISERVER_LISTGAMESCOMMAND_H
#define REVERSISERVER_LISTGAMESCOMMAND_H

#include "Command.h"

class ListGamesCommand : public Command {
public:
    virtual void
    execute(vector<string> args, vector<Game> *games, int playerSocket, pthread_mutex_t &gamesVector_mutex);
};

#endif //REVERSISERVER_LISTGAMESCOMMAND_H
