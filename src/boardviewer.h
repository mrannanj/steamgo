#ifndef BOARDVIEWER_H
#define BOARDVIEWER_H

#include <QWidget>
#include <QPixmap>
#include "gamestate.h"

class BoardViewer : public QWidget {
    Q_OBJECT

public:
    BoardViewer(QWidget *parent, GameState& gameState);

public slots:
    void placeRandomStone();

protected:
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    int mMouseOverRow;
    int mMouseOverCol;
    QPixmap mBoardImage;
    QPixmap mBlackImage;
    QPixmap mWhiteImage;
    GameState& mGameState;
};

#endif // BOARDVIEWER_H
