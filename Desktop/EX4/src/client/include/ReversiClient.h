#ifndef REVERSI_REVERSICLIENT_H
#define REVERSI_REVERSICLIENT_H
#include "Checker.h"

class ReversiClient {
public:
    ReversiClient(const char *serverIP, int serverPort);
    ~ReversiClient();
    void connectToServer();


    int sendPosition(int x, char delimiter, int y);
    int readPosition(Checker::position &pos);

    char readPlayerSymbol();
    int readCurrentPlayer();
    void check();

//Members:

    char currentPlayerSymbol;

private:
    const char *serverIP;
    int serverPort;
    int clientSocket;
};


#endif //REVERSI_REVERSICLIENT_H