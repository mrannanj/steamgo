#include <QtWidgets/QtWidgets>
#include <QDebug>
#include "mainwindow.h"
#include "sgf.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    GameState gs;
    if (argc > 1) {
        if (!readSGF(argv[1], gs)) {
            qInfo() << "Failed to parse" << argv[1];
            return 1;
        }
    }
    MainWindow mainWindow(gs);
    mainWindow.show();

    return app.exec();
}
