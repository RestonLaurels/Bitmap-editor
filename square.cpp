#include "square.h"
#include <QPainter>
#include <paintscene.h>

Square::Square(QPointF point, QObject *parent) :
    Figure(point,parent)
{
    Q_UNUSED(point)
}

Square::~Square()
{

}

// Реализуем метод отрисовки
void Square::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QPen(QBrush(color), 4));

    QRectF rect(endPoint().x() > startPoint().x() ? startPoint().x() : endPoint().x(),
                endPoint().y() > startPoint().y() ? startPoint().y() : endPoint().y(),
                qAbs(endPoint().x() - startPoint().x()),
                qAbs(endPoint().y() - startPoint().y()));

    painter->drawRect(rect);

    Q_UNUSED(option)
    Q_UNUSED(widget)
}

