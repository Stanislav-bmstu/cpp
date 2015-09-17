#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "scene3d.h"

class MainWindow : public QMainWindow // класс MainWindow как подкласс QMainWindow
{
    Q_OBJECT // макрос, который нужно использовать при работе с сигналами и слотами

private:
    Scene3D* scene1; // указатель на объект класса Scene3D

public:
    MainWindow(); // конструктор объекта главного окна
};
#endif
