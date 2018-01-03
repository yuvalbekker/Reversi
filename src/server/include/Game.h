#include <string>
#include "Player.h"

#ifndef REVERSISERVER_GAME_H
#define REVERSISERVER_GAME_H
using namespace std;

class Game {
public:
    /**
     *
     * @param name
     */
    Game(string name);

    /**
     *
     * @param name
     * @param player1
     * @param player2
     */
    Game(string name, Player *player1, Player *player2);

    /**
     * The d'tor of the class
     */
    ~Game();

    /**
     * Returns the game name.
     * @return string
     */
    string getGameName();

    /**
     * Returns the first player.
     * @return Player*
     */
    Player *getFirstPlayer();

    /**
     * Returns the second player.
     * @return Player*
     */
    Player *getSecondPlayer();

    /**
     * Setter of sname member
     * @param name
     */
    void setGameName(string name);

    /**
     * Setter of first player member
     * @param player
     */
    void setFirstPlayer(Player *player);

    /**
     * Setter of second player member
     * @param player
     */
    void setSecondPlayer(Player *player);

    /**
     * Return the if the game is fully occupied, otherwise false.
     * @return bool
     */
    bool isBusy();

private:
    string name;
    Player *firstPlayer;
    Player *secondPlayer;
};

#endif //REVERSISERVER_GAME_H
