#include "gamestate.h"
#include <stack>
#include <tuple>

using std::stack, std::tuple, std::ostream, std::vector;

void GameState::attemptMove(int row, int col, bool addToRecord) {
    // Only add the stone if we are looking at the latest board situation.
    if (addToRecord && moveIdx != (int)this->moves.size())
        return;

    enum Stone curStone = Stone::BLACK;
    if (this->lastStone == Stone::BLACK)
        curStone = Stone::WHITE;

    // Ugly special case for pass.
    if (row < 0 && col < 0) {
        this->lastStone = curStone;
        if (!addToRecord)
            return;
        Move move {
            .row = -1,
            .col = -1,
            .stone = curStone,
        };
        this->moves.push_back(move);
        this->moveIdx += 1;
        return;
    }

    // Only empty spots can be played in.
    if (this->board[row][col] != Stone:: NONE)
        return;

    // Place the stone on board temporarily.
    this->board[row][col] = curStone;

    // Check if this stone would capture something.
    vector<tuple<int,int>> adjacents = getAdjacents(row, col);
    bool willCapture = false;
    for (auto [adj_row, adj_col] : adjacents) {
        if (this->board[adj_row][adj_col] != curStone)
            willCapture |= captureMaybe(adj_row, adj_col, false) < 0;
    }

    // No capture, so check that we have at least one liberty.
    if (!willCapture && captureMaybe(row, col, false) < 0) {
        this->board[row][col] = Stone:: NONE;
        return;
    }

    // Capture adjacent 0 liberty groups.
    for (auto [adj_row, adj_col] : adjacents) {
        if (this->board[adj_row][adj_col] != curStone)
            this->captureMaybe(adj_row, adj_col, true);
    }

    // The move cannot repeat history.
    for (const Board &b : this->boardHistory) {
        if (b == this->board) {
            this->board = this->boardHistory.back();
            return;
        }
    }

    this->boardHistory.push_back(this->board);
    this->lastStone = curStone;

    if (!addToRecord)
        return;
    Move move {
        .row = row,
        .col = col,
        .stone = curStone,
    };
    this->moves.push_back(move);
    this->moveIdx += 1;
}

void GameState::boardAtMove(int idx) {
    if (idx < 0 || idx > (int)moves.size())
        return;
    clearBoard();
    moveIdx = idx;
    for (size_t i = 0; i < (size_t)idx; ++i) {
        const Move &move = this->moves.at(i);
        attemptMove(move.row, move.col, false);
    }
}

bool GameState::coordWithinBoard(int row, int col) {
    return row >= 0 && row < kBoardSize && col >= 0 && col < kBoardSize;
}

vector<tuple<int,int>> GameState::getAdjacents(int row, int col) {
    std::tuple<int,int> adjacents[] = {
        {row+1, col}, {row-1, col},
        {row, col+1}, {row, col-1},
    };
    vector<tuple<int,int>> ret;
    for (auto [adj_row, adj_col] : adjacents) {
        if (coordWithinBoard(adj_row, adj_col))
            ret.push_back({adj_row, adj_col});
    }
    return ret;
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
        vector<tuple<int,int>> adjacents = getAdjacents(row, col);
        for (auto [adjRow, adjCol] : adjacents) {
            // No liberties outside the board
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

        vector<tuple<int,int>> adjacents = getAdjacents(row, col);
        for (auto [adjRow, adjCol] : adjacents) {
            if (board[adjRow][adjCol] == groupColor) {
                group.push({adjRow, adjCol});
            }
        }
    }

    return ret;
}

void GameState::clearBoard(void) {
    this->lastStone = NONE;
    for (auto &rowArray : this->board)
        rowArray.fill(Stone::NONE);
    this->moveIdx = 0;
}

void GameState::next(void) {
    if (moveIdx < this->moves.size())
        boardAtMove(moveIdx + 1);
}

void GameState::previous(void) {
    if (moveIdx > 0)
        boardAtMove(moveIdx - 1);
}

ostream &operator<<(ostream &os, const GameState &gs) {
    for (size_t j = 0; j < gs.board.size(); ++j) {
        for (size_t i = 0; i < gs.board[j].size(); ++i) {
            enum Stone stone = gs.board[j][i];
            switch (stone) {
            case Stone::NONE:
                os << ".";
                break;
            case Stone::BLACK:
                os << "#";
                break;
            case Stone::WHITE:
                os << "o";
                break;
            }
        }
        os << "\n";
    }
    return os;
}
