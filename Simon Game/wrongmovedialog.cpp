#include "wrongmovedialog.h"
#include "ui_wrongmovedialog.h"

WrongMoveDialog::WrongMoveDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WrongMoveDialog)
{
    //doh = new QMediaPlayer();
   // QPixmap ralph("/Users/alecadair/Documents/CS3505/assign5/Simon/ralphsad.jpg");
    //ui->label->setPixmap(ralph);
    //ui->label->show();
 //   doh->setMedia(QUrl::fromLocalFile("/Users/alecadair/Documents/CS3505/assign5/Simon/dohdoh.mp3"));
    //doh->play();
    ui->setupUi(this);
}

WrongMoveDialog::~WrongMoveDialog()
{
   // delete(doh);
    delete ui;
}

void WrongMoveDialog::on_pushButton_clicked()
{
    emit restart();
    close();
}

void WrongMoveDialog::on_pushButton_2_clicked()
{
    exit(1);
}
