#include <cstdlib>
#include <limits>
#include "../include/LocalOnlinePlayer.h"
#include "../include/ConfigReader.h"

using namespace std;

LocalOnlinePlayer::LocalOnlinePlayer() {
    this->playerType = playerType;
    string configurationPath = "clientConfig.txt";
    ConfigReader reader(configurationPath);
    reader.readConfigFile();
    this->client = new ReversiClient(reader.getIP().c_str(), reader.getPort());
    try {
        client->connectToServer();
        cout << "Connected to server" << endl;
        cout << "Waiting for other player to join...";
        this->playerType = this->client->readPlayerSymbol();
        cout << "My symbol is: " << this->playerType << endl;

    } catch (const char *msg) {
        cout << "Failed to connect to server. Reason:" << msg << endl;
        throw "Failed to connect to server";
    }
}

LocalOnlinePlayer::~LocalOnlinePlayer() {
    delete this->client;
}

Checker::position LocalOnlinePlayer::generatePosition(std::vector<Checker::position> &moves, Board &board) {
    Checker::position pos = readPositionFromUser(moves);
    return pos;
}

Checker::position LocalOnlinePlayer::readPositionFromUser(std::vector<Checker::position> &moves) {
    Checker::position pos;
    int i = 0;
    int j = 0;

    while (true) {
        bool foundInMoves = false;
        cout << "\nPlease enter your move in the format: row col" << endl;
        cin >> i >> j;

        if (cin.fail() || i > 8 || i <= 0 || j > 8 || j <= 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input." << endl;
            continue;
        }

        // Check if the move is possible:
        for (int k = 0; k < moves.size(); k++) {
            if (moves[k].row == i - 1 && moves[k].col == j - 1) {
                foundInMoves = true;
            }
        }

        if (!foundInMoves) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Not a legal move." << endl;
            continue;
        }

        // If the move is possible:
        pos.row = i;
        pos.col = j;
        moves.clear();

        return pos;
    }
}

ReversiClient *LocalOnlinePlayer::getClient() {
    return this->client;
}