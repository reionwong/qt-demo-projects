#include "pickerwindow.h"
#include <QApplication>
#include <QScreen>
#include <QPainter>
#include <QKeyEvent>

PickerWindow::PickerWindow(QWidget *parent)
    : QWidget(parent)
{
    setWindowFlags(Qt::X11BypassWindowManagerHint | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | Qt::Tool);
    setMouseTracking(true);

    setCursor(Qt::BlankCursor);
}

void PickerWindow::start()
{
    m_pixmap = QApplication::primaryScreen()->grabWindow(0);

    resize(m_pixmap.size());
    move(0, 0);
}

void PickerWindow::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);

    QPoint tl, br, pos(QCursor::pos());

    tl.setX(pos.x() - 10);
    tl.setY(pos.y() - 10);
    br.setX(pos.x() + 10);
    br.setY(pos.y() + 10);

    QRect rect(tl, br);

    QPixmap pix = m_pixmap.copy(rect);
    QPixmap zoomPix = pix.scaled(pix.width() * 4, pix.height() * 4);

    QPainter painter(this);
    painter.drawPixmap(0, 0, m_pixmap);

    int x = qMax(0, pos.x() - (zoomPix.width() / 2));
    int y = qMax(0, pos.y() - (zoomPix.height() / 2));

    painter.drawImage(x, y, QImage(":/image/magnifier.png").scaled(zoomPix.width(), zoomPix.height()));
    painter.drawPixmap(x+5, y+5, zoomPix.scaled(zoomPix.width()-10, zoomPix.height()-10));

    painter.drawImage(QRect(pos.x()-4, pos.y()-4, 10, 10), QImage(":/image/center_rect.png").scaled(10, 10));

    QImage img = m_pixmap.copy(pos.x(), pos.y(), 1, 1).toImage();
    QColor color = QColor(img.pixel(0, 0));
    QString hex = QString("#%1%2%3").arg(color.red(), 2, 16, QLatin1Char('0'))
            .arg(color.green(), 2, 16, QLatin1Char('0'))
            .arg(color.blue(), 2, 16, QLatin1Char('0')).toUpper();

    QRect textRect = painter.boundingRect(QRect(x+5, y + zoomPix.height(), 10, 10), Qt::TextWordWrap, hex);
    textRect.adjust(0, 2, 2, 2);

    painter.setBrush(Qt::white);
    painter.drawRect(textRect);
    painter.drawText(textRect, hex);
    painter.end();
}

void PickerWindow::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Escape)
        setVisible(false);
}

void PickerWindow::mouseMoveEvent(QMouseEvent *e)
{
    update();
}

void PickerWindow::mousePressEvent(QMouseEvent *e)
{

}

void PickerWindow::mouseReleaseEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        image = m_pixmap.toImage();

        QColor color = image.pixel(QCursor::pos());

        setVisible(false);

        emit finished(color);
    }
}
