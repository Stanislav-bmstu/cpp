#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <triangle.h>
#include <gamer.h>
#include <yadro.h>
#include <QGLWidget>

class Gameplay
{
    Yadro*    yadro;
    Sfera*    sfera;
    Triangle* Triangles;
    Gamer     gamer[2];

    int start;
    int finish;

    bool oldplayer;
    int oldfinish;


public:
    bool fire;
    Gameplay();
    ~Gameplay();

    void init(Sfera* asfera, Yadro* ayadro, Triangle* TriangleArray);

    // Непосредственно игра
    void game(int number);

    // Выстрел
    void shot(int start, int finish);

    // Строительство
    void building(int number);

    // Возможность ведения огня
    bool maybeFire();

    // Функции запуска
    bool selectStart();
    int  returnStart();
    void proverka();

};

#endif // GAMEPLAY_H
