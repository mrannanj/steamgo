#include <QtWidgets/QtWidgets>
#include "boardviewer.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    BoardViewer viewer;
    viewer.show();

    return app.exec();
}
