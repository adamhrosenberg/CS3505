#ifndef COLORCHOOSER_H
#define COLORCHOOSER_H

#include <QWidget>
#include <QRadialGradient>
#include <QDebug>
#include <QPoint>
#include <QPainter>
#include <QMouseEvent>
#include <QColorDialog>
#include <QRgb>
#include "math.h"
#include "model.h"

namespace Ui {
class ColorChooser;
}

class ColorChooser : public QWidget
{
    Q_OBJECT

public:
    explicit ColorChooser(QWidget *parent = 0);
    ~ColorChooser();
    void setColorFromGrad(int, int);
    Model* model;


private slots:

    void on_redBox_valueChanged(int);
    void on_greenBox_valueChanged(int);
    void on_blueBox_valueChanged(int);
    void on_redSlider_valueChanged(int);
    void on_blueSlider_valueChanged(int);
    void on_greenSlider_valueChanged(int);
    void on_alphaBox_valueChanged(int arg1);
    void on_alphaSlider_valueChanged(int value);

public slots:
    void mousePressEvent(QMouseEvent*);
    void labelChoseSlot(QColor);

protected:
    void paintEvent(QPaintEvent*);

signals:
    void rValueChanged(QColor);
    void alphaChangedSig(int);

private:
    Ui::ColorChooser *ui;
    QLinearGradient gradient;
};

#endif // COLORCHOOSER_H
