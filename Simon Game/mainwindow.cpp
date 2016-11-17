#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //QPalette pal;
    //pal.setColor(QPalette::Button, QColor(Qt::darkBlue));
    ui->BlueButton->setAutoFillBackground(true);
    //ui->BlueButton->setPalette(pal);
    ui->BlueButton->setEnabled(false);
    ui->BlueButton->update();
    //pal.setColor(QPalette::Button, QColor(Qt::darkRed));
    ui->RedButton->setAutoFillBackground(true);
    //ui->RedButton->setPalette(pal);
    ui->RedButton->setEnabled(false);
    ui->RedButton->update();
    ui->ProgressBar->setRange(0,1);
    ui->ProgressBar->setValue(0);
    QPixmap pixmap(":/SoundsAndImages/ned.png");
    QIcon icon(pixmap);
    ui->RedButton->setIcon(icon);
    QSize iconSize(80, 80);
    ui->RedButton->setIconSize(iconSize);
    QPixmap pixmap2(":/SoundsAndImages/barney.png");
    QIcon icon2(pixmap2);
    ui->BlueButton->setIcon(icon2);
    QSize iconSize2(80,80);
    ui->BlueButton->setIconSize(iconSize2);
    dialogWindow.setModal(true);
    QObject::connect(&dialogWindow, SIGNAL(restart()), this, SLOT(restart()));
    ui->ProgressBar->setRange(0, 1);
    ui->ProgressBar->setValue(0);
}

MainWindow::~MainWindow()
{
    if(doh != NULL){
        delete doh;
    }
    delete ui;
}

void MainWindow::on_RedButton_clicked()
{
    emit RedButtonPushed();
    return;
}

void MainWindow::on_BlueButton_clicked()
{
    emit BlueButtonPushed();
    return;
}

void MainWindow::on_StartButton_clicked()
{
    emit StartButtonPushed();
    return;
}

void MainWindow::playersTurn(){
   // ui->TurnLabel->setText("Player");
    QPalette pal;
    if(!ui->BlueButton->isEnabled())
        ui->BlueButton->setEnabled(true);
        pal.setColor(QPalette::Button, QColor(Qt::blue));
        ui->BlueButton->setAutoFillBackground(true);
        ui->BlueButton->setPalette(pal);
        ui->BlueButton->update();
    if(!ui->RedButton->isEnabled())
        ui->RedButton->setEnabled(true);
        pal.setColor(QPalette::Button, QColor(Qt::red));
        ui->RedButton->setAutoFillBackground(true);
        ui->RedButton->setPalette(pal);
        ui->RedButton->update();
    return;
}

void MainWindow::computersTurn(){
   // ui->TurnLabel->setText("Computer");
    if(ui->BlueButton->isEnabled())
        ui->BlueButton->setEnabled(false);
    if(ui->RedButton->isEnabled())
        ui->RedButton->setEnabled(false);
    return;
}

void MainWindow::HighlightDone(){
    //QPushButton* butptr;
    QPalette pal;
//    pal.setColor(QPalette::Button, QColor(Qt::yellow));
    ui->BlueButton->setAutoFillBackground(true);
    ui->BlueButton->setPalette(pal);
    ui->BlueButton->update();
//    pal.setColor(QPalette::Button, QColor(Qt::yellow));
    ui->RedButton->setPalette(pal);
    ui->RedButton->update();

   /* if(isBlue){
        QPalette pal;
        pal.setColor(QPalette::Button, QColor(Qt::darkBlue));
        ui->BlueButton->setAutoFillBackground(true);
        ui->BlueButton->setPalette(pal);
        ui->BlueButton->update();
    }
    else{
        QPalette pal;
        pal.setColor(QPalette::Button, QColor(Qt::darkRed));
        ui->RedButton->setPalette(pal);
        ui->RedButton->update();
    }*/
    return;
}

void MainWindow::ButtonToHighlight(bool isBlue, int HighlightTime){
    ui->BlueButton->setEnabled(false);
    ui->RedButton->setEnabled(false);
    if(isBlue){
        //high light blue
       // qDebug()<<"Computer has clicked blue";
        //ui->BlueButton->set
        QPalette pal;
        pal.setColor(QPalette::Button, QColor(Qt::blue));
        ui->BlueButton->setAutoFillBackground(true);
        ui->BlueButton->setPalette(pal);
        ui->BlueButton->update();
    }
    else{
        //high light redHighlightTime
        //qDebug()<<"Computer has clicked red";
        QPalette pal;
        pal.setColor(QPalette::Button, QColor(Qt::red));
        ui->RedButton->setAutoFillBackground(true);
        ui->RedButton->setPalette(pal);
        ui->RedButton->update();
    }
    return;
}

void MainWindow::disableStart(){
   // ui->StartButton->setEnabled(false);
    ui->StartButton->setText("Restart");
    return;
}

void MainWindow::updateStartTime(int time){
    if(time != 4)
        ui->StartButton->setText(QString::number(time));
    else
        ui->StartButton->setText("Written By: Alec and Adam");
    return;
}

void MainWindow::updateProgress(int low, int high){
    ui->ProgressBar->setRange(0, high);
    ui->ProgressBar->setValue(low);
}

void MainWindow::wrongMove(){
    ui->BlueButton->setEnabled(false);
    ui->RedButton->setEnabled(false);
    doh = new QMediaPlayer();
    doh->setMedia(QUrl("qrc:/SoundsAndImages/dohdoh.mp3"));
    doh->play();
    dialogWindow.exec();
}

void MainWindow::restart(){
    //doh->stop();
    emit restart2();
}

void MainWindow::restartForModel(){
    ui->BlueButton->setEnabled(false);
    ui->RedButton->setEnabled(false);
    ui->StartButton->setText("Start Game");
    ui->StartButton->setEnabled(true);
    ui->ProgressBar->setRange(0, 1);
    ui->ProgressBar->setValue(0);
}

void MainWindow::updateText(QString s){
    ui->TurnLabel->setText(s);
}
