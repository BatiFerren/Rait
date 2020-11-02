#include "myrait.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyRait w;
    w.show();

    return a.exec();
}
