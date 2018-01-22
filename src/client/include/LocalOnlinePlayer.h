#ifndef LOCALONLINEPLAYER_H
#define LOCALONLINEPLAYER_H


#include "IPlayer.h"
#include "ReversiClient.h"

class LocalOnlinePlayer : public IPlayer {
public:
    /**
     * The constructor.
     * @param playerType
     *
     */
    LocalOnlinePlayer();

    /**
    * This is a virtual d'tor.
    */
    virtual ~LocalOnlinePlayer();

    /**
    * This function generates a move by getting
    * input from the user, then sending it to the server.
    */
    Checker::position generatePosition(std::vector<Checker::position> &moves, Board &board);

    /**
     * Returns the tcp client object.
     * @return ReversiClient
     */
    ReversiClient *getClient();

    /**
     * Manages the command sending to the server
     * @return int
     */
    int sendCommandToServer();

    /**
     * Initializes the game
     * @return bool
     */
    bool initializeGame();

private:
    /**
     * Read a move from the user.
     * @param moves
     * @return Checker::position
     */
    Checker::position readPositionFromUser(std::vector<Checker::position> &moves);

    /**
     * Rad a command from the user
     * @return the scanned command
     */
    string scanCommand();

    /**
     * Return true if the input command is valid, otherwise false.
     * @param command
     * @return bool
     */
    bool isValidCommand(string command);

    /**
     * Parse the input command to a vector of strings
     * @param commandStr
     * @return vector<string>
     */
    vector<string> parseCommandStr(string commandStr);

    ReversiClient *client;

};


#endif //REVERSI_LOCALONLINEPLAYER_H
