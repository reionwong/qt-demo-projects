#include "colorview.h"
#include <QMouseEvent>

ColorView::ColorView(QWidget *parent)
    : QLabel(parent)
{
    setMouseTracking(true);

    setFixedSize(92, 70);
}

void ColorView::setBackgroundColor(const QString &color)
{
    setStyleSheet("background: " + color);
}

void ColorView::mousePressEvent(QMouseEvent *ev)
{
    if (ev->button() == Qt::LeftButton)
        emit clicked();
}

void ColorView::mouseMoveEvent(QMouseEvent *)
{
    setCursor(Qt::PointingHandCursor);
}
