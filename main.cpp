#include <QtWidgets/QtWidgets>
#include "boardviewer.h"
#include "gamestate.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    GameState gameState;
    BoardViewer viewer(nullptr, gameState);
    viewer.show();

    return app.exec();
}
