#include <iostream>
#include <stdlib.h>
#include "../include/ConfigReader.h"
#include "../include/Server.h"

using namespace std;

int main() {
    try {
        string configurationPath = "serverConfig.txt";
        ConfigReader reader(configurationPath);
        reader.readConfigFile();
        int serverConfiguredPort = reader.getPort();
        Server server(serverConfiguredPort);
        server.start();
        cout << "Enter exit to stop server" << endl;
        bool exit = false;
        while (!exit) {
            cout.flush();
            cin.clear();
            string command;
            cin >> ws;
            getline(cin, command, '\n');
            if (command == "exit") {
                server.stop();
                exit = true;
            }
        }

    } catch (const char *msg) {
        cout << "Cannot start server. Reason: " << msg << endl;
        exit(-1);
    }
}
