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

TEST(TestSGF, CaptureOne) {
    GameState gs;
    ASSERT_TRUE(readSGF(PROJECT_SOURCE_DIR "/sgf/capture_one.sgf", gs));
    stringstream ss;
    ss << gs;
    string expected =
        "...................\n"
        "...................\n"
        "...................\n"
        "...................\n"
        "...................\n"
        "...................\n"
        "...................\n"
        "...................\n"
        "........#..........\n"
        ".......#.#..o......\n"
        "........#...o......\n"
        "...................\n"
        "...................\n"
        "...................\n"
        "...................\n"
        "...................\n"
        "...................\n"
        "...................\n"
        "...................\n";
    ASSERT_EQ(ss.str(), expected);
}

TEST(TestSGF, SelfCapture) {
    GameState gs;
    ASSERT_TRUE(readSGF(PROJECT_SOURCE_DIR "/sgf/self_capture.sgf", gs));
    stringstream ss;
    ss << gs;
    string expected =
        "...................\n"
        "...................\n"
        "...................\n"
        "...................\n"
        "...................\n"
        "...................\n"
        "...................\n"
        "...................\n"
        "...................\n"
        "...................\n"
        "...................\n"
        "...................\n"
        "oo.#...............\n"
        "#o.#...............\n"
        ".o.#...............\n"
        "#o.#...............\n"
        "oo.#...............\n"
        "...................\n"
        "...................\n";
    ASSERT_EQ(ss.str(), expected);
}

TEST(TestSGF, Ko) {
    GameState gs;
    ASSERT_TRUE(readSGF(PROJECT_SOURCE_DIR "/sgf/ko.sgf", gs));
    stringstream ss;
    ss << gs;
    string expected =
        "...................\n"
        "...................\n"
        "....#o.............\n"
        "...#.#o............\n"
        "....#o.............\n"
        "...................\n"
        "...................\n"
        "...................\n"
        "....#..............\n"
        "...................\n"
        "...................\n"
        "...................\n"
        "...................\n"
        "...................\n"
        "...................\n"
        "...................\n"
        "...................\n"
        "...................\n"
        "...................\n";
    ASSERT_EQ(ss.str(), expected);
}
