#include "paintscene.h"
#include "paint.h"
#include <QPainter>
#include <QPen>
#include <QLineEdit>
#include <QPixmap>
#include <QRgb>

paintScene::paintScene(QObject *parent) : QGraphicsScene(parent)
{

}

paintScene::~paintScene()
{

}


void paintScene::filling(int x, int y, QColor specialcolor,QColor color, QImage *image)
{

    if (color==specialcolor) return;//если цвет, которым мы закрашиваем совпадает с тем, который сейчас установлен, то уходим

    if ((x>=0)&&(y>=0)){ //если мы находимся в картине
        if (QColor((*image).pixel(x,y))==specialcolor){ //совпадение спеццвета с тем, на котором мы сейчас находимся
            //теперь красим
            addLine(x,y,x,y,
                    QPen(QBrush(color),1,Qt::SolidLine,Qt::RoundCap));
            //перемащее влево
            filling(x-1,y,specialcolor,color,image);
            //перемещение вверх
            //filling(x,y-1,specialcolor,color,image);
            //перемещение вправо
            //filling(x+1,y,specialcolor,color,image);
            //перемещение вниз
            //filling(x,y+1,specialcolor,color,image);
            return;
        }
        else return;
    }
    return;
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
            if(style==1){
                double x = event->scenePos().x(),
                       y = event->scenePos().y();
                QImage image(width(), height(), QImage::Format_ARGB32_Premultiplied);

                QPainter painter(&image);
                QColor specialcol;
                painter.setRenderHint(QPainter::Antialiasing);
                render(&painter);

                //запомнили цвет пикселя на котором стоим
                specialcol = QColor(image.pixel(x,y));
                //переходим к циклу закрашивания
                paintScene::filling(x,y,specialcol,color, &image);
                //x,y -мышка, цвет который закрашиваеем, цвет которым мы закрашиваем, указатель на картину
            }
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

