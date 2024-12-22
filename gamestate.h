#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <array>

constexpr unsigned kBoardSize = 19;

enum Stone {
    NONE,
    BLACK,
    WHITE,
};

struct GameState {
    std::array<std::array<Stone, kBoardSize>, kBoardSize> board = {NONE};
};

#endif // GAMESTATE_H
