#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sstream>
#include <cstdlib>
#include "../include/ReversiClient.h"

using namespace std;

ReversiClient::ReversiClient(const char *serverIP, int serverPort) :
        serverIP(serverIP), serverPort(serverPort),
        clientSocket(0) {
    this->gameName = "";
}

void ReversiClient::connectToServer() {

    // Create a socket:
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        throw "Error opening socket";
    }
    // Convert the ip string to a network address:
    struct in_addr address;
    if (!inet_aton(serverIP, &address)) {
        throw "Can't parse IP address";
    }

    // Get a hostent structure for the given host address:
    struct hostent *server;
    server = gethostbyaddr((const void *) &address, sizeof
            address, AF_INET);
    if (server == NULL) {
        throw "Host is unreachable";
    }

    // Create a structure for the server address:
    struct sockaddr_in serverAddress;
    bzero((char *) &address, sizeof(address));
    serverAddress.sin_family = AF_INET;
    memcpy((char *) &serverAddress.sin_addr.s_addr, (char *) server->h_addr, server->h_length);
    serverAddress.sin_port = htons(serverPort);

    // Establish a connection with the TCP server:
    if (connect(clientSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) == -1) {
        throw "Server is down";
    }
}


ReversiClient::~ReversiClient() {
    close(this->clientSocket);
}

int ReversiClient::sendPosition(int x, char delimiter, int y) {
    string commandString = "play ";
    if (x == -3 && y == -3) {
        commandString = "close";
    } else {
        stringstream ss;
        ss << x;
        string str = ss.str();
        commandString += str + delimiter;
        stringstream ss2;
        ss2 << y;
        str = ss2.str();
        commandString += str;
    }
    int result = sendCommandToServer(commandString);
    return result;
}

int ReversiClient::readPosition(Checker::position &pos) {
    int bytesRead, row = 0, col = 0;
    char positionString[MAX_COMMAND_LEN];
    bytesRead = recv(clientSocket, positionString, sizeof(positionString), MSG_NOSIGNAL);
    if (positionString == "exit") {
        close(this->clientSocket);
        throw "Error reading command to socket";
    }
    if (bytesRead == 0) {
        //close(this->clientSocket);
        throw "Error reading command to socket";
    }
    vector<string> splitPosition = parseCommandStr(positionString);
    row = atoi(splitPosition.at(0).c_str());
    col = atoi(splitPosition.at(1).c_str());
    // Update the position argument:
    pos.row = row;
    pos.col = col;
    return bytesRead;
}

char ReversiClient::readPlayerSymbol() {
    char symbol;
    // Read the player's symbol:
    int n = recv(this->clientSocket, &symbol, sizeof(symbol), MSG_NOSIGNAL);
    if (n == 0) {
        close(this->clientSocket);
        throw "Error reading symbol from socket";
    }
    return symbol;
}

int ReversiClient::sendCommandToServer(string commandString) {
    bool commandSentSuccessfully = false;
    while (!commandSentSuccessfully) {
        bool isValidCommandType = false;
        string commandStringForSend = commandString;
        vector<string> commandVector = parseCommandStr(commandStringForSend);
        string commandType = commandVector.at(0);;

        //Send the input command to the server
        int n = send(clientSocket, commandStringForSend.data(), sizeof(commandStringForSend), MSG_NOSIGNAL);
        if (n == 0) {
            close(this->clientSocket);
            throw "Error sending command to socket";
        }
        //Read the result sent from the server according to the command
        if (commandType == "start") {
            long startGameResult = 0;
            n = recv(clientSocket, &startGameResult, MAX_COMMAND_LEN, MSG_NOSIGNAL);
            if (n == 0) {
                close(this->clientSocket);
                throw "Error reading command from socket";
            }
            if (startGameResult == -1) {
                cout << "Game already exist" << endl;
                return 0;
            } else if (startGameResult == 1) {
                //this->symbol = 'X';
                this->gameName = commandVector.at(1);
                cout << "Game '" << this->gameName << "' created successfully" << endl;
                commandSentSuccessfully = true;
                cout << "Waiting for other player to join '" << this->gameName << "'..." << endl;
                this->symbol = this->readPlayerSymbol();
                return 1;
            }
        }
        if (commandType == "list_games") {
            char result[MAX_COMMAND_LEN];
            n = recv(clientSocket, result, MAX_COMMAND_LEN, MSG_NOSIGNAL);
            if (n == 0) {
                close(this->clientSocket);
                throw "Error reading command from socket";
            }
            cout << "Available games:" << endl;
            cout << result << endl;
            return 0;
        }
        if (commandType == "join") {
            char secondPlayerSymbol;
            n = recv(clientSocket, &secondPlayerSymbol, sizeof(secondPlayerSymbol), MSG_NOSIGNAL);
            if (secondPlayerSymbol == -1) {
                cout << "Game doesn't exist, couldn't join game" << endl;
                return 0;
            } else {
                this->gameName = commandVector.at(1);
                cout << "Joined game '" << this->gameName << "' successfully" << endl;
                commandSentSuccessfully = true;
                this->symbol = secondPlayerSymbol;
                return 1;
            }
        }
        if (commandType == "play") {
            commandSentSuccessfully = true;
        }
        if (commandType == "close") {
            Checker::position closeMessagePosition;
            readPosition(closeMessagePosition);
            if (closeMessagePosition.row == -4 && closeMessagePosition.col == -4) {
                cout << "Game '" << this->gameName << "' closed successfully" << endl;
                return 2;
            } else if (closeMessagePosition.row == -2 && closeMessagePosition.col == -2) {
                cout << "Not a game member" << endl;
                return 0;
            }
        }
    }
    return 1;
}

vector<string> ReversiClient::parseCommandStr(string commandStr) {
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

char ReversiClient::getSymbol() {
    return this->symbol;
}

int ReversiClient::getSocket() {
    return this->clientSocket;
}
