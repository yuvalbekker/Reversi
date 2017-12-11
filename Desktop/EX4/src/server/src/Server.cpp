#include "../include/Server.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#define MAX_CONNECTED_CLIENTS 2

using namespace std;

Server::Server(int port) : port(port), serverSocket(0) {
    cout << "Server" << endl;
}

void Server::start() {

    /// Create a socket point
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        throw "Error opening socket";
    }

    // Assign a local address to the socket
    struct sockaddr_in serverAddress;
    bzero((void *) &serverAddress,
          sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(port);
    if (bind(serverSocket, (struct sockaddr
    *) &serverAddress, sizeof(serverAddress)) == -1) {
        throw "Error on binding";
    }



    // Define the client socket's structures
    struct sockaddr_in clientAddress;
    socklen_t clientAddressLen = sizeof((struct sockaddr*) &clientAddress);

    int numberOfConnectedPlayers = 0, iteration = 0;
    while (true) {

        // Start listening to incoming connections
        listen(serverSocket, MAX_CONNECTED_CLIENTS);
        // Wait until two players are connected to the server
        while (numberOfConnectedPlayers != MAX_CONNECTED_CLIENTS) {
            cout << "Waiting for client connections..." << endl;

            // Accept a new client connection
            int clientSocket = accept(serverSocket, (struct
                    sockaddr *) &clientAddress, &clientAddressLen);
            numberOfConnectedPlayers++;
            if (numberOfConnectedPlayers == 1) {
                this->firstPlayerSocket = clientSocket;
                this->currentPlayerSocket = this->firstPlayerSocket;
            } else if (numberOfConnectedPlayers == 2) {
                this->secondPlayerSocket = clientSocket;
            }
            cout << "Client connected" << endl;
            if (clientSocket == -1)
                throw "Error on accept";
        }
        if (iteration == 0) {
            notifyPlayers();
        }
        iteration++;
        int xPosition = 0, yPosition = 0;
        int operation = readPosition(xPosition, yPosition);

        // If there was an error or a client disconnected, start a new game:
        if (operation == 0 || operation == -1) {
            close(this->firstPlayerSocket);
            close(this->secondPlayerSocket);
            numberOfConnectedPlayers = 0;
            iteration = 0;
            continue;
        }

        cout << "The pos to be written is: " << xPosition << "," << yPosition << endl;
        if (xPosition != 0 && yPosition != 0) {
            int operation2 = writePosition(xPosition, yPosition);
            if (operation2 == 0) {
                close(this->firstPlayerSocket);
                close(this->secondPlayerSocket);
                numberOfConnectedPlayers = 0;
            }
        }

        // If the game has ended:
        if (xPosition == 0 && yPosition == 0) {
            close(this->firstPlayerSocket);
            close(this->secondPlayerSocket);
            numberOfConnectedPlayers = 0;
            stop();
        }

        swapPlayersTurn();
        cout << "One move was read and written. " << endl;
    }
}

void Server::stop() {
    close(serverSocket);
}

int Server::readPosition(int &xPosition, int &yPosition) {
    char delimiter = ' ';
    // Read new exercise arguments
    int n = read(this->currentPlayerSocket, &xPosition, sizeof(xPosition));
    if (n == -1) {
        cout << "Error reading xPosition" << endl;
        return -1;
    }
    if (n == 0) {
        cout << "Client disconnected" << endl;
        return -1;
    }
    n = read(this->currentPlayerSocket, &delimiter, sizeof(delimiter));
    if (n == -1) {
        cout << "Error reading delimiter" << endl;
        return -1;
    }
    n = read(this->currentPlayerSocket, &yPosition, sizeof(yPosition));
    if (n == -1) {
        cout << "Error reading yPosition" << endl;
        return -1;
    }
    cout << "Read position: " << xPosition << delimiter << yPosition << endl;
}

void Server::notifyPlayers() {
    char firstPlayerSymbol = 'X';
    char secondPlayerSymbol = 'O';
    int n = write(this->firstPlayerSocket, &firstPlayerSymbol, sizeof(firstPlayerSymbol));
    if (n == -1) {
        cout << "Error writing to socket" << endl;
        return;
    }
    n = write(this->secondPlayerSocket, &secondPlayerSymbol, sizeof(secondPlayerSymbol));
    if (n == -1) {
        cout << "Error writing to socket" << endl;
        return;
    }
}

void Server::swapPlayersTurn() {
    if (this->currentPlayerSocket == this->firstPlayerSocket) {
        this->currentPlayerSocket = this->secondPlayerSocket;
    } else if (this->currentPlayerSocket == this->secondPlayerSocket) {
        this->currentPlayerSocket = this->firstPlayerSocket;
    }
}



int Server::writePosition(int &xPosition, int &yPosition) {
    char delimiter = ' ';
    int n = 0, x = xPosition, y = yPosition;
    if (this->currentPlayerSocket == this->firstPlayerSocket) {
        n = write(this->secondPlayerSocket, &xPosition, sizeof(xPosition));
        n = write(this->secondPlayerSocket, &delimiter, sizeof(delimiter));
        n = write(this->secondPlayerSocket, &yPosition, sizeof(yPosition));
    } else if (this->currentPlayerSocket == this->secondPlayerSocket) {
        n = write(this->firstPlayerSocket, &xPosition, sizeof(xPosition));
        n = write(this->firstPlayerSocket, &delimiter, sizeof(delimiter));
        n = write(this->firstPlayerSocket, &yPosition, sizeof(yPosition));
    }
    cout << "Written position: " << xPosition << delimiter << yPosition << endl;
    return n;
}