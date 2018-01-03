#include <sys/socket.h>
#include <iostream>
#include "../include/PlayCommand.h"

void
PlayCommand::execute(vector<string> args, vector<Game> *games, int playerSocket, pthread_mutex_t &gamesVector_mutex) {
    Game *currentGame;
    pthread_mutex_lock(&gamesVector_mutex);
    for (int i = 0; i < games->size(); i++) {
        if (games->at(i).getFirstPlayer()->getSocket() == playerSocket ||
            games->at(i).getSecondPlayer()->getSocket() == playerSocket) {
            currentGame = &games->at(i);
            break;
        }
    }
    cout << "Received PlayCommand for game '" << currentGame->getGameName() << endl;
    pthread_mutex_unlock(&gamesVector_mutex);
    string positionMessage = args.at(0) + " " + args.at(1);
    int n;
    pthread_mutex_lock(&gamesVector_mutex);
    if (currentGame->getFirstPlayer()->getSocket() == playerSocket) {
        n = send(currentGame->getSecondPlayer()->getSocket(), positionMessage.data(), sizeof(positionMessage),
                 MSG_NOSIGNAL);
        cout << "Play sent to second player. socketId = " << currentGame->getSecondPlayer()->getSocket() << endl;

    } else if (currentGame->getSecondPlayer()->getSocket() == playerSocket) {
        n = send(currentGame->getFirstPlayer()->getSocket(), positionMessage.data(), sizeof(positionMessage),
                 MSG_NOSIGNAL);
        cout << "Play sent to first player. socketId = " << currentGame->getFirstPlayer()->getSocket() << endl;
    }
    pthread_mutex_unlock(&gamesVector_mutex);
    if (n == -1) {
        throw "Error sending position to socket";
    }
}
