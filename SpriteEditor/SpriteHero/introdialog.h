#ifndef INTRODIALOG_H
#define INTRODIALOG_H

#include <QDialog>

namespace Ui {
class IntroDialog;
}

class IntroDialog : public QDialog
{
    Q_OBJECT

public:
    explicit IntroDialog(QWidget *parent = 0);
    ~IntroDialog();
    int getSizeChosen();

private slots:
    void on_comboBox_activated(int index);
    void on_pushButton_clicked();

private:
    Ui::IntroDialog *ui;
    int sizeChosen;

signals:
    void goSig(int size);
};

#endif // INTRODIALOG_H
