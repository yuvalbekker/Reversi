#include <iostream>
#include <sys/socket.h>
#include "../include/JoinCommand.h"

void
JoinCommand::execute(vector<string> args, vector<Game> *games, int playerSocket, pthread_mutex_t &gamesVector_mutex) {
    string inputGameNameArg = args.at(0);
    Game *currentGame;
    cout << "Received JoinCommand. Game name: " << inputGameNameArg << endl;
    bool gameExists = false;
    pthread_mutex_lock(&gamesVector_mutex);
    for (int i = 0; i < games->size(); i++) {
        if (games->at(i).getGameName() == inputGameNameArg && !games->at(i).isBusy()) {
            games->at(i).getSecondPlayer()->setSocket(playerSocket);
            gameExists = true;
            cout << "Second player joined the game: " << inputGameNameArg << endl;
            currentGame = &games->at(i);
            break;
        }
    }
    pthread_mutex_unlock(&gamesVector_mutex);
    if (!gameExists) {
        char result = -1;
        int n = send(playerSocket, &result, sizeof(result), MSG_NOSIGNAL);
        cout << "Game '" << inputGameNameArg << "' doesn't exist, error message sent to client" << endl;
        if (n == -1) {
            throw "Error sending error code to socket";
        }
    } else {
        pthread_mutex_lock(&gamesVector_mutex);
        char firstPlayerSymbol = currentGame->getFirstPlayer()->getSymbol();
        char secondPlayerSymbol = currentGame->getSecondPlayer()->getSymbol();
        pthread_mutex_unlock(&gamesVector_mutex);
        int n = send(currentGame->getFirstPlayer()->getSocket(), &firstPlayerSymbol, sizeof(firstPlayerSymbol),
                     MSG_NOSIGNAL);
        if (n == -1) {
            cout << "Error send symbol to socket" << endl;
            return;
        } else {
            cout << "sent first player Symbol: '" << firstPlayerSymbol << "'" << endl;
        }
        n = send(currentGame->getSecondPlayer()->getSocket(), &secondPlayerSymbol, sizeof(secondPlayerSymbol),
                 MSG_NOSIGNAL);
        if (n == -1) {
            cout << "Error send symbol to socket" << endl;
            return;
        } else {
            cout << "sent second player Symbol: '" << secondPlayerSymbol << "'" << endl;
        }
        cout << "'" << inputGameNameArg << "' game is busy" << endl;
    }
}