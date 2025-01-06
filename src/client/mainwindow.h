#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include "client/appstate.h"
#include "client/boardviewer.h"

class MainWindow : public QWidget {
    Q_OBJECT

public:
    MainWindow(AppState &appState, QWidget *parent = nullptr);

private:
    AppState& mAppState;
    BoardViewer *mBoardViewer;
    QPushButton *mNextButton;
    QPushButton *mPreviousButton;
    QPushButton *mSaveButton;
};

#endif // MAINWINDOW_H
