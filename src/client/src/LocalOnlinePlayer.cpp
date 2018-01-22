#include <cstdlib>
#include <limits>
#include <sstream>
#include <unistd.h>
#include <sys/socket.h>
#include "../include/LocalOnlinePlayer.h"
#include "../include/ConfigReader.h"

using namespace std;

LocalOnlinePlayer::LocalOnlinePlayer() {
    this->playerType = playerType;
    string configurationPath = "clientConfig.txt";
    ConfigReader reader(configurationPath);

    // Read the config file to get the IP and the Port:
    reader.readConfigFile();

    // Create a client and connect to it using the info that was read:
    this->client = new ReversiClient(reader.getIP().c_str(), reader.getPort());
    try {
        client->connectToServer();
        cout << "Connected to server" << endl;
    } catch (const char *msg) {
        close(this->client->getSocket());
        cout << "Error occurred while connecting to server. Reason: " << msg << endl;
        throw "Failed to connect to server";
    }
}

LocalOnlinePlayer::~LocalOnlinePlayer() {
    delete this->client;
}

vector<string> LocalOnlinePlayer::parseCommandStr(string commandStr) {
    string str(commandStr);
    istringstream iss(str);
    vector<string> strArgs;
    while (iss) {
        string arg;
        iss >> arg;
        strArgs.push_back(arg);
    }
    return strArgs;
}

string LocalOnlinePlayer::scanCommand() {
    cout.flush();
    cin.clear();
    string commandStringForSend;
    cout << "Enter command (write 'returntomenu' to dissconnect the server and return back)" << endl;
    cin >> ws;
    getline(cin, commandStringForSend, '\n');
    return commandStringForSend;
}

bool LocalOnlinePlayer::isValidCommand(string command) {
    if (command == "start" || command == "list_games" || command == "join" ||
        command == "play" || command == "close" || command == "returntomenu") {
        return true;
    } else {
        cout
                << "Invalid command! possible commands are ([] = arg):"
                        " start [game_name],"
                        " list_games, "
                        "join [game_name],"
                        " play [x] [y],"
                        " close [game_name],"
                        " returntomenu"
                << endl;
    }
    return false;
}

Checker::position LocalOnlinePlayer::generatePosition(std::vector<Checker::position> &moves, Board &board) {

    // Read the move from the user and return it:
    Checker::position pos = readPositionFromUser(moves);
    return pos;
}

Checker::position LocalOnlinePlayer::readPositionFromUser(std::vector<Checker::position> &moves) {
    Checker::position pos;
    int i = 0;
    int j = 0;

    // Read a move from the user:
    while (true) {
        cout << "\nPlease enter your move in the format: row col. or 'close' in order to exit current game" << endl;
        bool foundInMoves = false;
        string playStr = scanCommand();
        if (playStr == "close") {
            pos.row = -3;
            pos.col = -3;
            return pos;
        } else {
            vector<string> commandVector = parseCommandStr(playStr);
            if (commandVector.size() != 3) {
                cout << "Invalid number of parameters, entered " << commandVector.size() - 1 << " parameters" << endl;
                continue;
            }
            try {
                i = atoi(commandVector.at(0).c_str());
                j = atoi(commandVector.at(1).c_str());
            }
            catch (const char *msg) {
                cout << "Incorrect position format" << endl;
                continue;
            }
            if (i > 8 || i <= 0 || j > 8 || j <= 0) {
                cout << "Invalid input, out of board bounds indices" << endl;
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
}

ReversiClient *LocalOnlinePlayer::getClient() {
    return this->client;
}

int LocalOnlinePlayer::sendCommandToServer() {
    try {
        string commandStringForSend;
        vector<string> commandVector;
        string commandType;
        bool isValidCommandType = false;
        bool canStartGame = false;
        while (!canStartGame) {
            //Scan command from the user
            while (!isValidCommandType) {
                commandStringForSend = scanCommand();
                commandVector = parseCommandStr(commandStringForSend);
                commandType = commandVector.at(0);
                isValidCommandType = isValidCommand(commandType);
            }
            if (commandType == "returntomenu") {
                return -1;
            } else {
                int result = client->sendCommandToServer(commandStringForSend);
                if (result != 0) {
                    canStartGame = true;
                }
                isValidCommandType = false;
            }
        }
        return 1;
    }
    catch (const char *msg) {
        shutdown(this->client->getSocket(), SHUT_RDWR);
        close(this->client->getSocket());
        cout << "Error occurred while initializing command. Reason: " << msg << endl;
        throw "Failed to connect to server";
    }
}

bool LocalOnlinePlayer::initializeGame() {
    int result = sendCommandToServer();
    if (result == 1) {
        this->playerType = this->client->getSymbol();
        cout << "Your symbol is: '" << this->playerType << "'" << endl;
        return true;
    } else if (result == -1) {
        return false;
    }
    return 0;
}

