#include "simonmodel.h"

/*!
 * \brief SimonModel::SimonModel
 * \param parent
 */
SimonModel::SimonModel(QObject *parent) : QObject(parent)
{
    initialState();

}


SimonModel::~SimonModel(){
    delete(nedPlayer);
    delete(belchPlayer);
    delete(mediaPlayer);
    delete(buttonColorTimer);
    delete(pauseColorTimer);
}

void SimonModel::RedPushed(){
    nedPlayer->play();
    if(computerMoves.at(MoveIndex) != 0){
        endGame();
        return;
    }
    else{
        if(MoveIndex == computerMoves.length() - 1){
            emit skipToButtonTimerDone();
        }
        else{
            emit lightButton();
        }
        return;
    }
}

void SimonModel::BluePushed(){
    belchPlayer->play();
    if(computerMoves.at(MoveIndex) != 1){
        endGame();
        return;
    }
    else{
        if(MoveIndex == computerMoves.length() - 1){
            emit skipToButtonTimerDone();
        }
        else{
            emit lightButton();
        }
        return;
    }
}

void SimonModel::StartPushed(){
    if(!gameHasStarted){
        computerMoves.clear();
        MoveIndex = -1;
        computerMoves.append(generateMove());
        gameHasStarted = true;
        pauseColorTimer->start(1000);
        mediaPlayer->play();
        //the emits were originally before pausecolortimer
        emit DisableStart();
        emit HighlightDone();
    }
    else{
        restartSlot();
    }
}

void SimonModel::playComputer(){
    qDebug()<<"---------COMPUTER TURN---------";

    if(gameHasStarted == 0){
        emit updateStartTime(4);
    }
    bool thisMove = computerMoves.at(MoveIndex);
    buttonColorTimer->start(sleepDuration);
    //this emit was above the button color timer first
    emit Highlight(thisMove,sleepDuration);
    if((MoveIndex == computerMoves.length() - 1) && (!moveAdded) &&(gameHasStarted)){
        computerMoves.append(generateMove());
        moveAdded = true;
    }
    return;
}

void SimonModel::playPlayer(){
    qDebug()<<"---------PLAYER TURN---------";
    bool thisMove = computerMoves.at(MoveIndex);
    emit playersTurn();
    return;
}

bool SimonModel::generateMove(){
    srand(time(NULL));
    int randomNumber = rand()%2;
    qDebug()<<randomNumber;
    return (randomNumber == 0);

}

void SimonModel::buttonTimerDone(){
    emit HighlightDone();
    pauseColorTimer->start(gapTime);
}

void SimonModel::buttonTimerDonePlayer(){
    emit playersTurn();
    pauseColorTimer->start(gapTime);
}

void SimonModel::pauseTimerDone(){
    MoveIndex++;
    if(isPlayersTurn){
        emit updateTextSig("Human");
    }
    else{
        emit updateTextSig("Computer");
    }
    if(moveAdded && !isPlayersTurn){
        emit updateProgress(MoveIndex, computerMoves.length() - 1);
    }
    else if(!moveAdded && !isPlayersTurn){
        emit updateProgress(MoveIndex, computerMoves.length());
    }
    else{
        emit updateProgress(MoveIndex, computerMoves.length());
    }
    if(MoveIndex >= computerMoves.length() && isPlayersTurn){
        MoveIndex = 0;
        isPlayersTurn = 0;
        emit computersTurn();
        moveAdded = false;
        gapTime -= 50;
        sleepDuration -= 75;
        playComputer();
    }
    else if (MoveIndex >= computerMoves.length() && !isPlayersTurn){
        MoveIndex = 0;

        isPlayersTurn = 1;
        emit playersTurn();
        playPlayer();
    }
    else if(MoveIndex < computerMoves.length() && isPlayersTurn){
        playPlayer();
    }
    else{
        playComputer();
        gameHasStarted = true;
    }
}

void SimonModel::startSlot(){

    playComputer();
}

void SimonModel::endGame(){
    nedPlayer->stop();
    belchPlayer->stop();
    mediaPlayer->stop();
    emit wrongMove();
   // dohPlayer->play();
    //exit(1);
    return;
}

void SimonModel::initialState(){
    MoveIndex = 0;
    moveAdded = 0;
    gameHasStarted = false;
    sleepDuration = 1000; //amount of time in miliseconds that the buttons are highlighted for.
    gapTime = 500; // amount of time to gap between button highlights.
    isPlayersTurn = false;
    buttonColorTimer = new QTimer(this);
    pauseColorTimer = new QTimer(this);
    buttonColorTimer->setSingleShot(true);
    pauseColorTimer->setSingleShot(true);
    QObject::connect(buttonColorTimer, SIGNAL(timeout()), this, SLOT(buttonTimerDone()));
    QObject::connect(pauseColorTimer, SIGNAL(timeout()), this, SLOT(pauseTimerDone()));
    QObject::connect(this, SIGNAL(playDone()), this, SLOT(pauseTimerDone()));
    QObject::connect(this, SIGNAL(skipToButtonTimerDone()), this, SLOT(buttonTimerDone()));
    QObject::connect(this, SIGNAL(lightButton()), this, SLOT(buttonTimerDonePlayer()));
    emit updateProgress(0, 1);
    emit updateTextSig("Computer");
    mediaPlayer = new QMediaPlayer();
    mediaPlayer->setMedia(QUrl("qrc:/SoundsAndImages/hawaiifiveo.m4a"));
    mediaPlayer->setVolume(100);
    belchPlayer = new QMediaPlayer();
    belchPlayer->setMedia(QUrl("qrc:/SoundsAndImages/belching.mp3"));
    belchPlayer->setVolume(100);
    nedPlayer = new QMediaPlayer();
    nedPlayer->setMedia(QUrl("qrc:/SoundsAndImages/okly.mp3"));
   // dohPlayer = new QMediaPlayer();
   // dohPlayer->setMedia(QUrl::fromLocalFile("/Users/alecadair/Documents/CS3505/assign5/Simon/dohdoh.mp3"));
}

void SimonModel::restartSlot(){
    sleepDuration = 1000;
    gapTime = 500;
    MoveIndex = 0;
    gameHasStarted = false;
    isPlayersTurn = false;
    emit updateProgress(0,1);
    computerMoves.clear();
    computerMoves.append(generateMove());
    emit restartSig();
    emit updateTextSig("Computer");
    mediaPlayer->stop();
}
