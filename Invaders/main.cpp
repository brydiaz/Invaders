#include "juegoprincipal.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    JuegoPrincipal w;
    w.show();
    return a.exec();
}
