#ifndef INTERFACE3DMODEL_H
#define INTERFACE3DMODEL_H

#include <QGLWidget> // подключаем класс QGLWidget

class Interface3dModel {
public:
    virtual void getVerTexArrays()      = 0;    // определить массив вершин
    virtual void getIndexArray()        = 0;    // определить массив индексов вершин
    //virtual GLfloat*** retVertexArray()  = 0;
    //virtual GLuint**  retIndexArray()   = 0;
    virtual void draw() = 0;
};

#endif // INTERFACE3DMODEL_H
