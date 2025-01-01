#ifndef BOARDVIEWER_H
#define BOARDVIEWER_H

#include <QWidget>
#include <QPixmap>
#include "gamestate.h"

class BoardViewer : public QWidget {
    Q_OBJECT

public:
    BoardViewer(QWidget *parent, GameState &gameState);

public slots:
    void next(void);
    void previous(void);

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
    GameState &mGameState;
};

#endif // BOARDVIEWER_H
