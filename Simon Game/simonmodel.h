#ifndef SIMONMODEL_H
#define SIMONMODEL_H

#include <QObject>
#include <time.h>
#include <QDebug>
#include <QTime>
#include <QThread> //for
#include <QTimer>
#include <cstdlib>
#include <ctime>
#include <QMediaPlayer>

using namespace std;

class SimonModel : public QObject
{
    Q_OBJECT
private:
    int sleepDuration;
//    bool isBlue;
    int MoveIndex;
    bool gameHasStarted;
    bool isPlayersTurn;
    int gapTime;
    bool moveAdded;
    QList<bool> computerMoves;
    QTimer* buttonColorTimer;
    QTimer* pauseColorTimer;
    QMediaPlayer* mediaPlayer;
    QMediaPlayer* belchPlayer;
    QMediaPlayer* nedPlayer;
    QMediaPlayer* dohPlayer;

    //private function
    void initialState();

public:
    explicit SimonModel(QObject *parent = 0);
    ~SimonModel();
    void playComputer();
    void playPlayer();
    bool generateMove();
    void endGame();

signals:
    void Highlight(bool, int);
    void HighlightDone();
    void PauseDone(bool);
    void DisableStart();
    void computersTurn();
    void playersTurn();
    void updateStartTime(int);
    void playDone();
    void updateProgress(int, int);
    void skipToButtonTimerDone();
    void lightButton();
    void wrongMove();
    void restartSig();
    void updateTextSig(QString);

private slots:
    void startSlot();
    void buttonTimerDonePlayer();

public slots:
    void RedPushed();
    void BluePushed();
    void StartPushed();
    void buttonTimerDone();
    void pauseTimerDone();
    void restartSlot();
};

#endif // SIMONMODEL_H
