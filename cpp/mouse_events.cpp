#include "scene3d.h"
#include "QtWidgets"

void Scene3D::mousePressEvent(QMouseEvent* pe) // нажатие клавиши мыши
{
   // при нажатии пользователем кнопки мыши переменной ptrMousePosition
   // будет присвоена координата указателя мыши
   ptrMousePosition = pe->pos();
   timer->stop();
}

void Scene3D::mouseReleaseEvent(QMouseEvent* pe)
{
   // функции, которые должны выполняться при отжатии клавиши мыши
    timer->start();
}

// изменение положения стрелки мыши
void Scene3D::mouseMoveEvent(QMouseEvent* pe)
{
   // вычисление углов поворота
   xRot1 += 180/nSca*(GLfloat)(pe->y()-ptrMousePosition.y())/height();
   zRot1 += 180/nSca*(GLfloat)(pe->x()-ptrMousePosition.x())/width();
   xRot2 += 180/nSca*(GLfloat)(pe->y()-ptrMousePosition.y())/height();
   zRot2 += 180/nSca*(GLfloat)(pe->x()-ptrMousePosition.x())/width();


   //xTra2 += 5*(GLfloat)(pe->y()-ptrMousePosition.y())/height();
   //yTra2 += 5*(GLfloat)(pe->x()-ptrMousePosition.x())/height();
   //xTra2 += 5*(GLfloat)(pe->x()-ptrMousePosition.x())/height();
   //zTra2 += 5*(GLfloat)(pe->x()-ptrMousePosition.x())/width();

   ptrMousePosition = pe->pos();

   updateGL(); // обновление изображения
}

void Scene3D::mouseDoubleClickEvent(QMouseEvent* pe)
{
   QPoint mousePosition = pe->pos();

   this->selectFigures(mousePosition); // выбрать фигуру
}

// вращение колёсика мыши
void Scene3D::wheelEvent(QWheelEvent* pe)
{
   if ((pe->delta())>0) scale_plus(); else if ((pe->delta())<0) scale_minus();

   updateGL(); // обновление изображения
}

// нажатие определенной клавиши
void Scene3D::keyPressEvent(QKeyEvent* pe)
{
   switch (pe->key())
   {
      case Qt::Key_Plus:
         scale_plus();     // приблизить сцену
      break;

      case Qt::Key_Equal:
         scale_plus();     // приблизить сцену
      break;

      case Qt::Key_Minus:
         scale_minus();    // удалиться от сцены
      break;

      case Qt::Key_Up:
         rotate_up();      // повернуть сцену вверх
      break;

      case Qt::Key_Down:
         rotate_down();    // повернуть сцену вниз
      break;

      case Qt::Key_Left:
        rotate_left();     // повернуть сцену влево
      break;

      case Qt::Key_Right:
         rotate_right();   // повернуть сцену вправо
      break;

      case Qt::Key_Z:
         translate_down(); // транслировать сцену вниз
      break;

      case Qt::Key_X:
         translate_up();   // транслировать сцену вверх
      break;

      case Qt::Key_Space:  // клавиша пробела
         defaultScene();   // возвращение значений по умолчанию
      break;

      case Qt::Key_Escape: // клавиша "эскейп"
         this->close();    // завершает приложение
      break;
   }

   updateGL(); // обновление изображения
}

void Scene3D::scale_plus() // приблизить сцену
{
   nSca = nSca*1.1;
}

void Scene3D::scale_minus() // удалиться от сцены
{
   nSca = nSca/1.1;
}

void Scene3D::rotate_up() // повернуть сцену вверх
{
   xRot1 += 1.0;
}

void Scene3D::rotate_down() // повернуть сцену вниз
{
   xRot1 -= 1.0;
}

void Scene3D::rotate_left() // повернуть сцену влево
{
   zRot1 += 1.0;
}

void Scene3D::rotate_right() // повернуть сцену вправо
{
   zRot1 -= 1.0;
}

void Scene3D::translate_down() // транслировать сцену вниз
{
   zTra1 -= 0.05;
}

void Scene3D::translate_up() // транслировать сцену вверх
{
   zTra1 += 0.05;
}

void Scene3D::defaultScene() // наблюдение сцены по умолчанию
{
   xRot1=-90; yRot1=0; zRot1=0; zTra1=0; nSca=1;
}



