#include "foxText.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    foxText w;
    w.show();
    return a.exec();
}
