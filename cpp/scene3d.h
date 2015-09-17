#ifndef SCENE3D_H
#define SCENE3D_H

#include <QGLWidget> // подключаем класс QGLWidget
#include <sfera.h>
#include <yadro.h>
#include <gameplay.h>

class Scene3D : public QGLWidget // класс Scene3D наследует встроенный класс QGLWidget
{
    Q_OBJECT          // макрос, который нужно использовать при работе с сигналами и слотами

private:
    GLfloat ratio; // отношение высоты окна виджета к его ширине

    // для первой фигуры
    GLfloat xRot1; // угол поворота вокруг оси X
    GLfloat yRot1; // угол поворота вокруг оси Y
    GLfloat zRot1; // угол поворота вокруг оси Z
    GLfloat xTra1; // величина трансляции по оси X
    GLfloat yTra1; // величина трансляции по оси Y
    GLfloat zTra1; // величина трансляции по оси Z
    GLfloat nSca;   // переменная отвечает за масштабирование объекта

    // для второй фигуры
    GLfloat xRot2; // угол поворота вокруг оси X
    GLfloat yRot2; // угол поворота вокруг оси Y
    GLfloat zRot2; // угол поворота вокруг оси Z
    GLfloat xTra2; // величина трансляции по оси X
    GLfloat yTra2; // величина трансляции по оси Y
    GLfloat zTra2; // величина трансляции по оси Z

    QPoint ptrMousePosition;        // координата указателя мыши
    QTimer *timer; // декларируем таймер

    Sfera sfera;
    Yadro yadro;

    Gameplay gameplay;

    // Отображение сцены
    void scale_plus();      // приблизить сцену
    void scale_minus();     // удалиться от сцены
    void rotate_up();       // повернуть сцену вверх
    void rotate_down();     // повернуть сцену вниз
    void rotate_left();     // повернуть сцену влево
    void rotate_right();    // повернуть сцену вправо
    void translate_down();  // транслировать сцену вниз
    void translate_up();    // транслировать сцену вверх
    void defaultScene();    // наблюдение сцены по умолчанию

    //void getVerTexArrays();   // определить массив вершин
    //void getIndexArray();     // определить массив индексов вершин
    void genTextures();         // создать текстуры
    //void drawFigure();        // построить фигуру

    void selectFigures(QPoint mp); // выбрать фигуру

protected:    
    // OpenGL
    void initializeGL();                    // метод для проведения инициализаций, связанных с OpenGL:
    void resizeGL(int nWidth, int nHeight); // метод вызывается при изменении размеров окна виджета
    void paintGL();                         // метод, чтобы заново перерисовать содержимое виджета

    // Mouse
    void mousePressEvent(QMouseEvent* pe);      // метод обработки события мыши при нажатии клавиши мыши
    void mouseMoveEvent(QMouseEvent* pe);       // метод обработки события мыши при перемещении мыши
    void mouseReleaseEvent(QMouseEvent* pe);    // метод обработки событий мыши при отжатии клавиши мыши
    void mouseDoubleClickEvent(QMouseEvent* pe);// метод обработки события мыши при нажатии клавиши мыши

    // Wheel
    void wheelEvent(QWheelEvent* pe);           // метод обработки событий колесика мыши

    // Key
    void keyPressEvent(QKeyEvent* pe);          // методы обработки события при нажатии клавиши

private slots:
    void change();                          // изменение углов поворота и величины трансляции
    void stopTmr();                         // остановить таймер
    void startTmr();                        // запустить таймер

public:
    Scene3D(QWidget* parent = 0);           // конструктор класса
    ~Scene3D();                             // деструктор
};
#endif
