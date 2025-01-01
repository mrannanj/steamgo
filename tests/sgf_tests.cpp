#include <gtest/gtest.h>
#include <sstream>
#include "gamestate.h"
#include "sgf.h"

using namespace std;

TEST(TestSGF, SimpleSGF) {
    GameState gs;
    ASSERT_TRUE(readSGF(PROJECT_SOURCE_DIR "/sgf/simple.sgf", gs));
    stringstream ss;
    ss << gs;
    string expected =
        "...................\n"
        "...................\n"
        "...................\n"
        "...o...........#...\n"
        "...................\n"
        "...................\n"
        "...................\n"
        "...................\n"
        "...................\n"
        ".........#.........\n"
        "...................\n"
        "...................\n"
        "...................\n"
        "...................\n"
        "...................\n"
        "...o...........#...\n"
        "...................\n"
        "...................\n"
        "...................\n";
    ASSERT_EQ(ss.str(), expected);
}