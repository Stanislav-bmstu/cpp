#include "gameplay.h"

Gameplay::Gameplay()
{
    start  = -1;
    finish = -1;

    oldplayer = 0;
    oldfinish = -1;
    fire = false;
}

Gameplay::~Gameplay()
{

}

void Gameplay::init(Sfera *asfera, Yadro *ayadro, Triangle *TriangleArray)
{
    sfera       = asfera;
    yadro       = ayadro;
    Triangles   = TriangleArray;
    //yadro     = ayadro;

    gamer[0].init(TriangleArray);
    gamer[1].init(TriangleArray);

    gamer[0].beginGame();
}

void Gameplay::game(int number)
{
    // Постройка кораблей
    if ( !(gamer[0].hasBuildAll() && gamer[1].hasBuildAll()) ) {
        building(number);
        return;
    }

    bool player = 0;
    if ( gamer[0].isGaming() ) {
        player = 0;
    } else {
        player = 1;
    }

    // Определяем старт запуска ракеты
    if ( gamer[player].include(number) && start == -1) {
        start = number;
        fire = false;
        return;
    }

    // Определяем цель ракеты
    if ( start != -1 ) {
        finish = number;
        yadro->shot(start, finish);
        oldfinish = finish;
        start  = -1;
        finish = -1;
        fire = true;
        oldplayer = player;
        gamer[player].endGame();
        gamer[!player].beginGame();
        return;
    }
}

void Gameplay::shot(int start, int finish)
{


}

void Gameplay::building(int number)
{
    if (gamer[0].isGaming() && number <  40 && !gamer[0].hasBuildAll()) {
        gamer[0].buildShip(number);
        if (gamer[0].hasBuildAll()) {
            gamer[0].endGame();
            gamer[1].beginGame();
        }
        return;
    }

    if (gamer[1].isGaming() && number >= 40 && !gamer[1].hasBuildAll()){
        gamer[1].buildShip(number);
        if (gamer[1].hasBuildAll()) {
            gamer[1].endGame();
            gamer[0].beginGame();
        }
        return;
    }
}

bool Gameplay::maybeFire()
{
    return fire;
}

bool Gameplay::selectStart()
{
    if (start != -1) {
        return true;
    }
    return false;
}

int Gameplay::returnStart()
{
    return start;
}

void Gameplay::proverka()
{
    bool shipKilled = false;
    shipKilled = gamer[!oldplayer].wasKilled(oldfinish);



    if ( oldfinish != -1 && shipKilled) {
        GLfloat x0 = sfera->VertexArray[oldfinish][0][0];
        GLfloat y0 = sfera->VertexArray[oldfinish][0][1];
        GLfloat z0 = sfera->VertexArray[oldfinish][0][2];

        GLfloat x1 = sfera->VertexArray[oldfinish][1][0];
        GLfloat y1 = sfera->VertexArray[oldfinish][1][1];
        GLfloat z1 = sfera->VertexArray[oldfinish][1][2];

        GLfloat x2 = sfera->VertexArray[oldfinish][2][0];
        GLfloat y2 = sfera->VertexArray[oldfinish][2][1];
        GLfloat z2 = sfera->VertexArray[oldfinish][2][2];

        for (int i = 0; i < 80; i++) {
            GLfloat x0temp = sfera->VertexArray[i][0][0];
            GLfloat y0temp = sfera->VertexArray[i][0][1];
            GLfloat z0temp = sfera->VertexArray[i][0][2];

            GLfloat x1temp = sfera->VertexArray[i][1][0];
            GLfloat y1temp = sfera->VertexArray[i][1][1];
            GLfloat z1temp = sfera->VertexArray[i][1][2];

            GLfloat x2temp = sfera->VertexArray[i][2][0];
            GLfloat y2temp = sfera->VertexArray[i][2][1];
            GLfloat z2temp = sfera->VertexArray[i][2][2];

            if (    (x0 == x0temp && y0 == y0temp && z0 == z0temp) ||
                    (x0 == x1temp && y0 == y1temp && z0 == z1temp) ||
                    (x0 == x2temp && y0 == y2temp && z0 == z2temp) ||

                    (x1 == x0temp && y1 == y0temp && z1 == z0temp) ||
                    (x1 == x1temp && y1 == y1temp && z1 == z1temp) ||
                    (x1 == x2temp && y1 == y2temp && z1 == z2temp) ||

                    (x2 == x0temp && y2 == y0temp && z2 == z0temp) ||
                    (x2 == x1temp && y2 == y1temp && z2 == z1temp) ||
                    (x2 == x2temp && y2 == y2temp && z2 == z2temp)   )
            {
                Triangles[i].fail();
            }
        }
    }

    if (gamer[!oldplayer].include(oldfinish)) {
        Triangles[oldfinish].kill();
    }
}
