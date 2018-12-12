#ifndef COLORVIEW_H
#define COLORVIEW_H

#include <QLabel>

class ColorView : public QLabel
{
    Q_OBJECT

public:
    ColorView(QWidget *parent = 0);

    void setBackgroundColor(const QString &color);

protected:
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);

signals:
    void clicked();
};

#endif // COLORVIEW_H
