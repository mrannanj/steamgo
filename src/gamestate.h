#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <array>
#include <vector>

constexpr unsigned kBoardSize = 19;

enum Stone {
    NONE,
    BLACK,
    WHITE,
};

struct Move {
    int row = -1;
    int col = -1;
    enum Stone stone = NONE;
};

struct GameState {
    enum Stone lastStone = NONE;
    std::array<std::array<Stone, kBoardSize>, kBoardSize> board = {NONE};
    std::vector<Move> moves;

    bool coordWithinBoard(int row, int col);
    int captureMaybe(int row, int col, bool capture);
};

#endif // GAMESTATE_H