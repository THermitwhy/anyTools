#include "QCutImage.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCutImage w;
    w.show();
    return a.exec();
}
