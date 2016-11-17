#include "colorchooser.h"
#include "ui_colorchooser.h"

ColorChooser::ColorChooser(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ColorChooser)
{
    ui->setupUi(this);
    QPixmap primColor(ui->label->width(), ui->label->height());
    ui->redBox->setRange(0, 255);
    ui->blueBox->setRange(0, 255);
    ui->greenBox->setRange(0,255);
    ui->redSlider->setRange(0,255);
    ui->alphaSlider->setValue(255);
    primColor.fill(Qt::black);
    ui->label->setPixmap(primColor);    gradient = QLinearGradient(QPoint(ui->grad->x(), ui->grad->y()),
                             QPoint(ui->grad->x() + (ui->grad->width()),ui->grad->y() + ui->grad->height()));
    gradient.setColorAt(0, Qt::red);
    gradient.setColorAt(.2, Qt::yellow);
    gradient.setColorAt(.3, Qt::green);
    gradient.setColorAt(.5, Qt::cyan);
    gradient.setColorAt(.7, Qt::blue);
    gradient.setColorAt(.9, Qt::magenta);
}

void ColorChooser::labelChoseSlot(QColor color){
    emit rValueChanged(color);
}

ColorChooser::~ColorChooser()
{
    delete ui;
}

void ColorChooser::paintEvent(QPaintEvent* event){
    QPoint topLeft(ui->grad->x(), ui->grad->y());
    QRect rect(topLeft.x(), topLeft.y(), ui->grad->width(), ui->grad->height());
    QPainter painter(this);
    painter.fillRect(rect, gradient);

}

void ColorChooser::mousePressEvent(QMouseEvent *event){
    qDebug() << "mouse pressed" << endl;
    int x = event->x();
    int y = event->y();
    int minX = ui->grad->x();
    int maxX = ui->grad->x() + ui->grad->width();
    int minY = ui->grad->y();
    int maxY = ui->grad->y() + ui->grad->height();
    QRect rect = ui->grad->rect();
    if((x >=minX) && (x < maxX) && (y > minY) && (y < maxY)){
        qDebug() << x << " , " << y << endl;
        QColor colorChose = QColorDialog::getColor(Qt::white, this);
        emit rValueChanged(colorChose);
        QPixmap map(ui->label->width(), ui->label->height());
        map.fill(colorChose);
        ui->redSlider->setValue(colorChose.red());
        ui->blueSlider->setValue(colorChose.blue());
        ui->greenSlider->setValue(colorChose.green());
    }
}

void ColorChooser::on_redBox_valueChanged(int arg1){
    emit rValueChanged(QColor(arg1,ui->greenBox->value(),ui->blueBox->value()));
    QPixmap map(ui->label->width(), ui->label->height());
    map.fill(QColor(arg1,175,42));
    ui->redSlider->setValue(arg1);
    ui->label->setPixmap(map);
}

void ColorChooser::on_greenBox_valueChanged(int value){
    int r = ui->redBox->value();
    int b = ui->blueBox->value();
    emit rValueChanged(QColor(r, value, b));
    QPixmap map(ui->label->width(), ui->label->height());
    map.fill(QColor(r,value,b));
    ui->greenSlider->setValue(value);
    ui->label->setPixmap(map);
}


void ColorChooser::on_blueBox_valueChanged(int value){
    int r = ui->redBox->value();
    int g = ui->greenBox->value();
    emit rValueChanged(QColor(r, g, value));
    QPixmap map(ui->label->width(), ui->label->height());
    map.fill(QColor(r, g, value));
    ui->blueSlider->setValue(value);
    ui->label->setPixmap(map);
}

void ColorChooser::on_redSlider_valueChanged(int value){
    int g = ui->greenBox->value();
    int b = ui->blueBox->value();
    emit rValueChanged(QColor(value, g, b));
    QPixmap map(ui->label->width(), ui->label->height());
    map.fill(QColor(value, g, b));
    ui->redBox->setValue(value);
    ui->label->setPixmap(map);

}

void ColorChooser::on_greenSlider_valueChanged(int value){
    int r = ui->redBox->value();
    int b = ui->blueBox->value();
    emit rValueChanged(QColor(r, value, b));
    QPixmap map(ui->label->width(), ui->label->height());
    map.fill(QColor(r, value, b));
    ui->greenBox->setValue(value);
    ui->label->setPixmap(map);
}

void ColorChooser::on_blueSlider_valueChanged(int value){
    int r = ui->redBox->value();
    int g = ui->greenBox->value();
    emit rValueChanged(QColor(r, g, value));
    QPixmap map(ui->label->width(), ui->label->height());
    map.fill(QColor(r, g, value));
    ui->blueBox->setValue(value);
    ui->label->setPixmap(map);
}



void ColorChooser::on_alphaBox_valueChanged(int arg1){
    ui->alphaBox->setValue(arg1);
    ui->alphaSlider->setValue(arg1);
    emit alphaChangedSig(arg1);
}

void ColorChooser::on_alphaSlider_valueChanged(int value){
    on_alphaBox_valueChanged(value);
}
