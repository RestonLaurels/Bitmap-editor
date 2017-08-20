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


void paintScene::filling(int x, int y, QColor specialcolor,QColor color, QImage *image)
{

    if (color!=specialcolor) return;//если цвет, которым мы закрашиваем совпадает с тем, который сейчас установлен, то уходим


    if ((x>=0)&&(y>=0)){ //если мы находимся в картине
        if (QColor((*image).pixel(x,y)) == specialcolor){ //совпадение спеццвета с тем, на котором мы сейчас находимся
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


/*
void paintScene::filling(int x, int y, QRgb oldColor,QRgb newColor, QImage & img)
{
            if (oldColor == newColor) return;

            QStack<QPoint> stk;
            QPoint pt;

            int y1;
            bool spanLeft, spanRight;

            stk.push(QPoint(x, y));
            addEllipse(x,y,r*2, r*2, QPen(Qt::NoPen), QBrush(color));
            while (!stk.empty()) {
                pt = stk.pop();
                x = pt.x();
                y = pt.y();

                y1 = y;
                while (y1 >= 0 && img.pixel(x, y1) == oldColor) y1--;
                y1++;

                spanLeft = spanRight = false;
                while (y1 < img.height() && img.pixel(x, y1) == oldColor) {
                    //img.setPixel(x, y1, newColor);
                    //addLine(x,y,x,y,QPen(QBrush(color),1,Qt::SolidLine,Qt::RoundCap));

                    //addEllipse(x,y,r*2, r*2, QPen(Qt::NoPen), QBrush(color));
                    //
                    if (!spanLeft && x > 0 && img.pixel(x-1, y1) == oldColor) {
                        stk.push(QPoint(x-1, y1));
                        spanLeft = true;
                    } else if(spanLeft && x > 0 && img.pixel(x-1, y1) != oldColor) {
                        spanLeft = false;
                    }
                    if (!spanRight && x < (img.width() - 1) && img.pixel(x+1, y1) == oldColor) {
                        stk.push(QPoint(x+1, y1));
                        spanRight = true;
                    } else if(spanRight && (x < img.width() - 1) && img.pixel(x+1, y1) != oldColor) {
                        spanRight = false;
                    }
                    y1++;
                }
            }
    return;
}

*/
void paintScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

    switch(style){
        case 0:
        {
        // При нажатии кнопки мыши отрисовываем эллипс
            //r = paint.inputA->value();
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
                QImage image(width(), height(), QImage::Format_RGB32);

                QPainter painter(&image);
                QColor specialcol;


                painter.setRenderHint(QPainter::Antialiasing);

                render(&painter);
                //запомнили цвет пикселя на котором стоим
                specialcol = QColor(image.pixel(x,y));
                //color=specialcol;
                //переходим к циклу закрашивания
                //paintScene::filling(x,y,specialcol.rgb(),color.rgb(), image);
                paintScene::filling(x,y,specialcol,color, &image);

                //x,y -мышка, цвет который закрашиваеем, цвет которым мы закрашиваем, указатель на картину
                //drawImage(0, 0, image);
                //addPixmap(image);
                //addPixmap(image);
                //QPainter().drawImage(0, 0, image);
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
            case RombType: {
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
        case 1:
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

