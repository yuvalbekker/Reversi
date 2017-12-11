#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "../include/ReversiClient.h"

using namespace std;

ReversiClient::ReversiClient(const char *serverIP, int serverPort) :
        serverIP(serverIP), serverPort(serverPort),
        clientSocket(0) {
}

void ReversiClient::connectToServer() {
    // Create a socket point
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        throw "Error opening socket";
    }
    // Convert the ip string to a network address
    struct in_addr address;
    if (!inet_aton(serverIP, &address)) {
        throw "Can't parse IP address";
    }
    // Get a hostent structure for the given host address
    struct hostent *server;
    server = gethostbyaddr((const void *) &address, sizeof
            address, AF_INET);
    if (server == NULL) {
        throw "Host is unreachable";
    }
    // Create a structure for the server address
    struct sockaddr_in serverAddress;
    bzero((char *) &address, sizeof(address));
    serverAddress.sin_family = AF_INET;
    memcpy((char *) &serverAddress.sin_addr.s_addr, (char *) server->h_addr, server->h_length);
    // htons converts values between host and network byteorders
    serverAddress.sin_port = htons(serverPort);
    // Establish a connection with the TCP server
    if (connect(clientSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) == -1) {
        throw "Error connecting to server";
    }
}


ReversiClient::~ReversiClient() {

}

int ReversiClient::sendPosition(int x, char delimiter, int y) {
    // Write the exercise arguments to the socket
    int n = write(clientSocket, &x, sizeof(x));
    if (n == -1) {
        throw "Error writing x to socket";
    }
    n = write(clientSocket, &delimiter, sizeof(delimiter));
    if (n == -1) {
        throw "Error writing delimiter to socket";
    }
    n = write(clientSocket, &y, sizeof(y));
    if (n == -1) {
        throw "Error writing y to socket";
    }
    // Read the result from the server
    //int result;
    //n = read(clientSocket, &result, sizeof(result));
    if (n == -1) {
        throw "Error reading result from socket";
    }
    return n;
}

int ReversiClient::readPosition(Checker::position &pos) {
    int bytesRead, row = 0, col = 0;
    char delimiter = ' ';
    bytesRead = read(clientSocket, &row, sizeof(row));
    bytesRead = read(clientSocket, &delimiter, sizeof(delimiter));
    bytesRead = read(clientSocket, &col, sizeof(col));
    if (bytesRead < 0) {
        throw "Error reading from server";
    }
    pos.row = row;
    pos.col = col;
    return bytesRead;
}

int ReversiClient::readCurrentPlayer() {
    int bytesRead;
    char currentPlayerSymbol;
    bytesRead = read(clientSocket, &currentPlayerSymbol, sizeof(currentPlayerSymbol));
    if (bytesRead < 0) {
        throw "Error reading the current player from server";
    }
    this->currentPlayerSymbol = currentPlayerSymbol;

    return bytesRead;
}

char ReversiClient::readPlayerSymbol() {
    char symbol;
    int n = read(this->clientSocket, &symbol, sizeof(symbol));
    if (n == -1) {
        throw "Error reading result from socket";
    }
    return symbol;
}

void ReversiClient::check() {
    cout << "Checked good" << endl;
}