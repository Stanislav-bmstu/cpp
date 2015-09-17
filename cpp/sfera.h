#ifndef SFERA_H
#define SFERA_H

#include <QGLWidget>
#include <interface3dmodel.h>
#include <triangle.h>

class Sfera : public Interface3dModel {
    GLuint  IndexArray[80][3];    // декларируем массив индексов вершин
    Triangle TriangleArray[80];
    GLfloat** TextureArray;

public:
    GLfloat VertexArray[80][3][3];  // декларируем массив вершин
    Sfera();
    ~Sfera();
    void getVerTexArrays(); // определить массив вершин
    void getIndexArray();   // определить массив индексов вершин

    GLuint**  retIndexArray();
    GLfloat** retTextureArray();

    void build(int number);
    void kill(int number);
    void fail(int number);
    void clean(int number);

    Triangle* retTriangle();

    void draw();
};

#endif // SFERA_H
