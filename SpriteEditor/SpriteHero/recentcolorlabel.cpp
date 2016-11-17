#include "recentcolorlabel.h"

RecentColorLabel::RecentColorLabel(QWidget *parent) : QLabel(parent)
{
    labelColor = Qt::white;
}

void RecentColorLabel::mousePressEvent(QMouseEvent *event){
    if(event->button() == Qt::RightButton){
        labelColor= QColorDialog::getColor(Qt::white, this);
        QPixmap map(this->width(), this->height());
        map.fill(labelColor);
        this->setPixmap(map);
    }
    else{
        emit setPrimColor(labelColor);
    }
    //update();
}

void RecentColorLabel::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    QPen pen(labelColor);
    painter.setPen(Qt::black);
    QRect rect(this->x(), this->y(), this->width(), this->height());
    painter.drawRect(rect);
    painter.fillRect(rect,labelColor);
}
