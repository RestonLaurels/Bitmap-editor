#include "paint.h"
#include <QApplication>
#include <QPainter>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Paint w;
    w.show();

    return a.exec();
}
