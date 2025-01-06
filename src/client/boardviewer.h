#ifndef BOARDVIEWER_H
#define BOARDVIEWER_H

#include <QWidget>
#include <QPixmap>
#include "client/appstate.h"
#include "common/gamestate.h"

class BoardViewer : public QWidget {
    Q_OBJECT

public:
    BoardViewer(QWidget *parent, AppState &appState);

public slots:
    void next(void);
    void previous(void);
    void save(void);

protected:
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    int mMouseRow;
    int mMouseCol;
    QPixmap mBoardImage;
    QPixmap mBlackImage;
    QPixmap mWhiteImage;
    AppState &mAppState;
    GameState &mGameState;
};

#endif // BOARDVIEWER_H
