#include "boardviewer.h"
#include <QPainter>
#include <QPaintEvent>

BoardViewer::BoardViewer(QWidget *parent)
    : QWidget(parent), black(":/images/black.png"), board(":/images/board.png") {
    setWindowTitle("Go Board");
    resize(608, 608);
}

void BoardViewer::paintEvent(QPaintEvent *event) {
    QPainter painter(this);

    if (board.isNull()) {
        painter.drawText(rect(), Qt::AlignCenter, "Failed to load the board image.");
        return;
    } else if (black.isNull()) {
        painter.drawText(rect(), Qt::AlignCenter, "Failed to load the black stone image.");
        return;
    }

    int rows = 19;
    int cols = 19;
    QSize bgSize = board.size().scaled(size(), Qt::KeepAspectRatio);

    int bgX = (width() - bgSize.width()) / 2; // Center the background
    int bgY = (height() - bgSize.height()) / 2;

    // Draw background
    painter.drawPixmap(bgX, bgY, bgSize.width(), bgSize.height(), board);

    // Use bgSize dimensions to define grid area
    int gridWidth = bgSize.width();
    int gridHeight = bgSize.height();

    // Adjust grid cells to fit within bgSize
    int cellWidth = gridWidth / cols;
    int cellHeight = gridHeight / rows;

    // Calculate the top-left corner for the grid
    int gridX = bgX;
    int gridY = bgY;
    QPixmap scaledImage = black.scaled(cellWidth, cellHeight, Qt::KeepAspectRatio);

    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            int x = gridX + col * cellWidth + (cellWidth - scaledImage.width()) / 2;
            int y = gridY + row * cellHeight + (cellHeight - scaledImage.height()) / 2;

            painter.drawPixmap(x, y, scaledImage);
        }
    }
}
