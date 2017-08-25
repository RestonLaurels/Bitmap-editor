#include "ellips.h"
#include <QPainter>
#include <paintscene.h>

ellips::ellips(QPointF point, QObject *parent) :
    Figure(point,parent)
{
    Q_UNUSED(point)
}

ellips::~ellips()
{

}

void ellips::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    painter->setPen(QPen(QBrush(color), 4));

    QRectF ellip(endPoint().x() > startPoint().x() ? startPoint().x() : endPoint().x(),
                endPoint().y() > startPoint().y() ? startPoint().y() : endPoint().y(),
                qAbs(endPoint().x() - startPoint().x()),
                qAbs(endPoint().y() - startPoint().y()));


    painter->drawEllipse(ellip);
    Q_UNUSED(option)
    Q_UNUSED(widget)
}
