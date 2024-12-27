#include <ctime>
#include <cstdlib>
#include <QtWidgets/QtWidgets>
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    std::srand(std::time(0));
    QApplication app(argc, argv);

    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}
