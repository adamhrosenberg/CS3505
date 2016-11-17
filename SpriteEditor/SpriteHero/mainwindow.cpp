#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    currentAlpha = 255;
    ui->widget_2->model = &(this->model);
    ui->tableWidget->setSortingEnabled(false);
    ui->tableWidget->setRowCount(1);
    ui->tableWidget->setColumnCount(0);
    ui->tableWidget->horizontalHeader()->setDefaultSectionSize(128);
    ui->tableWidget->verticalHeader()->setDefaultSectionSize(128);
    introDialog = new IntroDialog();
    connect(introDialog, SIGNAL(goSig(int)), this, SLOT(go(int)));
    connect(ui->widget_2, SIGNAL(rValueChanged(QColor)),this, SLOT(primaryColorChanged(QColor)));
    connect(ui->widget, SIGNAL(updateModelPixelSig(int, int, QColor)),this, SLOT(changePixelModel(int, int, QColor)));
    connect(ui->widget_2, SIGNAL(alphaChangedSig(int)), this, SLOT(changeAlpha(int)));
    connect(ui->widget, SIGNAL(rightClickSig(int, int)), this, SLOT(rightClickOnSpriteView(int,int)));
  //  connect(ui->widget, SIGNAL(drawPaintBucket(int,int,QColor)),this,SLOT(drawPaintBucket(int,int,QColor)));
}

MainWindow::~MainWindow()
{
    delete ui;
//    delete introDialog;
//    delete scrollArea;
//    delete thumbnail;
//    delete tableModel;
//    delete animationTimer;
//    delete introDialog;
}


void MainWindow::go(int dimension){
    QPixmap map(512,512);
    map.fill(Qt::transparent);
    ui->widget->setSprite(map);
    introDialog->close();
    int expo = (int)log(dimension)/log(2);
    ui->widget->minZoom = expo;

    ui->widget->spriteDimension = dimension;
    ui->widget->scaleFactor = (int)(div(512, dimension).quot);

    ui->widget->maxZoom = 32;

    model.addFrame(dimension,dimension);
    ui->widget_2->model = &model;
    timerInterval = (int)(1000/24);
    thumbnail = new QTableWidgetItem;
    currentGalleryIndex = 0;
    QImage img = model.getFrame(0);

    thumbnail -> setData(Qt::DecorationRole, QPixmap:: fromImage(img));
    ui->tableWidget->setSortingEnabled(false);

    ui->tableWidget->setRowCount(1);
    ui->tableWidget->setColumnCount(model.amountOfFrames());
    ui->tableWidget->setItem(0,0,thumbnail);

    animationTimer = new QTimer(this);
    connect(animationTimer,SIGNAL(timeout()),this,SLOT(updateAnimation()));
    animationTimer->start(timerInterval);
    currentFrameEditorIndex = 0;
    currentFramePanelIndex = 0;
}


void MainWindow::primaryColorChanged(QColor col){
    ui->widget->setPrimaryColor(col);
}

/*void MainWindow::drawPaintBucket(int x, int y, QColor colorToPaint){
    if(colorToPaint == (QColor(model.getFrame(currentFrameEditorIndex).pixel(x,y)))){
        cout << x << ","<< y << endl;
        return;
//        model.setPixelValueInFrame(model.amountOfFrames()-1, i,j, color.red(), color.green(), color.blue(), ((currentFrame.pixel(i,j) >> 24)));
    }
    else{

        if((x -1 >= 0) &&(y >= 0 && y < model.getFrameWidth(0))){
            drawPaintBucket(x - 1, y, colorToPaint);
        }
        if((x+1 < model.getFrameWidth(0)) &&(y >= 0 && y < model.getFrameWidth(0))){

          drawPaintBucket(x + 1, y, colorToPaint);
        }
        if((y+1 < model.getFrameWidth(0)) && (x >= 0 && x < model.getFrameWidth(0))){
            drawPaintBucket(x, y+1, colorToPaint);
        }
        if((y -1 >= 0) && &&(x >= 0 && x < model.getFrameWidth(0))){
            drawPaintBucket(x,y-1, colorToPaint);
        }
        model.setPixelValueInFrame(currentFrameEditorIndex, x,y, colorToPaint.red(), colorToPaint.green(), colorToPaint.blue(), ((model.getFrame(currentFrameEditorIndex).pixel(x,y) >> 24)));

    }
}*/

void MainWindow::rightClickOnSpriteView(int x, int y){
    cout << "rightClicked" << endl;
    model.setPixelValueInFrame(currentFrameEditorIndex, x, y, 0,0,0,0);
    QImage newImage = model.getFrame(currentFrameEditorIndex);
    updateFilmStrip(newImage);
    QPixmap newPixmap;
    newPixmap.convertFromImage(newImage);
    QSize newSize = QSize(newPixmap.size()*ui->widget->getScaleFactor());
    QPixmap newPix = newPixmap.scaled(newSize, Qt::KeepAspectRatio, Qt::FastTransformation);
    ui->widget->setSprite(newPix.scaled(512,512));
}

void MainWindow::changePixelModel(int x, int y, QColor color){
    model.setPixelValueInFrame(currentFrameEditorIndex, x, y, color.red(), color.green(),color.blue(), currentAlpha);
    QImage newImage = model.getFrame(currentFrameEditorIndex);
    updateFilmStrip(newImage);
    QPixmap newPixmap;
    newPixmap.convertFromImage(newImage);
    QSize newSize = QSize(newPixmap.size()*ui->widget->getScaleFactor());
    QPixmap newPix = newPixmap.scaled(newSize, Qt::KeepAspectRatio, Qt::FastTransformation);
    ui->widget->setSprite(newPix.scaled(512,512));

}

IntroDialog* MainWindow::getPointerToIntro(){
    return introDialog;
}

void MainWindow::on_addFrameButton_clicked()
{
    QImage currentFrame = model.getFrame(currentFrameEditorIndex);
    currentFrameEditorIndex++;
    model.addFrame(currentFrame.width(),currentFrame.height());

    //update last frame of gallery to be added.
    currentFrame = model.getFrame(model.amountOfFrames()-1);
    thumbnail = new QTableWidgetItem();
    thumbnail -> setData(Qt::DecorationRole, QPixmap:: fromImage(currentFrame).scaled(128,128));
    ui->tableWidget->setColumnCount(model.amountOfFrames());
    ui->tableWidget->setItem(0,model.amountOfFrames()-1,thumbnail);;

}

void MainWindow::updateAnimation(){
    QImage currentPanelFrame = model.getFrame(currentFramePanelIndex);
    QPixmap panelMap;
    QPixmap tempMap;
    QSize newSize = QSize(256,256);
    tempMap.convertFromImage(currentPanelFrame);
    panelMap = tempMap.scaled(newSize, Qt::KeepAspectRatio, Qt::FastTransformation);
    ui->animationPanelLabel->setPixmap(panelMap);
    if(currentFramePanelIndex < model.amountOfFrames() -1){
        currentFramePanelIndex ++;
    }
    else{
        currentFramePanelIndex = 0;
    }

}

void MainWindow::updateFilmStrip(QImage currentFrame){
    cout<<currentFrameEditorIndex<<endl;
    thumbnail = new QTableWidgetItem();
    thumbnail -> setData(Qt::DecorationRole, QPixmap:: fromImage(currentFrame).scaled(128,128));
    ui->tableWidget->setColumnCount(model.amountOfFrames());

    cout<<"Inserting " << endl;
    ui->tableWidget->setItem(0,currentFrameEditorIndex,thumbnail);
}

void MainWindow::on_tableWidget_clicked(const QModelIndex &index){
    currentGalleryIndex = index.column();
    QPixmap tempMap;
    tempMap.fill(Qt::transparent);
    currentFrameEditorIndex = index.column();
    tempMap.convertFromImage(model.getFrame(currentFrameEditorIndex));
    ui->widget->setSprite(tempMap.scaled(512,512));
}

/*void MainWindow::on_tableWidget_doubleClicked(const QModelIndex &index)
{
    QPixmap tempMap;
    currentFrameEditorIndex = index.column();
    tempMap.convertFromImage(model.getFrame(currentFrameEditorIndex));
    ui->widget->setSprite(tempMap.scaled(512,512));
}*/

void MainWindow::on_duplicateFrameButton_clicked()
{
    QImage currentFrame = model.getFrame(currentGalleryIndex);
    model.addFrame(currentFrame.width(),currentFrame.height());


    for(int i=0; i<currentFrame.height(); i++){
        for(int j=0; j<currentFrame.width(); j++){
            QColor color = QColor(currentFrame.pixel(i,j));
            cout<< "current alpha " << currentAlpha << endl;
            model.setPixelValueInFrame(model.amountOfFrames()-1, i,j, color.red(), color.green(), color.blue(), ((currentFrame.pixel(i,j) >> 24)));
        }
    }

    QPixmap newMap;
    newMap.fromImage(model.getFrame(model.amountOfFrames()-1));
    updateFilmStripAtIndex(newMap.toImage(),model.amountOfFrames()-1);

}

void MainWindow::updateFilmStripAtIndex(QImage image, int index){
    QImage currentFrame = model.getFrame(currentGalleryIndex);
    thumbnail = new QTableWidgetItem();
    thumbnail -> setData(Qt::DecorationRole, QPixmap:: fromImage(currentFrame).scaled(128,128));
    ui->tableWidget->setColumnCount(model.amountOfFrames());
    ui->tableWidget->setItem(0,index,thumbnail);
}

void MainWindow::on_fpsSlider_valueChanged(int value)
{
   int val = (int) 1000/value;
   animationTimer->setInterval(val);
   QString sVal = QString::number(value);
   ui->fpsLabel->setText("FPS: " + sVal);
}

void MainWindow::on_clearFrameButton_clicked(){
    QImage currentFrame = model.getFrame(currentGalleryIndex);
    for(int i=0; i<currentFrame.height(); i++){
        for(int j=0; j<currentFrame.width(); j++){
            model.setPixelValueInFrame(currentGalleryIndex,i,j,0,0,0,0);
        }
    }
    QPixmap newMap;
    newMap.fromImage(model.getFrame(currentGalleryIndex));
    updateFilmStripAtIndex(newMap.toImage(),currentGalleryIndex);
    ui->widget->setSprite(newMap.scaled(512,512));
}

void MainWindow::on_deleteFrameButton_clicked(){

}

void MainWindow::on_saveButton_clicked()
{
    cout<<"getting there"<<endl;

    QString file = QFileDialog::getSaveFileName(this,"Save SSP", "/home", "");
    if(file != ""){
        model.saveSSP(file.toStdString(), "");
    }
}

void MainWindow::on_openButton_clicked()
{
    QStringList file = QFileDialog::getOpenFileNames(this,"Select SSP",
                "/home","(*.*)");
    if(file.size() != 0){
        QString fileName = file.at(0);
        qDebug() <<fileName << endl;
        model.openSSP(fileName.toStdString(), "");
    }
    ui->tableWidget->clear();
    ui->tableWidget->clearContents();
    for(int i = 0; i < model.amountOfFrames();i++){
        QImage currentFrame = model.getFrame(i);
        thumbnail = new QTableWidgetItem();
        thumbnail->setData(Qt::DecorationRole,QPixmap::fromImage(currentFrame).scaled(128,128));
        ui->tableWidget->setColumnCount(model.amountOfFrames());
        ui->tableWidget->setItem(0, i, thumbnail);
    }
    ui->widget->scaleFactor = (int)(div(512, model.getFrameWidth(0)).quot);
    currentFrameEditorIndex = 0;
    QPixmap newMap;

    newMap.fromImage(model.getFrame(0));
    ui->widget->setSprite(newMap.scaled(512,512));
}

void MainWindow::on_gifButton_clicked()
{
   QString file = QFileDialog::getSaveFileName(this, "Save GIF", "/home", "");
   if(file != ""){
        model.exportGIF(file.toStdString(), "", ui->fpsSlider->value());
   }
}

void MainWindow::changeAlpha(int newA){
    //cout << "alphachanged"<< newA << endl;
    currentAlpha = newA;
}

