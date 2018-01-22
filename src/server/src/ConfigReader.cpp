#include <fstream>
#include <stdlib.h>
#include "../include/ConfigReader.h"

using namespace std;

ConfigReader::ConfigReader(string &pathToConfig) : pathToConfigFile(pathToConfig), ip("127.0.0.1"), port(5577) {

};

int ConfigReader::readConfigFile() {
    ifstream configFile;

    // Open the config file:
    configFile.open(pathToConfigFile.c_str());
    string buffer, strIP = "IP ", strPort = "PORT ";

    if (configFile.is_open()) {
        while (getline(configFile, buffer)) {

            // Look for IP or PORT in the file, and get the IP address
            // and port #:
            if (buffer.find(strIP) != buffer.npos) {
                unsigned long indicator = buffer.find(strIP);
                buffer.erase(0, indicator + strIP.length());
                ip = buffer;
            }
            if (buffer.find(strPort) != buffer.npos) {
                unsigned long indicator = buffer.find(strPort);
                buffer.erase(0, indicator + strPort.length());
                port = atoi(buffer.c_str());
            }
        }
    } else {
        cout << "Config file could not be read." << endl;
        configFile.close();
        return -1;
    }
    configFile.close();
    return 1;
}

void ConfigReader::readServerFile() {
    ifstream configFile;
    string buf;
    configFile.open(pathToConfigFile.c_str());
    if (configFile.is_open()) {
        getline(configFile, buf);
        if (!buf.empty()) {
            port = atoi(buf.c_str());
        }
    }
    configFile.close();
}

ConfigReader::~ConfigReader() {

}

string ConfigReader::getIP() const {
    return ip;
}

int ConfigReader::getPort() const {
    return port;
}

std::string ConfigReader::getPathToFile() const {
    return pathToConfigFile;
}