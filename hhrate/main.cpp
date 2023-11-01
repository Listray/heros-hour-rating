#include "hhrate.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    hhrate w;
    w.show();
    return a.exec();
}
