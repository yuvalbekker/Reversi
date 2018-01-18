package main;

import game.GameController;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.layout.*;
import javafx.stage.Stage;

import javax.xml.bind.JAXBContext;
import javax.xml.bind.JAXBException;
import javax.xml.bind.Unmarshaller;
import java.io.File;
import java.io.IOException;
import java.net.URL;
import java.util.ResourceBundle;

public class MainController implements Initializable {

    private ReversiSettings settings;
    private String settingsFilePath;

    @FXML
    private StackPane rootPane;

    @Override
    public void initialize(URL location, ResourceBundle resources) {
        //settings = new ReversiSettings(Color.BLACK, Color.WHITE, 8);
        /*String color = "red";
        Color c = Color.web(color);*/
        settingsFilePath = "GameSettings.xml";
        JAXBContext jaxbContext = null;
        try {
            jaxbContext = JAXBContext.newInstance(ReversiSettings.class);
        } catch (JAXBException e) {
            e.printStackTrace();
        }
        Unmarshaller jaxbUnmarshaller = null;
        try {
            jaxbUnmarshaller = jaxbContext.createUnmarshaller();

        } catch (JAXBException e) {
            e.printStackTrace();
        }
        try {
            settings = (ReversiSettings) jaxbUnmarshaller.unmarshal(new File(settingsFilePath));
        } catch (JAXBException e) {
            e.printStackTrace();
        }
    }

    @FXML
    protected void handleSettingsAction(ActionEvent actionEvent) throws IOException {
        FXMLLoader loader = new FXMLLoader(getClass().getResource("settings.fxml"));
        Stage primStage = (Stage) rootPane.getScene().getWindow();
        primStage.setTitle("Settings");
        VBox pane = loader.load();
        SettingsController controller = loader.getController();
        controller.setSettings(settings, settingsFilePath);
        rootPane.getChildren().setAll(pane);
    }

    @FXML
    protected void handleExitAction(ActionEvent actionEvent) {
        System.exit(0);
    }

    public void handleStartAction(ActionEvent actionEvent) throws IOException {
        FXMLLoader loader = new FXMLLoader(getClass().getResource("../game/game.fxml"));
        Stage primStage = (Stage) rootPane.getScene().getWindow();
        primStage.setWidth(800);
        primStage.setHeight(600);
        primStage.setResizable(true);
        GameController controller = new GameController(settings);
        loader.setController(controller);
        HBox pane = loader.load();
        rootPane.getChildren().setAll(pane);
    }
}
