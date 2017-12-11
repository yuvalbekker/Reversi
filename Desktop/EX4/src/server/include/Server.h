#ifndef REVERSISERVER_SERVER_H
#define REVERSISERVER_SERVER_H

/**
 * Server portocol description:
 * Connection initialization notification: X - first player, O - second player
 * Player move: RowNumber ' ' ColNumber
 * No more moves: -1 ' ' -1
 * End of game: 0 ' ' 0
 */
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

    void notifyPlayers();

    /**
     * Read and parse the position send to the current players socket.
     * @param xPosition
     * @param yPosition
     * @return int
     */
    int readPosition(int &xPosition, int &yPosition);

    /**
     * Send the other player the last opponent move.
     * @param xPosition
     * @param yPosition
     * @return int
     */
    int writePosition(int &xPosition, int &yPosition);

    /**
     * Change the current player socket.
     */
    void swapPlayersTurn();

};


#endif //REVERSISERVER_SERVER_H
