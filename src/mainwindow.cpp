#include "mainwindow.h"

MainWindow::MainWindow(GameState &gameState, QWidget *parent):
    QWidget(parent),
    mGameState(gameState)
{
    mBoardViewer = new BoardViewer(this, mGameState);
    mPreviousButton = new QPushButton("Previous", this);
    mNextButton = new QPushButton("Next", this);

    connect(mPreviousButton, &QPushButton::clicked, mBoardViewer, &BoardViewer::previous);
    connect(mNextButton, &QPushButton::clicked, mBoardViewer, &BoardViewer::next);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(mBoardViewer);
    layout->addWidget(mPreviousButton);
    layout->addWidget(mNextButton);

    setLayout(layout);
    setWindowTitle("SteamGo");
}
