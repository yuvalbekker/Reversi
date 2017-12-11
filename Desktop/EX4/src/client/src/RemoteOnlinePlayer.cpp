#include <iostream>
#include "../include/RemoteOnlinePlayer.h"
using namespace std;

RemoteOnlinePlayer::RemoteOnlinePlayer(ReversiClient* matchingClient): client(matchingClient) {
}

RemoteOnlinePlayer::~RemoteOnlinePlayer() {
}

Checker::position RemoteOnlinePlayer::generatePosition(Checker::position &pos) {
    try {
        this->client->readPosition(pos);
    }

    catch (const char *msg) {
        cout << "Failed to send chosen position to server. Reason:" << msg << endl;
    }
    return pos;
}




