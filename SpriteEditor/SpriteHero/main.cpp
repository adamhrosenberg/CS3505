#include "mainwindow.h"
#include "introdialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    MainWindow w;
    w.show();
    IntroDialog* p = w.getPointerToIntro();
    p->show();


    return a.exec();
}
