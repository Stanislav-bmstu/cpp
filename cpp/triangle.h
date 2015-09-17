#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <QGLWidget>
#include <interface3dmodel.h>

class Triangle
{
    GLfloat** TextureArray;

    int     number;     // Номер сектора
    bool    playerN1;
    bool    playerN2;
    bool    ship;
    bool    enabled;    // Доступность сектора

public:
    Triangle();
    void init(int numberTr, bool player, GLfloat** Texture);
    ~Triangle();

    bool isPlayerN1();  // проверки принадлежности
    bool isPlayerN2();
    bool isShip();
    int  isNumber();

    void build();       // перерасчет текстурных координат
    void kill();
    void fail();
    void clean();
};

#endif // TRIANGLE_H
