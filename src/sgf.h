#ifndef SGF_H
#define SGF_H

#include <string>
#include "gamestate.h"

bool readSGF(const std::string &filename, GameState &gs);

#endif // SGF_H
