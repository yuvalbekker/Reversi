#ifndef REVERSI_CONFIGREADER_H
#define REVERSI_CONFIGREADER_H

#include <iostream>

// This class reads a config file containing an ip add. and a port #.
class ConfigReader {

//Members:
private:
    std::string pathToConfigFile;
    std::string ip;
    int port;

//Constructor & D'tor:
public:
    /**
     * A constructor for a config file reader.
     * @param pathToConfig
     */
    ConfigReader(std::string &pathToConfig);

    /**
    * A D'tor for a config file reader.
    */
    ~ConfigReader();

//Functions:
    /**
    * This function reads the client config file and assigns the IP
    * and port to the members.
    */
    void readConfigFile();

    /**
    * This function reads the server config file and assigns the port
    * to the port field.
    */
    void readServerFile();

    /**
    * This is a getter for the IP address.
    */
    std::string getIP() const;

    /**
    * This is a getter for the port #.
    */
    int getPort() const;

    /**
    * This is a getter for the path to the file.
    */
    std::string getPathToFile() const;
};

#endif //REVERSI_CONFIGREADER_H
