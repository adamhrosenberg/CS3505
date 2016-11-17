#ifndef SPRITEVIEW_H
#define SPRITEVIEW_H
#include <QLabel>
#include <QPixmap>
#include <QImage>
#include <iostream>
#include <QWheelEvent>
#include "model.h"

using namespace std;


class SpriteView: public QLabel
{

    Q_OBJECT

public:
    explicit SpriteView(QWidget* parent);
    ~SpriteView();
    void setPrimaryColor(QColor);
    void setSprite(QPixmap);
    int getScaleFactor();
    int spriteDimension;
    int scaleFactor;
    int minZoom;
    int maxZoom;

private:

    QPixmap sprite;
    QColor primaryColor;

    void mousePressEvent(QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent*);
    //void wheelEvent(QWheelEvent *event);
    void scaleMouseCoordsForSprite(QPoint);

signals:
    void rightClickSig(int x, int y);
    void updateModelPixelSig(int x, int y, QColor);

};

#endif // SPRITEVIEW_H
