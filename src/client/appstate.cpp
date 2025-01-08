#include "client/appstate.h"

using std::string;

AppState::AppState(const string &server_addr):
    gameState(),
    writeSGF(false),
    sgfFile(),
    goClient(grpc::CreateChannel(server_addr, grpc::InsecureChannelCredentials()))
{}
