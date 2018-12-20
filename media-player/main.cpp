#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setWindowIcon(QIcon(":/resources/icon.svg"));

    MainWindow window;

    window.setWindowTitle("media-player");
    window.setMinimumSize(700, 500);
    window.show();

    return app.exec();
}
