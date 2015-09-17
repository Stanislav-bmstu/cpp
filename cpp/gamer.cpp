#include "gamer.h"

Gamer::Gamer()
{
    realNumberOfShips = 0;
    buildAll    =   false;
    gaming      =   false;

    for (int i = 0; i < MAX_NUMBER_OF_SHIPS; i++) {
        playerShips[i] = -1;
    }
}

Gamer::~Gamer()
{

}

void Gamer::init(Triangle *TriangleArray)
{
    Triangles = TriangleArray;
}

bool Gamer::hasBuildAll()
{
    return buildAll;
}

bool Gamer::isGaming()
{
    return gaming;
}

void Gamer::beginGame()
{
    gaming = true;
}

void Gamer::endGame()
{
    gaming = false;
}

bool Gamer::include(int number)
{
    for (int i = 0; i < MAX_NUMBER_OF_SHIPS; i++) {
        if (number == playerShips[i]) {
            return true;
        }
    }

    return false;
}

void Gamer::buildShip(int number)
{
    for (int i = 0; i < MAX_NUMBER_OF_SHIPS; i++) {
        if (number == playerShips[i]) {
            return;
        }
    }

    playerShips[realNumberOfShips] = number;
    realNumberOfShips++;

    Triangles[number].build();

    if (realNumberOfShips >= MAX_NUMBER_OF_SHIPS) {
        buildAll = true;
    }
}

void Gamer::killShip(int number)
{
    Triangles[number].kill();
}

void Gamer::failShot(int number)
{
    Triangles[number].fail();
}

void Gamer::cleanAll()
{
    for (int i = 0; i < MAX_NUMBER_OF_SHIPS; i++) {
        Triangles[i].clean();
    }
}

bool Gamer::wasKilled(int number)
{
    for (int i = 0; i < MAX_NUMBER_OF_SHIPS; i++) {
        if (number == playerShips[i]) {
            return true;
        }
    }
    return false;
}





