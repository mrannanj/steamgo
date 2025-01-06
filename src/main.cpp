#include <string>
#include <vector>
#include <QtWidgets/QtWidgets>
#include <QDebug>
#include <cstring>
#include <string>
#include "appstate.h"
#include "mainwindow.h"
#include "common/sgf.h"

using std::string, std::vector;

int main(int argc, char *argv[]) {
    vector<string> args(argv, argv + argc);
    QApplication app(argc, argv);

    AppState appState;
    if (args.size() == 3) {
        if (args[1] == "-r") {
            if (!readSGF(args[2], appState.gameState)) {
                qCritical() << "Failed to parse" << args[2].c_str();
                return 1;
            }
        } else if (args[1] == "-w") {
            appState.writeSGF = true;
            appState.sgfFile = args[2];
        } else {
            qCritical() << "Unknown option" << args[1].c_str();
            return 1;
        }
    }
    MainWindow mainWindow(appState);
    mainWindow.show();

    return app.exec();
}
