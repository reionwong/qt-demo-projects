#include "dbutton.h"

DButton::DButton(QWidget *parent)
    : QPushButton(parent)
{
    this->setStyleSheet("border:none; outline: none;");
    this->setIconSize(QSize(25, 25));
    this->setFixedSize(32, 32);
    this->setCursor(QCursor(Qt::PointingHandCursor));
}
