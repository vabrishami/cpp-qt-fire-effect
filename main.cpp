#include "fireplace.h"
#include <QApplication>

int main(int argv, char** args)
{
    QApplication app(argv, args);
    FirePlace testFire(640, 128);
    testFire.show();

    return app.exec();
}
