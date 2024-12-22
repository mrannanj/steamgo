#include "boardviewer.h"
#include "gamestate.h"
#include <cstdlib>
#include <QPainter>
#include <QPaintEvent>

BoardViewer::BoardViewer(QWidget *parent, GameState& gameState):
    QWidget(parent),
    mBoardImage(":/images/board.png"),
    mBlackImage(":/images/black.png"),
    mWhiteImage(":/images/white.png"),
    mGameState(gameState)
{
}

void BoardViewer::placeRandomStone() {
    unsigned row = rand() % (kBoardSize + 1);
    unsigned col = rand() % (kBoardSize + 1);
    unsigned stone = 1 + (rand() % 2);
    mGameState.board[row][col] = static_cast<Stone>(stone);
    update();
}

void BoardViewer::paintEvent(QPaintEvent *event) {
    QPainter painter(this);

    if (mBoardImage.isNull()) {
        painter.drawText(rect(), Qt::AlignCenter, "Failed to load the board image.");
        return;
    } else if (mBlackImage.isNull()) {
        painter.drawText(rect(), Qt::AlignCenter, "Failed to load the black stone image.");
        return;
    } else if (mWhiteImage.isNull()) {
        painter.drawText(rect(), Qt::AlignCenter, "Failed to load the white stone image.");
        return;
    }

    QSize boardSize = mBoardImage.size().scaled(size(), Qt::KeepAspectRatio);

    int bgX = (this->width() - boardSize.width()) / 2;
    int bgY = (this->height() - boardSize.height()) / 2;

    painter.drawPixmap(bgX, bgY, boardSize.width(), boardSize.height(), mBoardImage);

    int cellWidth = boardSize.width() / kBoardSize;
    int cellHeight = boardSize.height() / kBoardSize;

    QPixmap scaledBlack = mBlackImage.scaled(cellWidth, cellHeight, Qt::KeepAspectRatio);
    QPixmap scaledWhite = mWhiteImage.scaled(cellWidth, cellHeight, Qt::KeepAspectRatio);

    for (unsigned row = 0; row < kBoardSize; ++row) {
        for (unsigned col = 0; col < kBoardSize; ++col) {
            int x = bgX + col * cellWidth + (cellWidth - scaledBlack.width()) / 2;
            int y = bgY + row * cellHeight + (cellHeight - scaledBlack.height()) / 2;

            switch (mGameState.board[row][col]) {
            case Stone::BLACK:
                painter.drawPixmap(x, y, scaledBlack);
                break;
            case Stone::WHITE:
                painter.drawPixmap(x, y, scaledWhite);
                break;
            case Stone::NONE:
                break;
            }
        }
    }
}
