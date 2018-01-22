#ifndef REVERSISERVER_SERVER_H
#define REVERSISERVER_SERVER_H

#include "CommandsManager.h"
#include "ThreadPool.h"

/**
 * Server portocol description:
 * Connection initialization notification: X - first player, O - second player
 * Player move: RowNumber ' ' ColNumber
 * No more moves: -1 ' ' -1
 * End of game: 0 ' ' 0
 */

struct ServerTaskArgs {
    int serverSocket;
    pthread_mutex_t socketsVector_mutex;
    vector<Task *> *tasksVector;
    CommandsManager *commandsManagerInstance;
    vector<int> *socketsVector;
    ThreadPool* pool;
};

struct ClientThreadArgs {
    int clientSocket;
    CommandsManager *commandsManagerInstance;
};

#define THREADS_NUM 5

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
    //pthread_t serverThreadId;
    ServerTaskArgs *serverTasksArgs;
    CommandsManager *commandsManagerInstance;
    vector<Task *> *tasksVector;
    vector<int> *socketsVector;
    ThreadPool* pool;
};


#endif //REVERSISERVER_SERVER_H
