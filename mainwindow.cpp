#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
    mBoardViewer = new BoardViewer(this, mGameState);
    mControlButton = new QPushButton("Next", this);

    connect(mControlButton, &QPushButton::clicked, mBoardViewer, &BoardViewer::placeRandomStone);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(mBoardViewer);
    layout->addWidget(mControlButton);

    setLayout(layout);
    setWindowTitle("TrollGo");
    resize(800, 600);
}
