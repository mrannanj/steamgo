#include <string>
#include <vector>
#include <QtWidgets/QtWidgets>
#include <QDebug>
#include "mainwindow.h"
#include "sgf.h"

using std::string, std::vector;

int main(int argc, char *argv[]) {
    vector<string> args(argv, argv + argc);
    QApplication app(argc, argv);

    GameState gs;
    if (args.size() == 2) {
        if (!readSGF(args[1], gs)) {
            qCritical() << "Failed to parse" << args[1].c_str();
            return 1;
        }
    }
    MainWindow mainWindow(gs);
    mainWindow.show();

    return app.exec();
}
