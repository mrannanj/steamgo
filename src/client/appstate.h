#ifndef APPSTATE_H
#define APPSTATE_H

#include "common/gamestate.h"
#include "client/go_service_client.h"
#include <string>

struct AppState {
    AppState(const std::string &server_addr);

    GameState gameState;
    bool writeSGF = false;
    std::string sgfFile;
    GoServiceClient goClient;
};

#endif // APPSTATE_H
