#include "jaqubsuite.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    jaqubsuite w;
    w.show();

    return app.exec();
}

