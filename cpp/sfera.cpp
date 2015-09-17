#include "sfera.h"
#include "math.h"

Sfera::Sfera()
{
    TextureArray = new GLfloat* [240];
    for (int i = 0; i < 240; i++) {
        TextureArray[i] = new GLfloat[2];
    }

    bool player = 0;
    for (int i = 0; i < 80; i++) {
        TriangleArray[i].init(i, player, TextureArray);
        if ( i == 39) {
            player = 1;
        }
    }
}

Sfera::~Sfera()
{
    delete[] TextureArray;
}

void Sfera::getVerTexArrays() // определить массив вершин и текстурных координат
{
    const GLfloat pi=3.141593, k=pi/180; // глобальная переменная
    GLfloat R=1.0f; // радиус сферы
    //GLfloat alpha=pi/2;

    //GLfloat R=0.75; // радиус сферы

    // начальные значения для икосаэдра
    GLfloat a=4*R/sqrt(10+2*sqrt(5)); // сторона икосаэдра
    GLfloat alpha=acos((1-a*a/2/R/R)); // первый угол поворота по тэта
    // cos(alpha)=(1-a*a/2/R/R)
    GLfloat betha=alpha/2;

    //  VertexArray[треугольник][угол][координата]
    // Шапка
    for (int i = 0; i < 5; i++) {
        // 0 треугольник
        VertexArray[0+i*4][0][0] = 0;                               // 0 - угол X - координата
        VertexArray[0+i*4][0][1] = 0;                               // 0 - угол Y - координата
        VertexArray[0+i*4][0][2] = R;                               // 0 - угол Z - координата

        VertexArray[0+i*4][1][0] = R*sin(betha)*sin(((i+1)*72)*k);  // 1 - угол X - координата
        VertexArray[0+i*4][1][1] = R*sin(betha)*cos(((i+1)*72)*k);  // 1 - угол Y - координата
        VertexArray[0+i*4][1][2] = R*cos(betha);                    // 1 - угол Z - координата

        VertexArray[0+i*4][2][0] = R*sin(betha)*sin((i*72)*k);      // 2 - угол X - координата
        VertexArray[0+i*4][2][1] = R*sin(betha)*cos((i*72)*k);      // 2 - угол Y - координата
        VertexArray[0+i*4][2][2] = R*cos(betha);                    // 2 - угол Z - координата

        // 1 треугольник
        VertexArray[1+i*4][0][0] = R*sin(betha)*sin((i*72)*k);
        VertexArray[1+i*4][0][1] = R*sin(betha)*cos((i*72)*k);
        VertexArray[1+i*4][0][2] = R*cos(betha);

        VertexArray[1+i*4][1][0] = R*sin(alpha)*sin((36+i*72)*k);
        VertexArray[1+i*4][1][1] = R*sin(alpha)*cos((36+i*72)*k);
        VertexArray[1+i*4][1][2] = R*cos(alpha);

        VertexArray[1+i*4][2][0] = R*sin(alpha)*sin(i*72*k);
        VertexArray[1+i*4][2][1] = R*sin(alpha)*cos(i*72*k);
        VertexArray[1+i*4][2][2] = R*cos(alpha);

        // 2 треугольник
        VertexArray[2+i*4][0][0] = R*sin(alpha)*sin((36+i*72)*k);
        VertexArray[2+i*4][0][1] = R*sin(alpha)*cos((36+i*72)*k);
        VertexArray[2+i*4][0][2] = R*cos(alpha);

        VertexArray[2+i*4][1][0] = R*sin(betha)*sin((i*72)*k);
        VertexArray[2+i*4][1][1] = R*sin(betha)*cos((i*72)*k);
        VertexArray[2+i*4][1][2] = R*cos(betha);

        VertexArray[2+i*4][2][0] = R*sin(betha)*sin(((i+1)*72)*k);
        VertexArray[2+i*4][2][1] = R*sin(betha)*cos(((i+1)*72)*k);
        VertexArray[2+i*4][2][2] = R*cos(betha);

        // 3 треугольник
        VertexArray[3+i*4][0][0] = R*sin(betha)*sin(((i+1)*72)*k);
        VertexArray[3+i*4][0][1] = R*sin(betha)*cos(((i+1)*72)*k);
        VertexArray[3+i*4][0][2] = R*cos(betha);

        VertexArray[3+i*4][1][0] = R*sin(alpha)*sin(((i+1)*72)*k);
        VertexArray[3+i*4][1][1] = R*sin(alpha)*cos(((i+1)*72)*k);
        VertexArray[3+i*4][1][2] = R*cos(alpha);

        VertexArray[3+i*4][2][0] = R*sin(alpha)*sin((36+i*72)*k);
        VertexArray[3+i*4][2][1] = R*sin(alpha)*cos((36+i*72)*k);
        VertexArray[3+i*4][2][2] = R*cos(alpha);
    }

    // Цилиндр 1/2
    for (int i = 0; i < 5; i++) {
        // 20 треугольник
        VertexArray[20+i*8][0][0] = R*sin(alpha)*sin(i*72*k);
        VertexArray[20+i*8][0][1] = R*sin(alpha)*cos(i*72*k);
        VertexArray[20+i*8][0][2] = R*cos(alpha);

        VertexArray[20+i*8][1][0] = R*1*sin((18+i*72)*k);
        VertexArray[20+i*8][1][1] = R*1*cos((18+i*72)*k);
        VertexArray[20+i*8][1][2] = 0;

        VertexArray[20+i*8][2][0] = R*1*sin((-18+i*72)*k);
        VertexArray[20+i*8][2][1] = R*1*cos((-18+i*72)*k);
        VertexArray[20+i*8][2][2] = 0;

        // 21 треугольник
        VertexArray[21+i*8][0][0] = R*1*sin((-18+i*72)*k);
        VertexArray[21+i*8][0][1] = R*1*cos((-18+i*72)*k);
        VertexArray[21+i*8][0][2] = 0;

        VertexArray[21+i*8][1][0] = R*sin(pi-alpha)*sin((i*72)*k);
        VertexArray[21+i*8][1][1] = R*sin(pi-alpha)*cos((i*72)*k);
        VertexArray[21+i*8][1][2] = R*cos(pi-alpha);

        VertexArray[21+i*8][2][0] = R*sin(pi-alpha)*sin((-36+i*72)*k);
        VertexArray[21+i*8][2][1] = R*sin(pi-alpha)*cos((-36+i*72)*k);
        VertexArray[21+i*8][2][2] = R*cos(pi-alpha);

        // 22 треугольник
        VertexArray[22+i*8][0][0] = R*sin(pi-alpha)*sin((i*72)*k);
        VertexArray[22+i*8][0][1] = R*sin(pi-alpha)*cos((i*72)*k);
        VertexArray[22+i*8][0][2] = R*cos(pi-alpha);

        VertexArray[22+i*8][1][0] = R*1*sin((-18+i*72)*k);
        VertexArray[22+i*8][1][1] = R*1*cos((-18+i*72)*k);
        VertexArray[22+i*8][1][2] = 0;

        VertexArray[22+i*8][2][0] = R*1*sin((18+i*72)*k);
        VertexArray[22+i*8][2][1] = R*1*cos((18+i*72)*k);
        VertexArray[22+i*8][2][2] = 0;

        // 23 треугольник
        VertexArray[23+i*8][0][0] = R*1*sin((18+i*72)*k);
        VertexArray[23+i*8][0][1] = R*1*cos((18+i*72)*k);
        VertexArray[23+i*8][0][2] = 0;

        VertexArray[23+i*8][1][0] = R*sin(pi-alpha)*sin((36+i*72)*k);
        VertexArray[23+i*8][1][1] = R*sin(pi-alpha)*cos((36+i*72)*k);
        VertexArray[23+i*8][1][2] = R*cos(pi-alpha);

        VertexArray[23+i*8][2][0] = R*sin(pi-alpha)*sin((i*72)*k);
        VertexArray[23+i*8][2][1] = R*sin(pi-alpha)*cos((i*72)*k);
        VertexArray[23+i*8][2][2] = R*cos(pi-alpha);
    }

    // Цилиндр 2/2
    for (int i = 0; i < 5; i++) {
        // 24 треугольник
        VertexArray[24+i*8][0][0] = R*1*sin((18+i*72)*k);
        VertexArray[24+i*8][0][1] = R*1*cos((18+i*72)*k);
        VertexArray[24+i*8][0][2] = 0;

        VertexArray[24+i*8][1][0] = R*sin(alpha)*sin(i*72*k);
        VertexArray[24+i*8][1][1] = R*sin(alpha)*cos(i*72*k);
        VertexArray[24+i*8][1][2] = R*cos(alpha);

        VertexArray[24+i*8][2][0] = R*sin(alpha)*sin((36+i*72)*k);
        VertexArray[24+i*8][2][1] = R*sin(alpha)*cos((36+i*72)*k);
        VertexArray[24+i*8][2][2] = R*cos(alpha);

        // 25 треугольник
        VertexArray[25+i*8][0][0] = R*sin(alpha)*sin((36+i*72)*k);
        VertexArray[25+i*8][0][1] = R*sin(alpha)*cos((36+i*72)*k);
        VertexArray[25+i*8][0][2] = R*cos(alpha);

        VertexArray[25+i*8][1][0] = R*1*sin((54+i*72)*k);
        VertexArray[25+i*8][1][1] = R*1*cos((54+i*72)*k);
        VertexArray[25+i*8][1][2] = 0;

        VertexArray[25+i*8][2][0] = R*1*sin((18+i*72)*k);
        VertexArray[25+i*8][2][1] = R*1*cos((18+i*72)*k);
        VertexArray[25+i*8][2][2] = 0;

        // 26 треугольник
        VertexArray[26+i*8][0][0] = R*1*sin((54+i*72)*k);
        VertexArray[26+i*8][0][1] = R*1*cos((54+i*72)*k);
        VertexArray[26+i*8][0][2] = 0;

        VertexArray[26+i*8][1][0] = R*sin(alpha)*sin((36+i*72)*k);
        VertexArray[26+i*8][1][1] = R*sin(alpha)*cos((36+i*72)*k);
        VertexArray[26+i*8][1][2] = R*cos(alpha);

        VertexArray[26+i*8][2][0] = R*sin(alpha)*sin(((1+i)*72)*k);
        VertexArray[26+i*8][2][1] = R*sin(alpha)*cos(((1+i)*72)*k);
        VertexArray[26+i*8][2][2] = R*cos(alpha);

        // 27 треугольник
        VertexArray[27+i*8][0][0] = R*sin(pi-alpha)*sin((36+i*72)*k);
        VertexArray[27+i*8][0][1] = R*sin(pi-alpha)*cos((36+i*72)*k);
        VertexArray[27+i*8][0][2] = R*cos(pi-alpha);

        VertexArray[27+i*8][1][0] = R*1*sin((18+i*72)*k);
        VertexArray[27+i*8][1][1] = R*1*cos((18+i*72)*k);
        VertexArray[27+i*8][1][2] = 0;

        VertexArray[27+i*8][2][0] = R*1*sin((54+i*72)*k);
        VertexArray[27+i*8][2][1] = R*1*cos((54+i*72)*k);
        VertexArray[27+i*8][2][2] = 0;
    }

    // Дно
    for (int i = 0; i < 5; i++) {
        // 60 треугольник
        VertexArray[60+i*4][0][0] = R*sin(pi-betha)*sin((-36+i*72)*k);
        VertexArray[60+i*4][0][1] = R*sin(pi-betha)*cos((-36+i*72)*k);
        VertexArray[60+i*4][0][2] = R*cos(pi-betha);

        VertexArray[60+i*4][1][0] = R*sin(pi-alpha)*sin((-36+i*72)*k);
        VertexArray[60+i*4][1][1] = R*sin(pi-alpha)*cos((-36+i*72)*k);
        VertexArray[60+i*4][1][2] = R*cos(pi-alpha);

        VertexArray[60+i*4][2][0] = R*sin(pi-alpha)*sin((i*72)*k);
        VertexArray[60+i*4][2][1] = R*sin(pi-alpha)*cos((i*72)*k);
        VertexArray[60+i*4][2][2] = R*cos(pi-alpha);

        // 61 треугольник
        VertexArray[61+i*4][0][0] = R*sin(pi-alpha)*sin((i*72)*k);
        VertexArray[61+i*4][0][1] = R*sin(pi-alpha)*cos((i*72)*k);
        VertexArray[61+i*4][0][2] = R*cos(pi-alpha);

        VertexArray[61+i*4][1][0] = R*sin(pi-betha)*sin((36+i*72)*k);
        VertexArray[61+i*4][1][1] = R*sin(pi-betha)*cos((36+i*72)*k);
        VertexArray[61+i*4][1][2] = R*cos(pi-betha);

        VertexArray[61+i*4][2][0] = R*sin(pi-betha)*sin((-36+i*72)*k);
        VertexArray[61+i*4][2][1] = R*sin(pi-betha)*cos((-36+i*72)*k);
        VertexArray[61+i*4][2][2] = R*cos(pi-betha);

        // 62 треугольник
        VertexArray[62+i*4][0][0] = R*sin(pi-betha)*sin((36+i*72)*k);
        VertexArray[62+i*4][0][1] = R*sin(pi-betha)*cos((36+i*72)*k);
        VertexArray[62+i*4][0][2] = R*cos(pi-betha);

        VertexArray[62+i*4][1][0] = R*sin(pi-alpha)*sin((i*72)*k);
        VertexArray[62+i*4][1][1] = R*sin(pi-alpha)*cos((i*72)*k);
        VertexArray[62+i*4][1][2] = R*cos(pi-alpha);

        VertexArray[62+i*4][2][0] = R*sin(pi-alpha)*sin((36+i*72)*k);
        VertexArray[62+i*4][2][1] = R*sin(pi-alpha)*cos((36+i*72)*k);
        VertexArray[62+i*4][2][2] = R*cos(pi-alpha);

        // 63 треугольник
        VertexArray[63+i*4][0][0] = 0;
        VertexArray[63+i*4][0][1] = 0;
        VertexArray[63+i*4][0][2] = -R;

        VertexArray[63+i*4][1][0] = R*sin(pi-betha)*sin((-36+i*72)*k);
        VertexArray[63+i*4][1][1] = R*sin(pi-betha)*cos((-36+i*72)*k);
        VertexArray[63+i*4][1][2] = R*cos(pi-betha);

        VertexArray[63+i*4][2][0] = R*sin(pi-betha)*sin((36+i*72)*k);
        VertexArray[63+i*4][2][1] = R*sin(pi-betha)*cos((36+i*72)*k);
        VertexArray[63+i*4][2][2] = R*cos(pi-betha);
    }

    for (int i = 0; i < 120; i+=3) {
        TextureArray[i+0][0]=0.0f;
        TextureArray[i+0][1]=0.0f;
        TextureArray[i+1][0]=0.25f;
        TextureArray[i+1][1]=0.5f;
        TextureArray[i+2][0]=0.5f;
        TextureArray[i+2][1]=0.0f;

    }
    for (int i = 120; i < 240; i+=3) {
        TextureArray[i+0][0]=0.5f;
        TextureArray[i+0][1]=1.0f;
        TextureArray[i+1][0]=0.25f;
        TextureArray[i+1][1]=0.5f;
        TextureArray[i+2][0]=0.0f;
        TextureArray[i+2][1]=1.0f;
    }
}

void Sfera::getIndexArray() // определить массив индексов
{
    for (int i = 0; i < 80; i++) {
        IndexArray[i][0] = i*3 + 0;
        IndexArray[i][1] = i*3 + 1;
        IndexArray[i][2] = i*3 + 2;
    }
}

GLuint** Sfera::retIndexArray()
{
    GLuint** result = (GLuint**)IndexArray;
    return result;
}


GLfloat** Sfera::retTextureArray()
{
    GLfloat** result = (GLfloat**)TextureArray;
    return result;
}

void Sfera::build(int number)
{
    TriangleArray[number].build();
}

void Sfera::kill(int number)
{
    TriangleArray[number].kill();
}

void Sfera::fail(int number)
{
    TriangleArray[number].fail();
}

void Sfera::clean(int number)
{
    TriangleArray[number].clean();
}

Triangle *Sfera::retTriangle()
{
    return TriangleArray;
}

void Sfera::draw() // построить фигуру
{
    GLfloat TextureArray2[240][2];

    for (int i = 0; i < 240; i++) {
        for (int j = 0; j < 2; j++) {
            TextureArray2[i][j] = TextureArray[i][j];
        }
    }

    glVertexPointer(3, GL_FLOAT, 0, VertexArray);
    // указываем, откуда нужно извлечь данные о массиве текстурных координат
    glTexCoordPointer(2, GL_FLOAT, 0, TextureArray2);
    // используя массивы вершин и индексов, строим поверхности
    glDrawElements(GL_TRIANGLES, 240, GL_UNSIGNED_INT, IndexArray);
}
