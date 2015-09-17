#include "triangle.h"

Triangle::Triangle()
{
    number  = -1;
    enabled = false;
    ship    = false;
    TextureArray = NULL;

    playerN1 = false;
    playerN2 = false;
}

void Triangle::init(int numberTr, bool player, GLfloat** Texture)
{
    number  = numberTr;
    enabled = true;
    ship    = false;
    TextureArray = Texture;

    if ( player == 0 ) {
        playerN1 = true;
        playerN2 = false;
    } else {
        playerN1 = false;
        playerN2 = true;
    }
    this->clean();
}

Triangle::~Triangle()
{

}

bool Triangle::isPlayerN1()
{
    return playerN1;
}

bool Triangle::isPlayerN2()
{
    return playerN2;
}

bool Triangle::isShip()
{
    return ship;
}

int Triangle::isNumber()
{
    return number;
}

void Triangle::build()
{
    ship = true;
    if ( isPlayerN1() ) {
        TextureArray[number*3+0][0]=0.5f;
        TextureArray[number*3+0][1]=0.0f;
        TextureArray[number*3+1][0]=0.75f;
        TextureArray[number*3+1][1]=0.5f;
        TextureArray[number*3+2][0]=1.0f;
        TextureArray[number*3+2][1]=0.0f;
    } else {
        TextureArray[number*3+0][0]=1.0f;
        TextureArray[number*3+0][1]=1.0f;
        TextureArray[number*3+1][0]=0.75f;
        TextureArray[number*3+1][1]=0.5f;
        TextureArray[number*3+2][0]=0.5f;
        TextureArray[number*3+2][1]=1.0f;
    }
}

void Triangle::kill()
{
    enabled = false;

    if ( isPlayerN1() ) {
        TextureArray[number*3+0][0]=1.0f;
        TextureArray[number*3+0][1]=0.0f;
        TextureArray[number*3+1][0]=1.0f;
        TextureArray[number*3+1][1]=0.5f;
        TextureArray[number*3+2][0]=0.75f;
        TextureArray[number*3+2][1]=0.5f;
    } else {
        TextureArray[number*3+0][0]=1.0f;
        TextureArray[number*3+0][1]=0.5f;
        TextureArray[number*3+1][0]=1.0f;
        TextureArray[number*3+1][1]=1.0f;
        TextureArray[number*3+2][0]=0.75f;
        TextureArray[number*3+2][1]=0.5f;
    }
}

void Triangle::fail()
{
    enabled = false;
    if ( isPlayerN1() ) {
        TextureArray[number*3+0][0]=0.75f;
        TextureArray[number*3+0][1]=0.5f;
        TextureArray[number*3+1][0]=0.5f;
        TextureArray[number*3+1][1]=0.0f;
        TextureArray[number*3+2][0]=0.25f;
        TextureArray[number*3+2][1]=0.5f;
    } else {
        TextureArray[number*3+0][0]=0.25f;
        TextureArray[number*3+0][1]=0.5f;
        TextureArray[number*3+1][0]=0.5f;
        TextureArray[number*3+1][1]=1.0f;
        TextureArray[number*3+2][0]=0.75f;
        TextureArray[number*3+2][1]=0.5f;
    }
}

void Triangle::clean()
{
    enabled = true;
    ship    = false;

    if ( isPlayerN1() ) {
        TextureArray[number*3+0][0]=0.0f;
        TextureArray[number*3+0][1]=0.0f;
        TextureArray[number*3+1][0]=0.25f;
        TextureArray[number*3+1][1]=0.5f;
        TextureArray[number*3+2][0]=0.5f;
        TextureArray[number*3+2][1]=0.0f;
    } else {
        TextureArray[number*3+0][0]=0.5f;
        TextureArray[number*3+0][1]=1.0f;
        TextureArray[number*3+1][0]=0.25f;
        TextureArray[number*3+1][1]=0.5f;
        TextureArray[number*3+2][0]=0.0f;
        TextureArray[number*3+2][1]=1.0f;
    }
}



