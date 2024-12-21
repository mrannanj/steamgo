#ifndef BOARDVIEWER_H
#define BOARDVIEWER_H

#include <QWidget>
#include <QPixmap>

class BoardViewer : public QWidget {
    Q_OBJECT

public:
    BoardViewer(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QPixmap mBoardImage;
    QPixmap mBlackImage;
    QPixmap mWhiteImage;
};

#endif // BOARDVIEWER_H
