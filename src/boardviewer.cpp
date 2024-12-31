#include "boardviewer.h"
#include "gamestate.h"
#include <tuple>
#include <QDebug>
#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QResizeEvent>

BoardViewer::BoardViewer(QWidget *parent, GameState& gameState):
    QWidget(parent),
    mMouseRow(-1),
    mMouseCol(-1),
    mBoardImage(":/images/board.png"),
    mBlackImage(":/images/black.png"),
    mWhiteImage(":/images/white.png"),
    mGameState(gameState)
{
    setMouseTracking(true);
    setMinimumSize(608, 608);
}

void BoardViewer::next() {
}

void BoardViewer::mouseMoveEvent(QMouseEvent *event) {
    QPoint mousePos = event->pos();

    int cellWidth = width() / kBoardSize;
    int cellHeight = height() / kBoardSize;
    int col = mousePos.x() / cellWidth;
    int row = mousePos.y() / cellHeight;

    if (col >= 0 && col < kBoardSize && row >= 0 && row < kBoardSize) {
        mMouseRow = row;
        mMouseCol = col;
    } else {
        mMouseRow = -1;
        mMouseCol = -1;
    }
    update();
}

void BoardViewer::mouseReleaseEvent(QMouseEvent *event) {
    if (mMouseRow < 0)
        return;

    // Only empty spots can be played in.
    if (mGameState.board[mMouseRow][mMouseCol] != Stone:: NONE)
        return;

    enum Stone curStone = Stone::BLACK;
    if (mGameState.lastStone == Stone::BLACK)
        curStone = Stone::WHITE;
    mGameState.board[mMouseRow][mMouseCol] = curStone;

    // Check if this stone would capture something.
    std::tuple<int,int> adjacents[] = {
        {mMouseRow+1, mMouseCol}, {mMouseRow-1, mMouseCol},
        {mMouseRow, mMouseCol+1}, {mMouseRow, mMouseCol-1},
    };
    bool willCapture = false;
    for (auto [adj_row, adj_col] : adjacents) {
        willCapture |= mGameState.captureMaybe(adj_row, adj_col, false) < 0;
    }

    // No capture, so check that we have at least one liberty.
    if (!willCapture && mGameState.captureMaybe(mMouseRow, mMouseCol, false) < 0) {
        mGameState.board[mMouseRow][mMouseCol] = Stone:: NONE;
        return;
    }

    // Capture adjacent 0 liberty groups.
    for (auto [adj_row, adj_col] : adjacents) {
        mGameState.captureMaybe(adj_row, adj_col, true);
    }
    mGameState.lastStone = curStone;

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

    QPixmap curStone = (mGameState.lastStone == Stone::BLACK) ? scaledWhite : scaledBlack;
    if (mMouseRow >= 0 && mMouseCol >= 0) {
        int x = bgX + mMouseCol * cellWidth + (cellWidth - scaledBlack.width()) / 2;
        int y = bgY + mMouseRow * cellHeight + (cellHeight - scaledBlack.height()) / 2;
        painter.setOpacity(0.5);
        painter.drawPixmap(x, y, curStone);
    }
}

void BoardViewer::resizeEvent(QResizeEvent *event) {
    QSize newSize = event->size();
    int adjustedWidth = newSize.width();
    int adjustedHeight = newSize.height();

    const float aspectRatio = 1.0f;
    if (float(adjustedWidth) / adjustedHeight > aspectRatio) {
        // Too wide: adjust width to match the height
        adjustedWidth = int(adjustedHeight * aspectRatio);
    } else {
        // Too tall: adjust height to match the width
        adjustedHeight = int(adjustedWidth / aspectRatio);
    }

    resize(adjustedWidth, adjustedHeight);
    QWidget::resizeEvent(event);
}
