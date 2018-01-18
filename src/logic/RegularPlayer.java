package logic;

import logic.IPlayer;

public class RegularPlayer implements IPlayer {
    private char playerType;

    public RegularPlayer(char pType) {
        this.playerType = pType;
    }
}
