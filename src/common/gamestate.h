#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <array>
#include <tuple>
#include <vector>
#include <iostream>

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

using Board = std::array<std::array<Stone, kBoardSize>, kBoardSize>;

struct GameState {
    enum Stone lastStone = NONE;
    Board board = {NONE};
    std::vector<Board> boardHistory;
    std::vector<Move> moves;
    int moveIdx = 0;

    bool attemptMove(int row, int col, bool addToRecord);
    void boardAtMove(int idx);
    bool coordWithinBoard(int row, int col);
    std::vector<std::tuple<int,int>> getAdjacents(int row, int col);
    int captureMaybe(int row, int col, bool capture);
    void clearBoard(void);
    void next(void);
    void previous(void);
};

std::ostream &operator<<(std::ostream &os, const GameState &gs);

#endif // GAMESTATE_H
