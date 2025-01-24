#include <iostream>
#include "client/appstate.h"

using std::cout, std::endl, std::string;

AppState::AppState(const string &server_addr):
    gameState(),
    writeSGF(false),
    sgfFile(),
    goClient(grpc::CreateChannel(server_addr, grpc::InsecureChannelCredentials()))
{
    bool success = goClient.hello();
    cout << "Connecting to server succeeded: " << success << endl;
    cout << "Client type: " << goClient.getClientType() << endl;
}
