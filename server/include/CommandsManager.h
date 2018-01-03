#include <map>
#include "Command.h"
#include "Game.h"

#ifndef REVERSISERVER_COMMANDSMANAGER_H
#define REVERSISERVER_COMMANDSMANAGER_H

class CommandsManager {
public:
    static CommandsManager *getInstance();

    ~CommandsManager();

    /**
     * Calls the specefic command object according the the input parameters.
     * @param command
     * @param args
     * @param socket
     */
    void executeCommand(string command, vector<string> args, int socket = 0);

private:
    // A singleton
    /**
     * The c'tor of the class
     */
    CommandsManager();

    /**
     * The c'tor of the class
     */
    CommandsManager(const CommandsManager &);

    static CommandsManager *instance;
    static pthread_mutex_t lock;
    static pthread_mutex_t gameVector_mutex;
    map<string, Command *> commandsMap;
    vector<Game> *games;
};


#endif //REVERSISERVER_COMMANDSMANAGER_H
