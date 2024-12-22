#ifndef BOARDVIEWER_H
#define BOARDVIEWER_H

#include <QWidget>
#include <QPixmap>
#include "gamestate.h"

class BoardViewer : public QWidget {
    Q_OBJECT

public:
    BoardViewer(QWidget *parent, GameState& gameState);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QPixmap mBoardImage;
    QPixmap mBlackImage;
    QPixmap mWhiteImage;
    GameState& mGameState;
};

#endif // BOARDVIEWER_H
