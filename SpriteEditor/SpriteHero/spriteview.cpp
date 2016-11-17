#include "spriteview.h"

SpriteView::SpriteView(QWidget* parent):
    QLabel(parent),
    scaleFactor(1),
    spriteDimension(1)
{

    QPixmap sprite2;
    sprite2 = QPixmap(spriteDimension, spriteDimension);

    QSize newSize = QSize(sprite2.size()*getScaleFactor());
    sprite = sprite2.scaled(newSize, Qt::KeepAspectRatio, Qt::FastTransformation);

    sprite.fill(Qt::white);
    setScaledContents(false);
    //setPixmap(sprite);
    primaryColor = Qt::black;

}
SpriteView::~SpriteView(){

}

void SpriteView::setPrimaryColor(QColor newPcolor){
//    cout<<"Test"<<endl;
    primaryColor = newPcolor;
//    cout << "primary color changed" <<endl;
}

void SpriteView::mousePressEvent(QMouseEvent *event){
    if(event->button() == Qt::RightButton){
        cout<<"GOT THE FUCK IN" << endl;
        int x = std::div(event->x(), scaleFactor).quot;
        int y = std::div(event->y(), scaleFactor).quot;
        emit rightClickSig(x, y);
    }
    else if(event->button() == Qt::LeftButton){
        QPoint coords = event->pos();
        scaleMouseCoordsForSprite(coords);
    }
}


void SpriteView::mouseMoveEvent(QMouseEvent *event){
    if(event->buttons() & Qt::LeftButton){
       QPoint coords = event->pos();
       scaleMouseCoordsForSprite(coords);
    }
    else if(event->buttons() & Qt::RightButton){
        int x= std::div(event->x(), scaleFactor).quot;
        int y= std::div(event->y(), scaleFactor).quot;
        emit rightClickSig(x, y);
    }
}
//void SpriteView::drawPaintBucket(int x, int y, QColor colorToPaint){
//    if(colorToPaint != (QColor(currentFrame.pixel(x,y)))){
//        cout << x << ","<< y << endl;
//        return;
//    }
//    else{
//        scaleMouseCoordsForSprite(QPoint(x,y));
//        drawPaintBucket(x - 1, y, colorToPaint);
//        drawPaintBucket(x + 1, y, colorToPaint);
//        drawPaintBucket(x, y+1, colorToPaint);
//        drawPaintBucket(x,y-1, colorToPaint);
//    }
//}

/*void SpriteView::wheelEvent(QWheelEvent *event){
    if(event->delta() < 0){
        if(scaleFactor>minZoom){
           scaleFactor /= 2;
           spriteDimension *=2;
           sprite = QPixmap(spriteDimension,spriteDimension);
           sprite.fill(Qt::white);

        }
        cout<<"New SF: " <<scaleFactor << endl;
    }
    else{
        if(scaleFactor<maxZoom){
           scaleFactor *= 2;
           spriteDimension /= 2;
           sprite = QPixmap(spriteDimension,spriteDimension);
           sprite.fill(Qt::white);
        }
        cout<<"New SF:\t" <<scaleFactor << endl;
    }
    QPoint coords = event->pos();
    scaleMouseCoordsForSprite(coords);
}*/

void SpriteView::scaleMouseCoordsForSprite(QPoint p){

    int x = std::div(p.x(), scaleFactor).quot;
    int y = std::div(p.y(), scaleFactor).quot;
//    cout<<"Scaled coordinates, (x,y): (" << x << " , " << y << " )" << endl;
    emit updateModelPixelSig(x, y,primaryColor);

}


int SpriteView::getScaleFactor(){
    return scaleFactor;
}

void SpriteView::setSprite(QPixmap newImage){
    sprite = newImage;
    setPixmap(sprite);
}

