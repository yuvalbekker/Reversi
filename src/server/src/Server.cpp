#include "../include/Server.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <stdio.h>


#define MAX_COMMAND_LEN 50

static void *acceptClients(void *);

static void *handleClient(void *);

using namespace std;

Server::Server(int port) : port(port), serverSocket(0), serverThreadId(0) {
    cout << "Server" << endl;
    this->threadArgs = new ServerThreadArgs;
    this->threadsVector = new vector<pthread_t *>;
    this->socketsVector = new vector<int>;
    this->threadArgs->threadsVector = this->threadsVector;
    this->commandsManagerInstance = CommandsManager::getInstance();
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

    // Reduce downtime of port:	
    int temp = 1;
    setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &temp, sizeof(temp));
    if (bind(serverSocket, (struct sockaddr
    *) &serverAddress, sizeof(serverAddress)) == -1) {
        throw "Error on binding";
    }

    // Start listening to incoming connection requests
    listen(this->serverSocket, INT32_MAX);
    this->threadArgs->serverSocket = this->serverSocket;
    this->threadArgs->commandsManagerInstance = this->commandsManagerInstance;
    this->threadArgs->socketsVector = this->socketsVector;
    int result;
    try {
        result = pthread_create(&serverThreadId, NULL, &acceptClients, (void *) this->threadArgs);
        this->threadArgs->threadsVector->push_back(&serverThreadId);
    } catch (const char *msg) {
        cout << "Unable to create the acceptClients thread";
        throw msg;
    }
    if (result != 0) {
        cout << "Unable to create the acceptClients thread";
        throw;
    }
}


static void *acceptClients(void *args) {
    ServerThreadArgs *serverThreadArgs = (ServerThreadArgs *) args;
    long serverSocket = serverThreadArgs->serverSocket;
    bool stopped = false;
    // Define the client socket's structures
    struct sockaddr_in clientAddress;
    socklen_t clientAddressLen = sizeof(clientAddress);
    pthread_mutex_t threadsVector_mutex = serverThreadArgs->threadsVector_mutex;
    pthread_mutex_t socketsVector_mutex = serverThreadArgs->socketsVector_mutex;
    while (!stopped) {
        cout << "Waiting for client connections..." << endl;
        // Accept a new client connection
        int clientSocket = accept(serverSocket, (struct sockaddr *) &clientAddress,
                                  &clientAddressLen);
        pthread_mutex_lock(&socketsVector_mutex);
        serverThreadArgs->socketsVector->push_back(clientSocket);
        pthread_mutex_unlock(&socketsVector_mutex);

        ClientThreadArgs *clientThreadArgs = new ClientThreadArgs();
        clientThreadArgs->clientSocket = clientSocket;
        clientThreadArgs->threadsVector = serverThreadArgs->threadsVector;
        clientThreadArgs->commandsManagerInstance = serverThreadArgs->commandsManagerInstance;
        clientThreadArgs->socketsVector = serverThreadArgs->socketsVector;
        cout << "Client connected" << endl;
        if (clientSocket == -1)
            throw "Error on accept";
        pthread_mutex_lock(&threadsVector_mutex);
        pthread_t threadId;
        pthread_create(&threadId, NULL, &handleClient, (void *) clientThreadArgs);
        clientThreadArgs->threadsVector->push_back(&threadId);
        pthread_mutex_unlock(&threadsVector_mutex);
    }
}

static void *handleClient(void *args) {
    ClientThreadArgs *clientThreadArgs = (ClientThreadArgs *) args;
    long clientSocket = clientThreadArgs->clientSocket;
    char commandStr[MAX_COMMAND_LEN];
    bool clientConnected = true;
    while (clientConnected) {
        // Read the command from the socket
        int n = recv(clientSocket, commandStr, MAX_COMMAND_LEN, MSG_NOSIGNAL);
        if (n == -1) {
            cout << "Error reading command" << endl;
            delete clientThreadArgs;
            return NULL;
        } else if (n == 0) {
            cout << "Client disconnected" << endl;
            clientConnected = false;
        } else {
            cout << "Received command: " << commandStr << endl;
            // Split the command string to the command name and the arguments
            string str(commandStr);
            istringstream iss(str);
            string command;
            iss >> command;
            vector<string> strArgs;
            while (iss) {
                string arg;
                iss >> arg;
                strArgs.push_back(arg);
            }
            clientThreadArgs->commandsManagerInstance->executeCommand(command, strArgs, clientSocket);
        }
    }
    delete clientThreadArgs;
    return NULL;
}

void Server::stop() {
    cout << "Stopping the server..." << endl;
    for (int i = 0; i < this->socketsVector->size(); i++) {
        cout << "Close socketId: " << this->socketsVector->at(i) << endl;
        shutdown(this->socketsVector->at(i),SHUT_RDWR);
        close(this->socketsVector->at(i));
    }
    cout << "Closing all threads:" << endl;
    for (int i = 0; i < this->threadsVector->size(); i++) {
        cout << "Close threadId: " << *this->threadsVector->at(i) << endl;
        pthread_cancel(*threadsVector->at(i));
    }
    cout << "Closing all sockets:" << endl;
    for (int i = 0; i < this->socketsVector->size(); i++) {
        cout << "Close socketId: " << this->socketsVector->at(i) << endl;
        shutdown(this->socketsVector->at(i),SHUT_RDWR);
        close(this->socketsVector->at(i));
    }

    delete this->commandsManagerInstance;
    cout << "Close server socketId: " << this->serverSocket << endl;
    delete this->threadArgs;

    close(this->serverSocket);
}
