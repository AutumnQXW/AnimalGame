#include "animalGame.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    animalGame w;
    w.show();
    return a.exec();
}

