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
    QPixmap black;
    QPixmap board;
};

#endif // BOARDVIEWER_H
