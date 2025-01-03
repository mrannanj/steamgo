#ifndef APPSTATE_H
#define APPSTATE_H

#include "gamestate.h"
#include <string>

struct AppState {
    GameState gameState;
    bool writeSGF = false;
    std::string sgfFile;
};

#endif // APPSTATE_H
