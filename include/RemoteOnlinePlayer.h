#ifndef REVERSI_REMOTEONLINEPLAYER_H
#define REVERSI_REMOTEONLINEPLAYER_H


#include "IPlayer.h"
#include "ReversiClient.h"

class RemoteOnlinePlayer : public  IPlayer {
public:
    /**
     * The constructor.
     * @param playerType
     *
     */
    RemoteOnlinePlayer(ReversiClient* cl);

    /**
     * A virtual d'tor.
     */
    virtual ~RemoteOnlinePlayer();

    /**
    * This function generates a move by reading it from the server.
    */
    Checker::position generatePosition(Checker::position &pos);

private:
    ReversiClient *client;
};


#endif //REVERSI_REMOTEONLINEPLAYER_H
