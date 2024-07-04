#include "qapplication.h"
#include "window.h"


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MaClasse window;
    window.show();
    return app.exec();
}
