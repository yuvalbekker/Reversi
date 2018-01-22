#include "../include/Server.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <stdio.h>


#define MAX_COMMAND_LEN 50
#define MAX_CONNECTIONS 100

static void *acceptClients(void *);

static void *handleClient(void *);

using namespace std;

Server::Server(int port) : port(port), serverSocket(0) {
    cout << "Server" << endl;
    this->pool = new ThreadPool(THREADS_NUM);
    this->serverTasksArgs = new ServerTaskArgs;
    this->tasksVector = new vector<Task *>;
    this->socketsVector = new vector<int>;
    this->serverTasksArgs->tasksVector = this->tasksVector;
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
    listen(this->serverSocket, MAX_CONNECTIONS);
    this->serverTasksArgs->serverSocket = this->serverSocket;
    this->serverTasksArgs->commandsManagerInstance = this->commandsManagerInstance;
    this->serverTasksArgs->socketsVector = this->socketsVector;
    this->serverTasksArgs->pool = this->pool;
    try {
        Task *task = new Task(&acceptClients, (void *) this->serverTasksArgs);
        this->pool->addTask(task);
        this->tasksVector->push_back(task);
    } catch (const char *msg) {
        cout << "Unable to create the acceptClients thread";
        throw msg;
    }
}


static void *acceptClients(void *args) {
    ServerTaskArgs *serverThreadArgs = (ServerTaskArgs *) args;
    long serverSocket = serverThreadArgs->serverSocket;
    ThreadPool *pool = serverThreadArgs->pool;
    bool stopped = false;
    // Define the client socket's structures
    struct sockaddr_in clientAddress;
    socklen_t clientAddressLen = sizeof(clientAddress);
    pthread_mutex_t socketsVector_mutex = serverThreadArgs->socketsVector_mutex;
    while (!stopped) {
        cout << "Waiting for client connections..." << endl;
        // Accept a new client connection
        int clientSocket = accept(serverSocket, (struct sockaddr *) &clientAddress,
                                  &clientAddressLen);
        serverThreadArgs->socketsVector->push_back(clientSocket);
        ClientThreadArgs *clientThreadArgs = new ClientThreadArgs();
        clientThreadArgs->clientSocket = clientSocket;
        clientThreadArgs->commandsManagerInstance = serverThreadArgs->commandsManagerInstance;
        cout << "Client connected" << endl;
        cout << "Socket number: " << clientSocket << endl;
        if (clientSocket == -1)
            throw "Error on accept";
        Task *task = new Task(&handleClient, (void *) clientThreadArgs);
        pool->addTask(task);
        serverThreadArgs->tasksVector->push_back(task);
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
    cout << "Closing all Sockets:" << endl;
    for (int i = 0; i < this->socketsVector->size(); i++) {
        cout << "Close socketId: " << this->socketsVector->at(i) << endl;
        shutdown(this->socketsVector->at(i), SHUT_RDWR);
        close(this->socketsVector->at(i));
    }
    delete this->socketsVector;

    cout << "Closing all tasks." << endl;
    this->pool->terminate();
    for (int i = 0; i < this->tasksVector->size(); i++) {
        delete tasksVector->at(i);
    }
    delete this->pool;
    delete this->tasksVector;

    delete this->commandsManagerInstance;
    cout << "Close server socketId: " << this->serverSocket << endl;
    delete this->serverTasksArgs;

    close(this->serverSocket);
}
