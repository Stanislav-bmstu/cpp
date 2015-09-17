#ifndef GAMER_H
#define GAMER_H

#include <triangle.h>


class Gamer
{
    static const int MAX_NUMBER_OF_SHIPS = 5;
    int playerShips[MAX_NUMBER_OF_SHIPS];
    int realNumberOfShips;
    bool buildAll;
    bool gaming;

    Triangle* Triangles;

public:
    Gamer();
    ~Gamer();

    void init(Triangle* TriangleArray);

    bool hasBuildAll();

    // игровой процесс
    bool isGaming();
    void beginGame();
    void endGame();

    // операции с кораблями
    bool include(int number);
    void buildShip(int number);
    void killShip(int number);
    void failShot(int number);
    void cleanAll();

    bool wasKilled(int number);
};

#endif // GAMER_H
