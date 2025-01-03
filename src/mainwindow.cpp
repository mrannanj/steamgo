#include "mainwindow.h"

MainWindow::MainWindow(AppState &appState, QWidget *parent):
    QWidget(parent),
    mAppState(appState),
    mBoardViewer(nullptr),
    mPreviousButton(nullptr),
    mNextButton(nullptr),
    mSaveButton(nullptr)
{
    mBoardViewer = new BoardViewer(this, mAppState);
    mPreviousButton = new QPushButton("Previous", this);
    mNextButton = new QPushButton("Next", this);

    connect(mPreviousButton, &QPushButton::clicked, mBoardViewer, &BoardViewer::previous);
    connect(mNextButton, &QPushButton::clicked, mBoardViewer, &BoardViewer::next);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(mBoardViewer);
    layout->addWidget(mPreviousButton);
    layout->addWidget(mNextButton);

    if (appState.writeSGF) {
        mSaveButton = new QPushButton("Save", this);
        connect(mSaveButton, &QPushButton::clicked, mBoardViewer, &BoardViewer::save);
        layout->addWidget(mSaveButton);
    }

    setLayout(layout);
    setWindowTitle("SteamGo");
}
