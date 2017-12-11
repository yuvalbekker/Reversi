#include <iostream>
#include <stdlib.h>
#include "../include/ConfigReader.h"
#include "../include/Server.h"

using namespace std;

int main() {
    string configurationPath = "serverConfig.txt";
    ConfigReader reader(configurationPath);
    reader.readConfigFile();
    int serverConfiguredPort = reader.getPort();
    Server server(serverConfiguredPort);
    try {
        server.start();
    } catch (const char *msg) {
        cout << "Cannot start server. Reason: " << msg << endl;
        exit(-1);
    }
}
