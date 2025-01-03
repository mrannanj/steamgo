#include "sgf.h"
#include <fstream>
#include <sstream>

using namespace std;

bool readSGF(const string &filename, GameState &gs) {
    ifstream f(filename);
    if (!f.good()) {
        f.close();
        return false;
    }
    stringstream s;
    s << f.rdbuf();
    f.close();
    string text(s.str());

    size_t idx1 = 0, idx2 = 0;
    size_t row, col;
    bool black = true;
    while (true) {
        idx1 = text.find(black ? ";B[" : ";W[", idx2);
        if (idx1 == string::npos)
            break;
        idx2 = text.find("]", idx1);
        if (idx2 == string::npos)
            return false;
        if (idx2 - idx1 == 3) {
            // Pass
            row = -1;
            col = -1;
        } else if (idx2 - idx1 == 5) {
            row = text[idx1 + 3 + 1] - 'a';
            col = text[idx1 + 3 + 0] - 'a';
        } else {
            // Invalid
            return false;
        }
        gs.attemptMove(row, col, true);
        black = !black;
    }
    return true;
}

bool writeSGF(const std::string &filename, const GameState &gs) {
    ofstream f(filename);
    if (!f.good()) {
        f.close();
        return false;
    }
    stringstream ss;
    ss <<
        "(;FF[4]\n"
        "CA[UTF-8]\n"
        "GM[1]\n"
        "GN[demo]\n"
        "PC[Online]\n"
        "PB[Black]\n"
        "PW[White]\n"
        "BR[10k]\n"
        "WR[10k]\n"
        "OT[Error: time control missing]\n"
        "RE[?]\n"
        "SZ[19]\n"
        "KM[6.5]\n"
        "RU[Japanese]\n\n";
    for (const Move &move : gs.moves) {
        ss << (move.stone == Stone::BLACK ? ";B[" : ";W[");
        if (move.row >= 0 && move.col >= 0)
            ss << (char)(move.col + 'a') << (char)(move.row + 'a');
        ss << "]\n";
    }
    ss << ")\n";
    f << ss.rdbuf();
    f.close();

    return true;
}
