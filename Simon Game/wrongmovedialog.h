#ifndef WRONGMOVEDIALOG_H
#define WRONGMOVEDIALOG_H

#include <QMediaPlayer>
#include <QPixmap>


#include <QDialog>

namespace Ui {
class WrongMoveDialog;
}

class WrongMoveDialog : public QDialog
{
    Q_OBJECT

public:
    QMediaPlayer *doh;
    explicit WrongMoveDialog(QWidget *parent = 0);
    ~WrongMoveDialog();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

signals:
    void restart();

private:
    Ui::WrongMoveDialog *ui;
};

#endif // WRONGMOVEDIALOG_H
