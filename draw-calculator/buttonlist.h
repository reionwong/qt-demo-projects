#ifndef BUTTONLIST_H
#define BUTTONLIST_H

#include <QWidget>
#include <QVector>

class ButtonList : public QWidget
{
    Q_OBJECT

public:
    explicit ButtonList(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void leaveEvent(QEvent *);
    int getButtonColumn(const int x, const int y);

signals:
    void clicked(const QString &text);

private:
    QList<QString> buttonName;
    int buttonWidth;
    int buttonHeight;
    int hoverIndex;
    int pressIndex;
    bool isPress;

    void initButtonName();
};

#endif // BUTTONLIST_H
