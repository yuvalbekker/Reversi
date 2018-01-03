#ifndef REVERSISERVER_PLAYER_H
#define REVERSISERVER_PLAYER_H

class Player {
public:
    /**
     * The c'tor of the class
     * @param socket
     */
    Player(int socket);

    /**
     * The c'tor of the class
     * @param symbol
     */
    Player(char symbol);

    /**
     * The c'tor of the class
     */
    Player();

    /**
     * The c'tor of the class
     * @param socket
     * @param symbol
     */
    Player(int socket, char symbol);

    /**
     * The d'tor of the class
     */
    ~Player();

    /**
     * Return the socket of the player
     * @return int
     */
    int getSocket();

    /**
     * Return the symbol of the player
     * @return char
     */
    char getSymbol();

    /**
     * The setter of the socket member
     * @param socket
     */
    void setSocket(int socket);

    /**
     * The setter og the symbol
     * @param symbol
     */
    void setSymbol(char symbol);

    /**
     * Return true if the player is connected, otherwise false
     * @return bool
     */
    bool isConnected();

    /**
     * Disconnect the player
     */
    void disconnect();

    /**
     * Closes the game of the player
     */
    void closeGame();

private:
    int socket;
    char symbol;
};

#endif //REVERSISERVER_PLAYER_H
