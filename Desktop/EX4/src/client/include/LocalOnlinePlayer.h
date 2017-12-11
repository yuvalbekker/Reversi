#ifndef REVERSI_LOCALONLINEPLAYER_H
#define REVERSI_LOCALONLINEPLAYER_H


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

    virtual ~LocalOnlinePlayer();

    Checker::position generatePosition(std::vector<Checker::position> &moves, Board &board);

    /**
     * Returns the tcp client object.
     * @return ReversiClient
     */
    ReversiClient *getClient();

private:
    /**
     * Read a move from the user.
     * @param moves
     * @return Checker::position
     */
    Checker::position readPositionFromUser(std::vector<Checker::position> &moves);

    ReversiClient *client;
};


#endif //REVERSI_LOCALONLINEPLAYER_H
