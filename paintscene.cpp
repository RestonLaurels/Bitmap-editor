#include "paintscene.h"
#include "paint.h"
#include <QPainter>
#include <QPen>
paintScene::paintScene(QObject *parent) : QGraphicsScene(parent)
{

}

paintScene::~paintScene()
{

}

void paintScene::filling()
{
    //определние цвета на этой координате
    //долгосрочно запоминаем его - сделать это необходимо до вызова функции


    //если он совпадает с тем цветом которым мы закрашиваем, то возвращаемся
    //если запомненный цвет не совпадает с нынешним, то возвращаемся

    //теперь определяем

    //перемащение влево
    //перемещение вверх
    //перемещение вправо
    //перемещение вниз


}

void Coloring(int x, int y){


}

void paintScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

    switch(style){
        case 0:
        {
        // При нажатии кнопки мыши отрисовываем эллипс
            addEllipse(event->scenePos().x() - r,
                        event->scenePos().y() - r,
                        r*2,
                        r*2,
                        QPen(Qt::NoPen),
                        QBrush(color));
        // Сохраняем координаты точки нажатия
            previousPoint = event->scenePos();
        }
        case 1:
        {
            double x = event->scenePos().x(),
                   y = event->scenePos().y();
            //определние цвета на этой координате
            //долгосрочно запоминаем его - сделать это необходимо до вызова функции
            /*
            QImage image;
            QPainter painter(&image);
            painter.setRenderHint(QPainter::Antialiasing);
            render(&painter);

            //addPixmap()
            */
            addEllipse(event->scenePos().x() - r,
                    event->scenePos().y() - r,
                    r*2,
                    r*2,
                    QPen(Qt::NoPen),
                    QBrush(color));

        }
        case 2:{}
    }
}

void paintScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    //const QColour ue";
    //QBrush p;
    //p.setColor(Qt::green);
    //p.setRgbF(255,255,255,1.0);
    // Отрисовываем линии с использованием предыдущей координаты
    switch(style){

        case 0:
        {
        addLine(previousPoint.x(),
                previousPoint.y(),
                event->scenePos().x(),
                event->scenePos().y(),
                QPen(QBrush(color),r*2,Qt::SolidLine,Qt::RoundCap));

        // Обновляем данные о предыдущей координате
        previousPoint = event->scenePos();
        }
        case 1:
        case 2:{}
    }
}
