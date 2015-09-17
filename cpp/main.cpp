#include <QtWidgets>
#include "mainwindow.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);  // создаётся приложение
    MainWindow mainwindow1;
    mainwindow1.resize(500, 500);
    mainwindow1.show();
    return app.exec();
}

