#include "mainwindow.h"
#include "gamewindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameWindow w;
    w.show();

    return a.exec();
}
