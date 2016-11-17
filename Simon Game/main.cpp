#include "mainwindow.h"
#include <QApplication>
#include <QPushButton>
//#include "Simon.h"
#include "simonmodel.h"
//#include "gameengine.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    SimonModel simon;
    //GameEngine engine(w,simon);

    w.show();

    QObject::connect(&w, SIGNAL(RedButtonPushed()), &simon, SLOT(RedPushed()));
    QObject::connect(&w, SIGNAL(BlueButtonPushed()), &simon, SLOT(BluePushed()));
    QObject::connect(&w, SIGNAL(StartButtonPushed()), &simon, SLOT(StartPushed()));
    QObject::connect(&simon, SIGNAL(Highlight(bool, int)), &w, SLOT(ButtonToHighlight(bool, int)));
    QObject::connect(&simon, SIGNAL(DisableStart()), &w, SLOT(disableStart()));
    QObject::connect(&simon, SIGNAL(playersTurn()), &w, SLOT(playersTurn()));
    QObject::connect(&simon, SIGNAL(computersTurn()), &w, SLOT(computersTurn()));
    QObject::connect(&simon, SIGNAL(HighlightDone()), &w, SLOT(HighlightDone()));
    QObject::connect(&simon,SIGNAL(updateStartTime(int)), &w, SLOT(updateStartTime(int)));
    QObject::connect(&simon, SIGNAL(updateProgress(int, int)), &w, SLOT(updateProgress(int, int)));
    QObject::connect(&simon, SIGNAL(wrongMove()), &w, SLOT(wrongMove()));
    QObject::connect(&w, SIGNAL(restart2()), &simon, SLOT(restartSlot()));
    QObject::connect(&simon, SIGNAL(restartSig()), &w, SLOT(restartForModel()));
    QObject::connect(&simon, SIGNAL(updateTextSig(QString)), &w, SLOT(updateText(QString)));
    return a.exec();
}
