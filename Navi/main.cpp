#include <QApplication>

#include "navi.h"
#include <QtSvg/QtSvg>
#include <QtSvg/QSvgRenderer>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Navi *navi = new Navi();

    navi->show();
    return app.exec();
}
