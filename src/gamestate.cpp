#include "gamestate.h"
#include <stack>
#include <tuple>
#include <QDebug>

using std::stack, std::tuple;

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
