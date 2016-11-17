#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "spriteview.h"
#include <QScrollArea>
#include <QTableView>
#include <QStandardItemModel>
#include <QTimer>
#include <QFileDialog>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QPixmap>
#include "introdialog.h"
#include "math.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void updateFilmStrip(QImage);
    void updateFilmStripAtIndex(QImage, int);
    IntroDialog* getPointerToIntro();
    Model model;

private:
    Ui::MainWindow *ui;
    QColor currentPrimColor;
    int currentAlpha;
    QScrollArea* scrollArea;
    QTableWidgetItem *thumbnail;
    QStandardItemModel* tableModel;
    int currentFramePanelIndex;
    int currentFrameEditorIndex;
    int currentGalleryIndex;
    QTimer* animationTimer;
    int timerInterval; //miliseconds
    IntroDialog* introDialog;

public slots:
    void primaryColorChanged(QColor);
    void changePixelModel(int, int, QColor);
    void go(int);
    void changeAlpha(int);
    void rightClickOnSpriteView(int x, int y);
    //void drawPaintBucket(int, int,QColor);

signals:
    void changeSpriteViewPrimaryColor(QColor);

private slots:
    void on_addFrameButton_clicked();
    void updateAnimation();
    void on_tableWidget_clicked(const QModelIndex &index);
  //  void on_tableWidget_doubleClicked(const QModelIndex &index);
    void on_duplicateFrameButton_clicked();
    void on_fpsSlider_valueChanged(int value);
    void on_clearFrameButton_clicked();
    void on_deleteFrameButton_clicked();
    void on_saveButton_clicked();
    void on_openButton_clicked();
    void on_gifButton_clicked();
};

#endif // MAINWINDOW_H
