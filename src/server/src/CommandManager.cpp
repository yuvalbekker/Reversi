#include <iostream>
#include "../include/CommandsManager.h"
#include "../include/StartCommand.h"
#include "../include/ListGamesCommand.h"
#include "../include/JoinCommand.h"
#include "../include/PlayCommand.h"
#include "../include/CloseCommand.h"

CommandsManager *CommandsManager::instance = 0;
pthread_mutex_t CommandsManager::lock;
pthread_mutex_t CommandsManager::gameVector_mutex;

CommandsManager::CommandsManager() {
    this->games = new vector<Game>;
    commandsMap["start"] = new StartCommand();
    commandsMap["list_games"] = new ListGamesCommand();
    commandsMap["join"] = new JoinCommand();
    commandsMap["play"] = new PlayCommand();
    commandsMap["close"] = new CloseCommand();
}

CommandsManager::~CommandsManager() {
    map<string, Command *>::iterator it;
    for (it = commandsMap.begin(); it !=
                                   commandsMap.end(); it++) {
        delete it->second;
    }
    for (int i = 0; i < this->games->size(); i++) {
        //this->games->at(i).getFirstPlayer()->disconnect();
        //this->games->at(i).getSecondPlayer()->disconnect();
        delete this->games->at(i).getSecondPlayer();
        delete this->games->at(i).getFirstPlayer();
    }
    delete this->games;
}

void CommandsManager::executeCommand(string command, vector<string> args, int playerSocket) {
    Command *commandObj = commandsMap[command];
    pthread_mutex_lock(&lock);
    if (commandsMap.at(command) == NULL) {
        cout << "Invalid command received" << endl;
    } else {
        commandObj->execute(args, this->games, playerSocket, gameVector_mutex);
    }
    pthread_mutex_unlock(&lock);

}

CommandsManager *CommandsManager::getInstance() {
    if (instance == 0) {
        pthread_mutex_lock(&lock);
        if (instance == 0) {
            instance = new CommandsManager();
        }
        pthread_mutex_unlock(&lock);
    }
    return instance;
}