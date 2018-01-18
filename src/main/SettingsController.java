package main;

import game.GameController;
import javafx.beans.property.IntegerProperty;
import javafx.beans.property.SimpleIntegerProperty;
import javafx.beans.property.SimpleStringProperty;
import javafx.beans.property.StringProperty;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.control.TextField;
import javafx.scene.layout.HBox;
import javafx.scene.layout.StackPane;
import javafx.scene.layout.VBox;
import javafx.scene.paint.Color;
import javafx.stage.Stage;

import javax.xml.bind.JAXBContext;
import javax.xml.bind.JAXBException;
import javax.xml.bind.Marshaller;
import javax.xml.bind.Unmarshaller;
import java.io.File;
import java.io.IOException;
import java.net.URL;
import java.util.ResourceBundle;

public class SettingsController implements Initializable {
    public SettingsController() {
        size = new SimpleIntegerProperty(0);
        firstPlayerColor = new SimpleStringProperty("");
        secondPlayerColor = new SimpleStringProperty("");
        result = new SimpleStringProperty("");
    }

    public void setSettings(ReversiSettings reversiSettings, String settingsPath) {
        size.setValue(reversiSettings.getGameBorderSize());
        firstPlayerColor.setValue(reversiSettings.getFirstPlayerColor());
        secondPlayerColor.setValue(reversiSettings.getSecondPlayerColor());
        settingsFilePath = settingsPath;
        settings = reversiSettings;
    }

    @FXML
    public VBox root;
    @FXML
    public TextField firstPlayerField;
    @FXML
    public TextField secondPlayerField;
    @FXML
    public TextField sizeField;
    private IntegerProperty size;
    private StringProperty firstPlayerColor;
    private StringProperty secondPlayerColor;
    private String settingsFilePath;
    private StringProperty result;
    private ReversiSettings settings;

    public void setResult(String value) {
        result.set(value);
    }

    public StringProperty resultProperty() {
        return result;
    }

    public String getResult() {
        return result.get();
    }

    public void setSize(int value) {
        size.set(value);
    }

    public IntegerProperty sizeProperty() {
        return size;
    }

    public int getSize() {
        return size.get();
    }

    public void setFirstPlayerColor(String value) {
        firstPlayerColor.set(value);
    }

    public StringProperty firstPlayerColorProperty() {
        return firstPlayerColor;
    }

    public String getFirstPlayerColor() {
        return firstPlayerColor.get();
    }

    public void setSecondPlayerColor(String value) {
        secondPlayerColor.set(value);
    }

    public StringProperty secondPlayerColorProperty() {
        return secondPlayerColor;
    }

    public String getSecondPlayerColor() {
        return secondPlayerColor.get();
    }

    @Override
    public void initialize(URL location, ResourceBundle resources) {

    }

    @FXML
    public void handleSaveAction(ActionEvent actionEvent) {
        result.setValue("");
        JAXBContext jaxbContext = null;
        try {
            jaxbContext = JAXBContext.newInstance(ReversiSettings.class);
        } catch (JAXBException e) {
            e.printStackTrace();
            result.setValue("Error occured while saving");
        }
        Marshaller jaxbMarshaller = null;
        try {
            jaxbMarshaller = jaxbContext.createMarshaller();

        } catch (JAXBException e) {
            e.printStackTrace();
            result.setValue("Error occured while saving");
        }
        try {
            jaxbMarshaller.marshal(new ReversiSettings(firstPlayerField.getText(),
                            secondPlayerField.getText(),
                            Integer.parseInt(sizeField.getText())),
                    new File(settingsFilePath));
        } catch (JAXBException e) {
            e.printStackTrace();
            result.setValue("Error occured while saving");
        }
        result.setValue("Settings saved successfully!");
    }

    public void handleExitAction(ActionEvent actionEvent) {
        System.exit(0);
    }

    public void handleMainWindowAction(ActionEvent actionEvent) throws IOException {
        FXMLLoader loader = new FXMLLoader(getClass().getResource("main.fxml"));
        Stage primStage = (Stage) root.getScene().getWindow();
        primStage.setTitle("Reversi");
        StackPane pane = loader.load();
        root.getChildren().setAll(pane);
    }

    public void handleStartAction(ActionEvent actionEvent) throws IOException {
        /*FXMLLoader loader = new FXMLLoader(getClass().getResource("../game/game.fxml"));
        Stage primStage = (Stage) root.getScene().getWindow();
        primStage.setWidth(800);
        primStage.setHeight(600);
        primStage.setResizable(true);
        GameController controller = new GameController(settings);
        loader.setController(controller);
        HBox pane = loader.load();
        root.getChildren().setAll(pane);*/
    }
}
