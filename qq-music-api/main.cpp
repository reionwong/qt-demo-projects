#include <QApplication>
#include "widget.h"
#include "qqmusic_api.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Widget widget;
    widget.resize(800, 600);
    widget.show();

    return app.exec();
}
