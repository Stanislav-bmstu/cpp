#include <QtWidgets>
#include <QtGui>
#include "mainwindow.h"
#include "scene3d.h"

MainWindow::MainWindow() // конструктор
{
    scene1 = new Scene3D; // создаю динамический объект класса Scene3D
    setCentralWidget(scene1); // обозначаю scene1 центральным виджетом в главном окне

    this->setWindowTitle(tr("Game")); // название главного окна
}
