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
    enum Stone lastStone = NONE;
    std::array<std::array<Stone, kBoardSize>, kBoardSize> board = {NONE};

    bool coordWithinBoard(int row, int col);
    int captureMaybe(int row, int col, bool capture);
};

#endif // GAMESTATE_H
