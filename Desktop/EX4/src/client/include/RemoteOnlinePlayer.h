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


    virtual ~RemoteOnlinePlayer();

    Checker::position generatePosition(Checker::position &pos);

private:
    ReversiClient *client;
};


#endif //REVERSI_REMOTEONLINEPLAYER_H
