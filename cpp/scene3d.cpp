#include <QtGui>      // подключаем модуль QtGui
#include <math.h>     // подключаем математическую библиотеку
#include <scene3d.h>  // подключаем заголовочный файл scene3D.h
#include "glext.h"    // подключаем заголовочный файл glext.h
#include <GL/glu.h>
//#include <GL/gl.h>
//#include <GL/glx.h>
//#include <glu.h>


///* в версии 1.2 */
//#ifndef GL_CLAMP_TO_EDGE
//#define GL_CLAMP_TO_EDGE 0x812F
//#endif

///* в версии 1.3 */
//#ifndef GL_MULTISAMPLE
//#define GL_MULTISAMPLE  0x809D
//#endif

const GLfloat pi=3.141593, k=pi/180; // глобальная переменная

GLint viewport[4]; // декларируем матрицу поля просмотра

GLfloat VertexArray[6][3];  // декларируем массив вершин
GLfloat TextureArray[6][2]; // декларируем массив текстурных координат
GLuint IndexArray[8][3];    // декларируем массив индексов вершин
GLuint textureID[2];        // декларируем массив текстурных объектов (id текстур)

GLint signs[2]={1, 1}; // массив знаков +1 или -1 (понадобятся при трансляции)
bool motionParameters[2]={1, 1}; // массив параметров, определяющих движение
int textureParameters[2]={0, 1}; // массив индексов массива текстурных ID

// конструктор класса Scene3D:
Scene3D::Scene3D(QWidget* parent/*= 0*/) : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    // начальные значения
    xRot1=-90.0f;   yRot1=0.0f; zRot1=0.0f;
    xRot2=-90.0f;   yRot2=0.0f; zRot2=0.0f;

    xTra1=0.0f;     yTra1=0.0f; zTra1=0.0f;
    xTra2=0.0f;     yTra2=0.0f; zTra2=0.0f;

    nSca=1;

    timer = new QTimer(this); // создаём таймер
    // связываем сигналы и слоты:
    connect(timer, SIGNAL(timeout()), this, SLOT(change()));

    Triangle* temp = sfera.retTriangle();
    gameplay.init(&sfera, &yadro, temp);
    timer->start(10); // запускаем таймер
    //timer->stop();

    // синхронизация кадров с дисплеем:
    QGLFormat frmt; // создать формат по умолчанию
    frmt.setSwapInterval(1); // установить синхронизацию в формат
    setFormat(frmt); // установить формат в контекст
}

Scene3D::~Scene3D() // деструктор
{

}

void Scene3D::initializeGL() // инициализация
{
    qglClearColor(Qt::black);   // цвет для очистки буфера изображения - будет просто фон окна
    glEnable(GL_DEPTH_TEST);    // устанавливаем режим проверки глубины пикселей
    glEnable(GL_CULL_FACE);     // устанавливаем режим, когда строятся только внешние поверхности
    glEnable(GL_TEXTURE_2D);    // установливаем режим двумерных текстур
    glEnable(GL_MULTISAMPLE);   // включаем мультивыборку

    sfera.getVerTexArrays();
    sfera.getIndexArray();

    yadro.getVerTexArrays();
    yadro.getIndexArray();

    genTextures();     // создать текстуры

    glEnableClientState(GL_VERTEX_ARRAY);           // активизируем массив вершин
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);    // активизируем массив текстурных координат
}

void Scene3D::resizeGL(int nWidth, int nHeight) // окно виджета
{
    glMatrixMode(GL_PROJECTION);    // устанавливаем текущей проекционную матрицу
    glLoadIdentity();               // присваиваем проекционной матрице единичную матрицу

    // отношение высоты окна виджета к его ширине
    ratio=(GLfloat)nHeight/(GLfloat)nWidth;

    // мировое окно
    if (nWidth>=nHeight)
        // параметры видимости ортогональной проекции:
        glOrtho(-2.0/ratio, 2.0/ratio, -2.0, 2.0, -10.0, 10.0);
    else
        glOrtho(-2.0, 2.0, -2.0*ratio, 2.0*ratio, -10.0, 10.0);

    // поле просмотра
    glViewport(0, 0, (GLint)nWidth, (GLint)nHeight);

    // извлекаем матрицу поля просмотра в viewport
    glGetIntegerv(GL_VIEWPORT, viewport);
}

void Scene3D::paintGL() // рисование
{
    // очищаем буферы изображения и глубины
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // устанавливаем матрицу моделирования текущей
    glMatrixMode(GL_MODELVIEW);
    // загружаем единичную матрицу в матрицу моделирования
    glLoadIdentity();


    glPushMatrix();                             // помещаем матрицу моделирования в стек матриц
        glScalef(nSca, nSca, nSca);             // масштабирование
        glTranslatef(xTra1, zTra1, yTra1);      // трансляция
        glRotatef(xRot1, 1.0f, 0.0f, 0.0f);     // поворот вокруг оси X
        glRotatef(yRot1, 0.0f, 1.0f, 0.0f);     // поворот вокруг оси Y
        glRotatef(zRot1, 0.0f, 0.0f, 1.0f);     // поворот вокруг оси Z
        glBindTexture(GL_TEXTURE_2D, textureID[textureParameters[1]]);  // выбираем текстуру для наложения:
        sfera.draw();                           // нарисовать фигуру
    glPopMatrix();                              // извлекаем матрицу моделирования из стека матриц

    glPushMatrix();                             // помещаем матрицу моделирования в стек матриц
        glScalef(nSca, nSca, nSca);             // масштабирование
        glTranslatef(xTra2, zTra2, yTra2);      // трансляция
        glRotatef(xRot2, 1.0f, 0.0f, 0.0f);     // поворот вокруг оси X
        glRotatef(yRot2, 0.0f, 1.0f, 0.0f);     // поворот вокруг оси Y
        glRotatef(zRot2, 0.0f, 0.0f, 1.0f);     // поворот вокруг оси Z
        glBindTexture(GL_TEXTURE_2D, textureID[textureParameters[0]]);// выбираем текстуру для наложения:
        yadro.draw();
    glPopMatrix();                              // извлекаем матрицу моделирования из стека матриц
}

void Scene3D::genTextures() // создаём текстуры
{
    // создаём, связываем, загружаем, возвращаем уникальный номер:
    textureID[0]=bindTexture(QPixmap(QString("../textures/picture1.jpg")), GL_TEXTURE_2D);
    // далее параметры текстурного объекта    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);    // при фильтрации игнорируются тексели, выходящие за границу текстуры для s координаты
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);    // при фильтрации игнорируются тексели, выходящие за границу текстуры для t координаты
    // glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);          // цвет текселя полностью замещает цвет фрагмента фигуры


    // создаём, связываем, загружаем, возвращаем уникальный номер:
    textureID[1]=bindTexture(QPixmap(QString("textures/picture2.jpg")), GL_TEXTURE_2D);
    // далее параметры текстурного объекта
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);    // при фильтрации игнорируются тексели, выходящие за границу текстуры для s координаты
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);    // при фильтрации игнорируются тексели, выходящие за границу текстуры для t координаты
    // glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);          // цвет текселя полностью замещает цвет фрагмента фигуры
}

void Scene3D::selectFigures(QPoint mp) // выбрать фигуру
{
    GLuint selectBuffer[4];             // буфер выбора (буфер совпадений)
    GLint hits;                         // счетчик соответствий
    glSelectBuffer(4, selectBuffer);    // использовать указанный буфер выбора

    glMatrixMode(GL_PROJECTION);        // матрица проекции стала активной
    glPushMatrix();                     // поместить текущую матрицу в стек матриц
    glRenderMode(GL_SELECT);            // переход в режим выбора
    glLoadIdentity();                   // загрузить единичную матрицу

    // новый объём под указателем мыши
    gluPickMatrix((GLdouble)mp.x(), (GLdouble)(viewport[3]-mp.y()), 1.0, 1.0, viewport);
    // мировое окно
    if (width()>=height())
        // параметры видимости ортогональной проекции:
        glOrtho(-2.0/ratio, 2.0/ratio, -2.0, 2.0, -10.0, 10.0);
    else
        glOrtho(-2.0, 2.0, -2.0*ratio, 2.0*ratio, -10.0, 10.0);

    glMatrixMode(GL_MODELVIEW); // модельно-видовая матрица стала активной
    glLoadIdentity();           // загружается единичная матрица моделирования

    glInitNames(); // инициализируется и очищается стек имён
    glPushName(0); // в стек имён помещается значение 0
    // (обязательно должен храниться хотя бы один элемент)

    glPushMatrix();
        glScalef(nSca, nSca, nSca);          // масштабирование
        glTranslatef(xTra1, zTra1, yTra1);   // трансляция
        glRotatef(xRot1, 1.0f, 0.0f, 0.0f);  // поворот вокруг оси X
        glRotatef(yRot1, 0.0f, 1.0f, 0.0f);  // поворот вокруг оси Y
        glRotatef(zRot1, 0.0f, 0.0f, 1.0f);  // поворот вокруг оси Z
        glBindTexture(GL_TEXTURE_2D, textureID[textureParameters[1]]);   // выбираем текстуру для наложения:
        for (int i = 0; i < 80; ++i) {
            glLoadName(i);
            glBegin(GL_TRIANGLES);
                for (int j = 0; j < 3; ++j) {
                    glVertex3f( sfera.VertexArray[i][j][0],
                                sfera.VertexArray[i][j][1],
                                sfera.VertexArray[i][j][2]  );
                }
            glEnd();
        }
    glPopMatrix(); // извлечь матрицу моделирования из стека матриц    

    // число совпадений и переход в режим рисования
    hits=glRenderMode(GL_RENDER);

    if (hits > 0)
    {
        int figureName=selectBuffer[3]; // имя фигуры
        gameplay.game(figureName);
        if ( gameplay.maybeFire() )
        {
            timer->start();
        }

        //sfera.game(figureName);
    }

    glMatrixMode(GL_PROJECTION);    // матрица проекции стала активной
    glPopMatrix();                  // извлечь матрицу из стека матриц
    updateGL();
}

// слот - изменение углов поворота и величины трансляции
void Scene3D::change()
{
    if (gameplay.selectStart()) {
        yadro.getStartVerTexArrays(sfera.VertexArray, gameplay.returnStart());
    }

    if (gameplay.maybeFire()) {
        yadro.fly(sfera.VertexArray, sfera);
    }

    if (!gameplay.selectStart() && yadro.doletelo == 1) {
        yadro.getVerTexArrays();
        yadro.doletelo = 0;
        gameplay.fire  = 0;
        yadro.delta1   = 0.0f;
        yadro.delta2   = 0.0f;
        gameplay.proverka();
    }

    yadro.getIndexArray();
    yadro.draw();

    updateGL(); // обновить изображение
}

void Scene3D::stopTmr()
{
    timer->stop();
}

void Scene3D::startTmr()
{
    timer->start();
}
