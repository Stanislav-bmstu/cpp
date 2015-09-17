#ifndef YADRO_H
#define YADRO_H

#include <QGLWidget>
#include <interface3dmodel.h>
#include <sfera.h>

class Yadro : public Interface3dModel {
    GLfloat VertexArrayYadro[6][3]; // декларируем массив вершин
    GLuint  IndexArrayYadro [6][3];  // декларируем массив индексов вершин
    GLfloat TextureArray[240][2];


    int     pli;        // точка вылета "ПЛИ"
    int     plifinish;  // цель "ПЛИ"
    int     shag;       // шаг полета ядра
    bool    signTh;     // знак поворота тета
    bool    signPh;     // знак поворота пси
    GLfloat deltaTh ;   // дельта тета
    GLfloat deltaPh ;   // дельта пси
    GLfloat deltaR  ;   // дельта расстояния от земли до ядра

public:
    Yadro();
    GLfloat delta1;     // флаг состояния ядра (долетела до цели)
    GLfloat delta2;     // флаг состояния ядра (готова к взлету)
    bool    doletelo;
    void getVerTexArrays(); // определить массив вершин
    void getIndexArray();   // определить массив индексов вершин
    void draw();            // отрисовка

    void getStartVerTexArrays(GLfloat sferaV[80][3][3], int start); // вывод ракеты на стартовую позицию

    void shot(int start, int finish);                   // выстрел
    void fly(GLfloat sferaV[80][3][3], Sfera &sfera);   // полет
};

#endif // YADRO_H
