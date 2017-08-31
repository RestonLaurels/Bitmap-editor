#include "line.h"
#include <QPainter>
#include <QLineF>
#include <paintscene.h>

line::line(QPointF point, QObject *parent) :
    Figure(point,parent)
{
    Q_UNUSED(point)
}



line::~line()
{

}

// Реализуем метод отрисовки
void line::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QPen(QBrush(color), 4));

    QLineF line(startPoint().x(), startPoint().y() , endPoint().x(),
                endPoint().y());

    painter->drawLine(line);

    Q_UNUSED(option)
    Q_UNUSED(widget)
}
