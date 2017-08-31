#include "triangle.h"
#include <QPainter>
#include <paintscene.h>

Triangle::Triangle(QPointF point, QObject *parent) :
    Figure(point,parent)
{
    Q_UNUSED(point)
}

Triangle::~Triangle()
{

}

// Реализуем метод отрисовки
void Triangle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QPen(QBrush(color), 4));

    QPolygonF polygon;

    polygon << QPointF(endPoint().x() + (startPoint().x() > endPoint().x() ? + 1 : - 1)*
                           abs((startPoint().x() - endPoint().x())/2), endPoint().y())
                << QPointF((endPoint().x() > startPoint().x()) ? endPoint().x() : startPoint().x(),
                           startPoint().y())
                << QPointF((endPoint().x() > startPoint().x()) ? startPoint().x() : endPoint().x(),
                           startPoint().y());

    painter->drawPolygon(polygon);

    Q_UNUSED(option)
    Q_UNUSED(widget)
}
