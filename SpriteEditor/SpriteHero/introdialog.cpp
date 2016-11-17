#include "introdialog.h"
#include "ui_introdialog.h"
#include "math.h"

IntroDialog::IntroDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IntroDialog)
{
    ui->setupUi(this);
    sizeChosen = 4;
    for(int i = 2; i < 10; i++){
        int dim = pow(2,i);
        QString item;
        QString sDim = QString::number(dim);
        item = sDim + " x " + sDim;
        ui->comboBox->addItem(item);
    }
}

IntroDialog::~IntroDialog()
{
    delete ui;
}

void IntroDialog::on_comboBox_activated(int index)
{
    sizeChosen = (pow(2,(index+2)));
}

int IntroDialog::getSizeChosen(){
    return sizeChosen;
}


void IntroDialog::on_pushButton_clicked()
{
    emit goSig(sizeChosen);
}
