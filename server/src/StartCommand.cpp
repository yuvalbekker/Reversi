#include <iostream>
#include <sys/socket.h>
#include "../include/StartCommand.h"

void
StartCommand::execute(vector<string> args, vector<Game> *games, int playerSocket, pthread_mutex_t &gamesVector_mutex) {
    string inputGameNameArg = args.at(0);
    cout << "Received StartCommand. Game name: '" << inputGameNameArg << "' from socket: " << playerSocket << endl;
    bool gameAlreadyExists = false;
    pthread_mutex_lock(&gamesVector_mutex);
    for (int i = 0; i < games->size(); i++) {
        if (games->at(i).getGameName() == inputGameNameArg) {
            gameAlreadyExists = true;
            break;
        }
    }
    pthread_mutex_unlock(&gamesVector_mutex);
    if (gameAlreadyExists) {
        long result = -1;
        int n = send(playerSocket, &result, sizeof(result), MSG_NOSIGNAL);
        cout << "Game '" << inputGameNameArg << "' already exits. message sent to the client" << endl;
        if (n == -1) {
            throw "Error sending error code to socket";
        }
    } else {
        string newGameName = inputGameNameArg;
        Game g(newGameName);
        g.getFirstPlayer()->setSocket(playerSocket);
        pthread_mutex_lock(&gamesVector_mutex);
        games->push_back(g);
        pthread_mutex_unlock(&gamesVector_mutex);
        cout << "Game '" << newGameName << "' created successfully" << endl;
        long result = 1;
        int n = send(playerSocket, &result, sizeof(result), MSG_NOSIGNAL);
        if (n == -1) {
            throw "Error sending error code to socket";
        }

    }
}
