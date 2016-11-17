#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPalette>
#include <time.h>
#include <QTimer>
#include "wrongmovedialog.h"
#include <QMediaPlayer>


using namespace std;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_RedButton_clicked();

    void on_BlueButton_clicked();

    void on_StartButton_clicked();
    void ButtonToHighlight(bool, int);
    void HighlightDone();
public slots:
    void disableStart();
    void playersTurn();
    void computersTurn();
    void updateStartTime(int);
    void updateProgress(int, int);
    void wrongMove();
    void restart();
    void restartForModel();
    void updateText(QString);
 //   void HighlightDone(bool);
signals:
    void RedButtonPushed();
    void BlueButtonPushed();
    void StartButtonPushed();
    void restart2();

private:
    Ui::MainWindow *ui;
    WrongMoveDialog dialogWindow;
    QMediaPlayer* doh;

};

#endif // MAINWINDOW_H
