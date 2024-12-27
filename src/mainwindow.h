#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include "gamestate.h"
#include "boardviewer.h"

class MainWindow : public QWidget {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private:
    BoardViewer *mBoardViewer;
    QPushButton *mControlButton;
    GameState mGameState;
};

#endif // MAINWINDOW_H
