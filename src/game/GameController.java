package game;

import javafx.beans.property.SimpleStringProperty;
import javafx.beans.property.StringProperty;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.Node;
import javafx.scene.control.Alert;
import javafx.scene.control.Label;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.HBox;
import javafx.scene.paint.Color;
import logic.Board;
import logic.Logic;
import logic.NormalRuleset;
import logic.Position;
import main.ReversiSettings;

import java.net.URL;
import java.util.ArrayList;
import java.util.ResourceBundle;

public class GameController implements Initializable {
    private ReversiSettings reversiSettings;
    private int boardSize;
    private String firstPlayerColor;
    private String secondPlayerColor;
    private String currentPlayerColor;
    private Board gameBoard;
    private NormalRuleset rules;

    @FXML
    private HBox root;
    @FXML
    private Label currentPlayerLabel;
    @FXML
    private Label firstPlayerScore;
    @FXML
    private Label secondPlayerScore;

    public GameController(ReversiSettings settings) {
        restartGame(settings);
    }

    private void restartGame(ReversiSettings settings) {
        reversiSettings = settings;
        firstPlayerColor = reversiSettings.getFirstPlayerColor();
        secondPlayerColor = reversiSettings.getSecondPlayerColor();
        currentPlayerColor = firstPlayerColor;
        boardSize = settings.getGameBorderSize();

        String firstColor = reversiSettings.getFirstPlayerColor();
        String secondColor = reversiSettings.getSecondPlayerColor();
        Color firstConvertedColor = Color.web(firstColor);
        Color secondConvertedColor = Color.web(secondColor);

        gameBoard = new Board(boardSize, firstConvertedColor, secondConvertedColor);
        rules = new NormalRuleset(gameBoard);

        gameBoard.onMouseClickedProperty().setValue(event -> {
            Node source = (Node) event.getTarget();
            Integer colIndex = GridPane.getColumnIndex(source);
            Integer rowIndex = GridPane.getRowIndex(source);
            makeMove(rowIndex, colIndex);
            event.consume();
        });
    }

    private void makeMove(int rowNumber, int columnNumber) {
        boolean isLegalMove = false;
        ArrayList<Position> positionArrayList = rules.calcPossibleMoves(getPlayerByColor(currentPlayerColor));
        if (positionArrayList.size() == 0) {
            switchCurrentPlayer();
            if (rules.calcPossibleMoves(getPlayerByColor(currentPlayerColor)).size() == 0) {
                Alert alert = new Alert(Alert.AlertType.INFORMATION);
                alert.setTitle("Game Over");
                alert.setHeaderText("Thanks for playing");
                alert.setContentText("Passing turn to " + currentPlayerColor + " player");
                alert.showAndWait();
                restartGame(reversiSettings);
            } else {
                Alert alert = new Alert(Alert.AlertType.INFORMATION);
                alert.setTitle("No Possible Moves!");
                alert.setHeaderText("Passing the turn to the opponent");
                alert.setContentText("Passing turn to " + currentPlayerColor + " player");
                alert.showAndWait();
            }
        } else {
            int i = 0;
            for (i = 0; i < positionArrayList.size(); i++) {
                System.out.print("\nA possible move is " + (positionArrayList.get(i).getPosition().row + 1) +
                        " , " + (positionArrayList.get(i).getPosition().col + 1));
            }

            for (i = 0; i < positionArrayList.size(); i++) {
                if (positionArrayList.get(i).row == rowNumber && positionArrayList.get(i).col == columnNumber) {
                    isLegalMove = true;
                    break;
                }
            }
            if (isLegalMove) {
                Position positionToMake = new Position(rowNumber + 1, columnNumber + 1);
                Logic.Player playerType = getPlayerByColor(currentPlayerColor);
                rules.makeMove(positionToMake, playerType);
                gameBoard.updateBoardDraw(rowNumber, columnNumber);
                gameBoard.draw();
                switchCurrentPlayer();

            } else {
                Alert alert = new Alert(Alert.AlertType.INFORMATION);
                alert.setTitle("Illegal Move!");
                alert.setHeaderText("Entered move is illegal");
                alert.setContentText((rowNumber+1) + "," + (columnNumber+1));
                alert.showAndWait();
            }
            firstPlayerScore.setText(firstPlayerColor + " player score: " +
                    gameBoard.countPlayersCheckers('O'));
            secondPlayerScore.setText(secondPlayerColor + " player score: " +
                    gameBoard.countPlayersCheckers('X'));
        }
    }


    private void switchCurrentPlayer() {
        if (currentPlayerColor == firstPlayerColor) {
            currentPlayerColor = secondPlayerColor;
        } else if (currentPlayerColor == secondPlayerColor) {
            currentPlayerColor = firstPlayerColor;
        }
        currentPlayerLabel.setText(currentPlayerColor);
    }

    private Logic.Player getPlayerByColor(String color) {
        if (color == firstPlayerColor) {
            return Logic.Player.White;
        } else if (color == secondPlayerColor) {
            return Logic.Player.Black;
        }
        return null;
    }

    @Override
    public void initialize(URL location, ResourceBundle resources) {
        currentPlayerLabel.setText(reversiSettings.getFirstPlayerColor());
        firstPlayerScore.setText(firstPlayerColor + " player score: " +
                gameBoard.countPlayersCheckers('O'));
        secondPlayerScore.setText(secondPlayerColor + " player score: " +
                gameBoard.countPlayersCheckers('X'));

        root.getChildren().add(0, gameBoard);
        root.widthProperty().addListener((observable, oldValue, newValue) -> {
            double boardNewWidth = newValue.doubleValue() - 220;
            gameBoard.setPrefWidth(boardNewWidth);
            gameBoard.draw();
        });
        root.heightProperty().addListener((observable, oldValue, newValue) -> {
            gameBoard.setPrefHeight(newValue.doubleValue());
            gameBoard.draw();
        });
    }
}
