#include "yadro.h"
#include "math.h"

Yadro::Yadro()
{
    pli    = 0;
    plifinish = 0;
    shag;
    signTh = 1;
    signPh = 1;
    delta1 = 0.0f;
    delta2 = 0.0f;
    doletelo = 0;
}

void Yadro::getVerTexArrays() // определить массив вершин и текстурных координат
{
    const GLfloat pi=3.141593, k=pi/180; // глобальная переменная
    GLfloat R=1.2f; // радиус сферы
    GLfloat alpha=pi/2;
    GLfloat r = 0.1f; // радиус сферы


    // вычисляем точки
    //0 точка
    VertexArrayYadro[0][0]=0.4+0.0f*r; // x
    VertexArrayYadro[0][1]=0.4+0.0f*r; // y
    VertexArrayYadro[0][2]=0.4+R*r;    // z
    //
    //1 точка
    VertexArrayYadro[1][1]=0.4+R*sin(alpha)*sin(0)*r;
    VertexArrayYadro[1][0]=0.4+R*sin(alpha)*cos(0)*r;
    VertexArrayYadro[1][2]=0.4+R*cos(alpha)*r;
    //
    //2 точка
    VertexArrayYadro[2][1]=0.4+R*sin(alpha)*sin(pi/2)*r;
    VertexArrayYadro[2][0]=0.4+R*sin(alpha)*cos(pi/2)*r;
    VertexArrayYadro[2][2]=0.4+R*    cos(alpha)*r;
    //
    //3 точка
    VertexArrayYadro[3][1]=0.4+R*sin(alpha)*sin(pi)*r;
    VertexArrayYadro[3][0]=0.4+R*sin(alpha)*cos(pi)*r;
    VertexArrayYadro[3][2]=0.4+R*    cos(alpha)*r;
    //
    //4 точка
    VertexArrayYadro[4][1]=0.4+R*sin(alpha)*sin(3*pi/2)*r;
    VertexArrayYadro[4][0]=0.4+R*sin(alpha)*cos(3*pi/2)*r;
    VertexArrayYadro[4][2]=0.4+R*cos(alpha)*r;
    //
    //5 точка
    VertexArrayYadro[5][1]=0.4+0.0f*r;
    VertexArrayYadro[5][0]=0.4+0.0f*r;
    VertexArrayYadro[5][2]=0.4-R*r;

    TextureArray[0][0]=0.5f*r; // x (s)
    TextureArray[0][1]=1.0f*r; // y (t)
    TextureArray[1][0]=1.0f*r;
    TextureArray[1][1]=0.0f*r;
    TextureArray[2][0]=0.0f*r;
    TextureArray[2][1]=0.0f*r;
    TextureArray[3][0]=1.0f*r;
    TextureArray[3][1]=0.0f*r;
    TextureArray[4][0]=0.0f*r;
    TextureArray[4][1]=0.0f*r;
    TextureArray[5][0]=0.5f*r;
    TextureArray[5][1]=1.0f*r;
}

void Yadro::getStartVerTexArrays(GLfloat sferaV[80][3][3], int start)
{
    const GLfloat pi=3.141593, k=pi/180;

    GLfloat x21 = sferaV[start][0][0]; GLfloat x22 = sferaV[start][1][0];  GLfloat x23 = sferaV[start][2][0];
    GLfloat y21 = sferaV[start][0][1]; GLfloat y22 = sferaV[start][1][1];  GLfloat y23 = sferaV[start][2][1];
    GLfloat z21 = sferaV[start][0][2]; GLfloat z22 = sferaV[start][1][2];  GLfloat z23 = sferaV[start][2][2];

    GLfloat x2 = (x21+x22+x23)/3;
    GLfloat y2 = (y21+y22+y23)/3;
    GLfloat z2 = (z21+z22+z23)/3;

    GLfloat r2      = sqrt(x2*x2 + y2*y2 + z2*z2);
    GLfloat theta2  = acos(z2/r2);
    GLfloat phi2    = atan2(y2,x2);


    for (int i = 0; i < 6; i++) {

        GLfloat x1 = VertexArrayYadro[i][0];
        GLfloat y1 = VertexArrayYadro[i][1];
        GLfloat z1 = VertexArrayYadro[i][2];

        GLfloat r1 = sqrt(x1*x1 + y1*y1 + z1*z1);
        GLfloat theta1 = acos(z1/r1);
        GLfloat phi1 = atan2(y1,x1);

        if (delta2 == 0.0f) {
            // Установка начальных параметров запуска
            delta2 = 1.0f;
            shag   = 2;
            deltaR = 0.15f;

            deltaTh = fabs(theta2 - theta1);
            deltaPh = fabs( phi2  -  phi1 );
            deltaR  = fabs(  r2   -   r1  );

            deltaTh = deltaTh / (GLfloat)shag;
            deltaPh = deltaPh / (GLfloat)shag;

            if ( theta1 < theta2) {
                signTh  = 1;
            } else {
                signTh  = 0;
            }

            if (  phi1  <  phi2 ) {
                signPh  = 1;
            } else {
                signPh  = 0;
            }
        }

        if ( signTh  == 1 ) {
            theta1+=deltaTh;
        } else {
            theta1-=deltaTh;
        }

        if ( signPh  == 1 ) {
            phi1+=deltaPh;
        } else {
            phi1-=deltaPh;
        }

        r1+= deltaR;

        if (shag > 0) {
            VertexArrayYadro[i][0]=r1*sin(theta1)*cos(phi1);
            VertexArrayYadro[i][1]=r1*sin(theta1)*sin(phi1);
            VertexArrayYadro[i][2]=r1*cos(theta1);
            int h = 43;
            if ( i == 5 ) {
                shag--;
            }
        }
        if (shag == 0 && pli < 80) {
            //delta2 = 0.0f;
            //sfera.kill(pli+plifinish);
            //pli+=plifinish;
        }
    }
}

void Yadro::shot(int start, int finish)
{
    pli         = start;
    plifinish   = finish - start;
}

void Yadro::getIndexArray() // определить массив индексов
{
    // 0 треугольник
    IndexArrayYadro[0][0]=0; // индекс (номер) 1-ой вершины
    IndexArrayYadro[0][1]=2; // индекс (номер) 2-ой вершины
    IndexArrayYadro[0][2]=1; // индекс (номер) 3-ей вершины

    // 1 треугольник
    IndexArrayYadro[1][0]=0;
    IndexArrayYadro[1][1]=3;
    IndexArrayYadro[1][2]=2;

    // 2 треугольник
    IndexArrayYadro[2][0]=0;
    IndexArrayYadro[2][1]=4;
    IndexArrayYadro[2][2]=3;

    // 3 треугольник
    IndexArrayYadro[3][0]=0;
    IndexArrayYadro[3][1]=1;
    IndexArrayYadro[3][2]=4;

    // 4 треугольник
    IndexArrayYadro[4][0]=5;
    IndexArrayYadro[4][1]=1;
    IndexArrayYadro[4][2]=2;

    // 5 треугольник
    IndexArrayYadro[5][0]=5;
    IndexArrayYadro[5][1]=2;
    IndexArrayYadro[5][2]=3;

    // 6 треугольник
    IndexArrayYadro[6][0]=5;
    IndexArrayYadro[6][1]=3;
    IndexArrayYadro[6][2]=4;

    // 7 треугольник
    IndexArrayYadro[7][0]=5;
    IndexArrayYadro[7][1]=4;
    IndexArrayYadro[7][2]=1;
}

void Yadro::draw()
{
    // указываем, откуда нужно извлечь данные о массиве вершин
    glVertexPointer(3, GL_FLOAT, 0, VertexArrayYadro);
    // указываем, откуда нужно извлечь данные о массиве текстурных координат
    glTexCoordPointer(2, GL_FLOAT, 0, TextureArray);
    // используя массивы вершин и индексов, строим поверхности
    glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, IndexArrayYadro);
}

void Yadro::fly(GLfloat sferaV[80][3][3]/*, int flag*/, Sfera &sfera)
{
    const GLfloat pi=3.141593, k=pi/180;


    GLfloat x21 = sferaV[pli+plifinish][0][0]; GLfloat x22 = sferaV[pli+plifinish][1][0];  GLfloat x23 = sferaV[pli+plifinish][2][0];
    GLfloat y21 = sferaV[pli+plifinish][0][1]; GLfloat y22 = sferaV[pli+plifinish][1][1];  GLfloat y23 = sferaV[pli+plifinish][2][1];
    GLfloat z21 = sferaV[pli+plifinish][0][2]; GLfloat z22 = sferaV[pli+plifinish][1][2];  GLfloat z23 = sferaV[pli+plifinish][2][2];

    GLfloat x2 = (x21+x22+x23)/3;
    GLfloat y2 = (y21+y22+y23)/3;
    GLfloat z2 = (z21+z22+z23)/3;

    GLfloat r2      = sqrt(x2*x2 + y2*y2 + z2*z2);
    GLfloat theta2  = acos(z2/r2);
    GLfloat phi2    = atan2(y2,x2);


    for (int i = 0; i < 6; i++) {
        // Расчеты координат движущегося ядра
        GLfloat x1 = VertexArrayYadro[i][0];
        GLfloat y1 = VertexArrayYadro[i][1];
        GLfloat z1 = VertexArrayYadro[i][2];

        GLfloat r1 = sqrt(x1*x1 + y1*y1 + z1*z1);
        GLfloat theta1 = acos(z1/r1);
        GLfloat phi1 = atan2(y1,x1);

        if (delta1 == 0.0f) {
            // установка начальных параметров запуска
            delta1 = 1.0f;
            shag   = 50;
            deltaR = 0.05f;
            deltaTh = fabs(theta2 - theta1);
            deltaPh = fabs( phi2  -  phi1 );
            deltaTh = deltaTh / (GLfloat)shag;
            deltaPh = deltaPh / (GLfloat)shag;
            if ( theta1 < theta2) {
                signTh  = 1;
            } else {
                signTh  = 0;
            }

            if (  phi1  <  phi2 ) {
                signPh  = 1;
            } else {
                signPh  = 0;
            }
        }

        // По флагам усанавливаем стороны вращения
        if ( signTh  == 1 ) {
            theta1+=deltaTh;
        } else {
            theta1-=deltaTh;
        }

        if ( signPh  == 1 ) {
            phi1+=deltaPh;
        } else {
            phi1-=deltaPh;
        }

        if ( shag > 25) {
            r1+= deltaR;
        } else {
            r1-= deltaR;
        }


        if (shag > 0) {
            VertexArrayYadro[i][0]=r1*sin(theta1)*cos(phi1);
            VertexArrayYadro[i][1]=r1*sin(theta1)*sin(phi1);
            VertexArrayYadro[i][2]=r1*cos(theta1);
            int h = 43;
            if ( i == 5 ) {
                shag--;
            }
            doletelo = 0;
        }
        if (shag == 0 && pli < 80) {
            // Признак сработал. Ракета прилетела
            sfera.fail(pli+plifinish);
            doletelo = 1;
        }
    }
}
