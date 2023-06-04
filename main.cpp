#include "startwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    StartWindow w;
    w.setWindowTitle("推箱子");
    w.setFixedSize(1200,750); //16*10
    w.setGeometry(35,35,1200,750);
    w.show();
    return a.exec();
}
