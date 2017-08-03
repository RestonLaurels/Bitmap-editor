#include "paintscene.h"
#include "paint.h"
paintScene::paintScene(QObject *parent) : QGraphicsScene(parent)
{

}

paintScene::~paintScene()
{

}

void paintScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //int r = inputB->value();
    // При нажатии кнопки мыши отрисовываем эллипс
    addEllipse(event->scenePos().x() - r,
               event->scenePos().y() - r,
               r*2,
               r*2,
               QPen(Qt::NoPen),
               QBrush(Qt::blue));
    // Сохраняем координаты точки нажатия
    previousPoint = event->scenePos();
}

void paintScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{

    // Отрисовываем линии с использованием предыдущей координаты
    addLine(previousPoint.x(),
            previousPoint.y(),
            event->scenePos().x(),
            event->scenePos().y(),
            QPen(Qt::blue,r*2,Qt::SolidLine,Qt::RoundCap));
    // Обновляем данные о предыдущей координате
    previousPoint = event->scenePos();
}
void Paint::printOk()
{
//    cout << "Hello world!\n";
//    cout.flush();
    int a = inputA->value();
    int b = inputB->value();
    int c = a + b;
    result->setText(QString::asprintf("%d", c));
    result->resize(result->sizeHint());
}


