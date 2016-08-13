#include "stdafx.h"
#include "simplepaint.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SimplePaint w;
    w.show();
    return a.exec();
}
