package main;

import javafx.scene.paint.Color;

import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlRootElement;

@XmlRootElement(name = "ReversiSettings")
public class ReversiSettings {
    private String firstPlayerColor;
    private String secondPlayerColor;
    private int gameBorderSize;

    public ReversiSettings(){

    }
    public ReversiSettings(String first, String second, int size) {
        firstPlayerColor = first;
        secondPlayerColor = second;
        gameBorderSize = size;
    }

    public String getFirstPlayerColor() {
        return firstPlayerColor;
    }

    public String getSecondPlayerColor() {
        return secondPlayerColor;
    }

    public int getGameBorderSize() {
        return gameBorderSize;
    }

    @XmlElement(name = "FirstPlayerColor")
    public void setFirstPlayerColor(String color) {
        firstPlayerColor = color;
    }
    @XmlElement(name = "SecondPlayerColor")
    public void setSecondPlayerColor(String color) {
        secondPlayerColor = color;
    }
    @XmlElement(name = "GameBorderSize")
    public void setGameBorderSize(int size) {
        gameBorderSize = size;
    }
}
