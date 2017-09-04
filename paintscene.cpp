#include "paintscene.h"
#include "paint.h"
#include <QPainter>
#include <QPen>
#include <QLineEdit>
#include <QPixmap>
#include <QRgb>
#include <QStack>

#include "paintscene.h"
#include "romb.h"
#include "triangle.h"
#include "square.h"
#include "ellips.h"
#include "line.h"

struct rem_l{
    int new_lx, old_lx;
    int y;

};
struct rem_r{
   int new_rx, old_rx;
   int y;

};


paintScene::paintScene(QObject *parent) : QGraphicsScene(parent)
{

}

paintScene::~paintScene()
{

}

int paintScene::typeFigure() const
{
    return m_typeFigure;
}

void paintScene::setTypeFigure(const int type)
{
    m_typeFigure = type;
}


void paintScene::filling(int x, int y, QColor specialcolor,QColor color, QImage *image, QPainter *painter, int deep)
{

    int right_x=x,left_x=x;
    int right_pred_x=x,left_pred_x=x;


    int up_remlastrx=0;
    int up_remlastlx=0;
    int up_remlasty=0;
    int down_remlastrx=0;
    int down_remlastlx=0;
    int down_remlasty=0;
    int uy;
    int dy;
    /* переменные для запоминания областей особой закраски
    *  где разница между новым и старыми левыми и правыми x  будет больше какого-то числа
    */
    rem_l reml[10];
    rem_r remr[10];

    int numberl=0;
    int numberr=0;

    if (deep >= maxdeep) return; // если мы уже слишком глубоко

    for (int up_y=y;(QColor((*image).pixel(x,up_y)) == specialcolor);up_y--)
    {
            if(QColor((*image).pixel(x,up_y)) == color) break;
            // если цвет заливкии и тот, который закрашиваем совпадают, то уходим

            for (int nowx=x;(QColor((*image).pixel(nowx,up_y)) == specialcolor); nowx++) {
                right_x=nowx;
            }
            if (abs(right_x-right_pred_x)>15){
                remr[numberr].new_rx=right_x;
                remr[numberr].old_rx=right_pred_x;
                remr[numberr].y=up_y;
                ++numberr;
            }

            for (int nowx=x;(QColor((*image).pixel(nowx,up_y)) == specialcolor); nowx--) {
                left_x=nowx;
            }
            if (abs(left_x-left_pred_x)>15){
                reml[numberl].new_lx=left_x;
                reml[numberl].old_lx=left_pred_x;
                reml[numberl].y=up_y;
                ++numberl;
            }


            addLine(right_x,up_y,left_x,up_y,
                QPen(QBrush(color),1,Qt::SolidLine,Qt::RoundCap));

            right_pred_x=right_x;
            left_pred_x=left_x;
            uy=up_y;


            //render(painter);

    }
    up_remlasty = uy;
    up_remlastlx = left_x;
    up_remlastrx = right_x;

    right_pred_x=x,
    left_pred_x=x;
    for (int down_y=y;(QColor((*image).pixel(x,down_y)) == specialcolor);down_y++)
    {
            if(QColor((*image).pixel(x,down_y)) == color) break;
            // если цвет карандаша и тот,который закрашиваем совпадают, то уходим
            for (int nowx=x;(QColor((*image).pixel(nowx,down_y)) == specialcolor); nowx++){
                right_x=nowx;
            }

            if (abs(right_x-right_pred_x)>15){
                remr[numberr].new_rx=right_x;
                remr[numberr].old_rx=right_pred_x;
                remr[numberr].y=down_y;
                ++numberr;
            }

            for (int nowx=x;(QColor((*image).pixel(nowx,down_y)) == specialcolor); nowx--){
                left_x=nowx;
            }

            if (abs(left_x-left_pred_x)>15){
                reml[numberl].new_lx=left_x;
                reml[numberl].old_lx=left_pred_x;
                reml[numberl].y=down_y;
                ++numberl;
            }

            addLine(right_x,down_y,left_x,down_y,
                QPen(QBrush(color),1,Qt::SolidLine,Qt::RoundCap));


            right_pred_x=right_x;
            left_pred_x=left_x;
            dy=down_y;
            //render(painter);
    }
    down_remlasty = dy;
    down_remlastlx = left_x;
    down_remlastrx = right_x;



    for (int i=1; i<numberl;++i)
    {
        filling( (reml[i].new_lx+reml[i].old_lx)/2,  reml[i].y,    specialcolor, color, image, painter,deep+1);
    }

    for (int j=1; j<numberr;++j)
    {
        filling( (remr[j].new_rx+remr[j].old_rx)/2,  remr[j].y,   specialcolor, color, image, painter,deep+1);
    }

    filling( (up_remlastrx   +   up_remlastlx)/2,  up_remlasty,    specialcolor, color, image, painter,deep+1);
    filling( (down_remlastrx + down_remlastlx)/2,  down_remlasty,  specialcolor, color, image, painter,deep+1);

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
            break;
        }
        case 1:
        {
           double x = event->scenePos().x(),
                       y = event->scenePos().y();
           QImage image(width(), height(), QImage::Format_ARGB32_Premultiplied);
           QPainter painter(&image);
           QColor specialcol;

           //painter.setRenderHint(QPainter::Antialiasing);
           render(&painter);
                //запоминаем цвет пикселя на котором стоим, чтобы знать какой цвет закрашива
           specialcol = image.pixel(x,y);
           paintScene::filling(event->scenePos().x(),event->scenePos().y(),specialcol,color, &image, &painter,0);

            break;

        }
        case 2:{
            switch (m_typeFigure) {

            case SquareType: {
                Square *item = new Square(event->scenePos());
                item->color=color;
                item->setPos(event->pos());
                tempFigure = item;
                break;
            }
            case RombType:{
                Romb *item = new Romb(event->scenePos());
                item->color=color;
                item->setPos(event->pos());
                tempFigure = item;
                break;
            }
            case TriangleType: {
                Triangle *item = new Triangle(event->scenePos());
                item->color=color;
                item->setPos(event->pos());
                tempFigure = item;
                break;
            }
            case EllipsType:{
                ellips *item = new ellips(event->scenePos());

                item->color=color;
                item->setPos(event->pos());
                tempFigure = item;
                break;
            }
            case LineType:{
                line *item = new line(event->scenePos());
                item->color=color;
                item->setPos(event->pos());
                tempFigure = item;
                break;


            }
            }
            this->addItem(tempFigure);
            break;
        }
    }
}
void paintScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
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
        break;
        }
        case 1:{
            break;
        }
        case 2:{
            /* Устанавливаем конечную координату положения мыши
            * в текущую отрисовываемую фигуру
            * */
            tempFigure->setEndPoint(event->scenePos());
            // Обновляем содержимое сцены, необходимо для устранения артефактов при отрисовке фигур

            this->update(QRectF(0,0,this->width(), this->height()));
            break;

        }

    }
}

