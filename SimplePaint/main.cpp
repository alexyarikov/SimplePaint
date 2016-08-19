#include "stdafx.h"
#include "SimplePaint.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SimplePaint::SimplePaint w;
    w.show();
    return a.exec();
}
