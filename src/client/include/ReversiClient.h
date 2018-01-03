#ifndef REVERSICLIENT_H
#define REVERSICLIENT_H

#include "Checker.h"
#include <string.h>
#include <vector>

using namespace std;
#define MAX_COMMAND_LEN 50

class ReversiClient {
public:

    /**
     * The constructor for ReversiClient.
     * @param serverIP
     * @param serverPort
     */
    ReversiClient(const char *serverIP, int serverPort);

    /**
     * The d'tor for ReversiClient.
     */
    ~ReversiClient();

    /**
    * This function connects the client to the server.
    */
    void connectToServer();

    /**
     * This function sends a given move to the server.
     * @param x
     * @param delimiter
     * @param y
     * @return int
     */
    int sendPosition(int x, char delimiter, int y);

    /**
     * Sends the input to the server the returns the result.
     * @param commandString
     * @return int
     */
    int sendCommandToServer(string commandString);

    /**
     * Returns the symbol of the player.
     * @return char
     */
    char getSymbol();

    /**
    * This function reads a move into the given Checker::position.
    */
    int readPosition(Checker::position &pos);

    /**
    * This function reads the player's symbol.
    */
    char readPlayerSymbol();

    /**
     * Returns the socket of the player.
     * @return int
     */
    int getSocket();

//Members:
    char currentPlayerSymbol;

private:
    const char *serverIP;
    int serverPort;
    int clientSocket;
    char symbol;
    string gameName;

    vector<string> parseCommandStr(string commandStr);

};


#endif //REVERSICLIENT_H