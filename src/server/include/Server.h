#ifndef REVERSISERVER_SERVER_H
#define REVERSISERVER_SERVER_H

#include "CommandsManager.h"

/**
 * Server portocol description:
 * Connection initialization notification: X - first player, O - second player
 * Player move: RowNumber ' ' ColNumber
 * No more moves: -1 ' ' -1
 * End of game: 0 ' ' 0
 */
struct ServerThreadArgs {
    int serverSocket;
    pthread_mutex_t threadsVector_mutex;
    pthread_mutex_t socketsVector_mutex;
    vector<pthread_t *> *threadsVector;
    CommandsManager *commandsManagerInstance;
    vector<int> *socketsVector;
};

struct ClientThreadArgs {
    int clientSocket;
    vector<pthread_t *> *threadsVector;
    CommandsManager *commandsManagerInstance;
    vector<int> *socketsVector;
};

class Server {
public:


    /**
     * the C'tor of the server.
     * @param port
     */
    Server(int port);

    /**
     * Starts the sever.
     */
    void start();

    /**
     * Stops the server
     */
    void stop();

private:
    int port;
    int serverSocket; // the socket's file descriptor
    int firstPlayerSocket;
    int secondPlayerSocket;
    int currentPlayerSocket;
    pthread_t serverThreadId;
    ServerThreadArgs *threadArgs;
    CommandsManager *commandsManagerInstance;
    vector<pthread_t *> *threadsVector;
    vector<int> *socketsVector;

};


#endif //REVERSISERVER_SERVER_H
