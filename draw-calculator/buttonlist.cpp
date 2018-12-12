#include "buttonlist.h"
#include <QPainter>
#include <QDebug>
#include <QEvent>
#include <QMouseEvent>

ButtonList::ButtonList(QWidget *parent)
    : QWidget(parent)
{
    buttonWidth = 80;
    buttonHeight = 60;
    hoverIndex = -1;
    pressIndex = -1;

    setMouseTracking(true);
    setFixedHeight(300);

    initButtonName();
}

void ButtonList::initButtonName()
{
    buttonName << "C" << "%" << "←" << "÷"
               << "7" << "8" << "9" << "×"
               << "4" << "5" << "6" << "－"
               << "1" << "2" << "3" << "＋"
               << "0" << "." << "( )" << "＝";
}

void ButtonList::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.setBrush(Qt::white);
    painter.drawRect(rect());

    QFont font;
    font.setPointSize(13);
    painter.setFont(font);

    for (int y = 0; y < 5; ++y) {
        for (int x = 0; x < 4; ++x) {

            const int column = x + y * 4;

            if (buttonName.at(column) == "＝") {
                const QRect rect(x * buttonWidth, y * buttonHeight, buttonWidth - 1, buttonHeight - 1);
                painter.setPen(QColor("#2CA7F8"));
                painter.setBrush(QColor("#2CA7F8"));
                painter.drawRect(rect);
                painter.setPen(QColor("#FFFFFF"));
                painter.drawText(rect, Qt::AlignCenter, buttonName.at(column));
            } else {

                // hover state
                if (column == hoverIndex) {
                    painter.setPen(QColor("#2CA7F8"));
                } else {
                    painter.setPen(QColor("#F2F2F2"));
                }

                // press state
                if (column == pressIndex) {
                    painter.setBrush(QColor("#F7F7F7"));
                } else {
                    painter.setBrush(QColor("#FFFFFF"));
                }
                
                const QRect rect(x * buttonWidth, y * buttonHeight, buttonWidth - 1, buttonHeight - 1);
                painter.drawRect(rect);

                if (buttonName.at(column) == "＋" || buttonName.at(column) == "－" ||
                    buttonName.at(column) == "×" || buttonName.at(column) == "÷") {
                    painter.setPen(QColor("#2CA7F8"));
                } else {
                    painter.setPen(QColor("#4B4B4B"));
                }
                painter.drawText(rect, Qt::AlignCenter, buttonName.at(column));

            }
        }
    }
}

void ButtonList::mouseMoveEvent(QMouseEvent *e)
{
    int column = getButtonColumn(e->x(), e->y());

    if (hoverIndex != column) {
        hoverIndex = column;
        update();
    }
}

void ButtonList::leaveEvent(QEvent *)
{
    hoverIndex = -1;
    update();
}

void ButtonList::mousePressEvent(QMouseEvent *e)
{
    isPress = true;

    pressIndex = getButtonColumn(e->x(), e->y());
    update();
}

void ButtonList::mouseReleaseEvent(QMouseEvent *e)
{
    isPress = false;

    emit clicked(buttonName.at(pressIndex));

    pressIndex = -1;
    update();
}

int ButtonList::getButtonColumn(const int x, const int y)
{
    return x / buttonWidth + (y / buttonHeight * 4);
}
