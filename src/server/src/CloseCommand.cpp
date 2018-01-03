#include <iostream>
#include <sys/socket.h>
#include "../include/CloseCommand.h"

void
CloseCommand::execute(vector<string> args, vector<Game> *games, int playerSocket, pthread_mutex_t &gamesVector_mutex) {
    Game *currentGame;
    bool gameFound = false;
    pthread_mutex_lock(&gamesVector_mutex);
    for (int i = 0; i < games->size(); i++) {
        if (games->at(i).getFirstPlayer()->getSocket() == playerSocket ||
            games->at(i).getSecondPlayer()->getSocket() == playerSocket) {
            currentGame = &games->at(i);
            gameFound = true;
            break;
        }
    }
    if (gameFound) {
        cout << "Received CloseCommand for game '" << currentGame->getGameName() << "'" << endl;
        string gameName = currentGame->getGameName();
        int a = games->size();
        for (int i = 0; i < games->size(); i++) {
            if (games->at(i).getFirstPlayer()->getSocket() == playerSocket ||
                games->at(i).getSecondPlayer()->getSocket() == playerSocket) {
                games->at(i).getFirstPlayer()->closeGame();
                games->at(i).getSecondPlayer()->closeGame();
                games->erase(games->begin() + i);
                cout << "Game '" << gameName << "'" << "removed successfully" << endl;
                break;
            }
        }
        a = games->size();
        int b = 0;
    } else {
        string positionMessage = "-2 -2";
        int n = send(playerSocket, positionMessage.data(), sizeof(positionMessage),
                     MSG_NOSIGNAL);
        cout << "Invalid close command (not a game member). error code sent to client" << endl;
    }
    pthread_mutex_unlock(&gamesVector_mutex);
}