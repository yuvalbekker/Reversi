#include <sys/socket.h>
#include <iostream>
#include "../include/ListGamesCommand.h"

void ListGamesCommand::execute(vector<string> args, vector<Game> *games, int playerSocket,
                               pthread_mutex_t &gamesVector_mutex) {
    cout << "Received ListGamesCommand " << endl;
    string gamesListString;
    pthread_mutex_lock(&gamesVector_mutex);
    for (int i = 0; i < games->size(); i++) {
        if (!games->at(i).isBusy())
            gamesListString += games->at(i).getGameName() + "\n";
    }
    pthread_mutex_unlock(&gamesVector_mutex);
    int n = send(playerSocket, gamesListString.data(), sizeof(gamesListString), MSG_NOSIGNAL);
    if (n == -1) {
        throw "Error sending games list string to socket";
    }
    cout << "Available games:" << endl;
    cout << gamesListString << endl;
    cout << "List of available games sent:" << endl;

}