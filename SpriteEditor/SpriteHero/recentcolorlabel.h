#ifndef RECENTCOLORLABEL_H
#define RECENTCOLORLABEL_H

#include <QLabel>
#include <QWidget>
#include <QColorDialog>
#include <QPainter>
#include <QMouseEvent>

class RecentColorLabel : public QLabel
{
    Q_OBJECT
private:
    QColor labelColor;
public:

    explicit RecentColorLabel(QWidget *parent = 0);
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *);


signals:
    void setPrimColor(QColor);

public slots:

};

#endif // RECENTCOLORLABEL_H
