#ifndef SGF_H
#define SGF_H

#include <string>
#include "gamestate.h"

bool readSGF(const std::string &filename, GameState &gs);
bool writeSGF(const std::string &filename, const GameState &gs);

#endif // SGF_H
