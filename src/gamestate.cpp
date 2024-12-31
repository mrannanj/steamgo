#include "gamestate.h"
#include <stack>
#include <tuple>
#include <QDebug>

using std::stack, std::tuple;

void GameState::attemptMove(int row, int col) {
    if (row < 0)
        return;

    // Only empty spots can be played in.
    if (this->board[row][col] != Stone:: NONE)
        return;

    enum Stone curStone = Stone::BLACK;
    if (this->lastStone == Stone::BLACK)
        curStone = Stone::WHITE;
    this->board[row][col] = curStone;

    // Check if this stone would capture something.
    std::tuple<int,int> adjacents[] = {
        {row+1, col}, {row-1, col},
        {row, col+1}, {row, col-1},
    };
    bool willCapture = false;
    for (auto [adj_row, adj_col] : adjacents) {
        willCapture |= captureMaybe(adj_row, adj_col, false) < 0;
    }

    // No capture, so check that we have at least one liberty.
    if (!willCapture && captureMaybe(row, col, false) < 0) {
        this->board[row][col] = Stone:: NONE;
        return;
    }

    // Capture adjacent 0 liberty groups.
    for (auto [adj_row, adj_col] : adjacents) {
        this->captureMaybe(adj_row, adj_col, true);
    }
    this->lastStone = curStone;

    Move move {
        .row = row,
        .col = col,
        .stone = curStone,
    };
    this->moves.push_back(move);
}

bool GameState::coordWithinBoard(int row, int col) {
    return row >= 0 && row < kBoardSize && col >= 0 && col < kBoardSize;
}

int GameState::captureMaybe(int origRow, int origCol, bool capture) {
    if (!coordWithinBoard(origRow, origCol))
        return 0;
    enum Stone groupColor = board[origRow][origCol];
    if (groupColor == Stone::NONE)
        return 0;

    int ret = 0;
    bool visited[kBoardSize][kBoardSize] = {false};
    stack<tuple<int,int>> group;
    group.push({origRow, origCol});
    while (group.size() > 0) {
        auto [row, col] = group.top();
        group.pop();
        visited[row][col] = true;
        tuple<int,int> adjacents[] = {
            {row+1, col}, {row-1, col}, {row, col+1}, {row, col-1},
        };
        for (auto [adjRow, adjCol] : adjacents) {
            // No liberties outside the board
            if (!coordWithinBoard(adjRow, adjCol))
                continue;
            if (visited[adjRow][adjCol])
                continue;
            enum Stone coordStone = board[adjRow][adjCol];
            if (coordStone == Stone::NONE) {
                ret += 1;
                visited[adjRow][adjCol] = true;
            } else if (coordStone == groupColor) {
                group.push({adjRow, adjCol});
            }
        }
    }

    // Capture on the next call when the capture parameter is true.
    if (!capture)
        return (ret == 0) ? -1 : 0;
    // Group has liberties, not capturing.
    if (capture && ret > 0) {
        return 0;
    }
    group.push({origRow, origCol});
    while (group.size() > 0) {
        auto [row, col] = group.top();
        group.pop();
        board[row][col] = Stone::NONE;

        tuple<int,int> adjacents[] = {
            {row+1, col}, {row-1, col}, {row, col+1}, {row, col-1},
        };
        for (auto [adjRow, adjCol] : adjacents) {
            if (!coordWithinBoard(adjRow, adjCol))
                continue;
            if (board[adjRow][adjCol] == groupColor) {
                group.push({adjRow, adjCol});
            }
        }
    }

    return ret;
}
