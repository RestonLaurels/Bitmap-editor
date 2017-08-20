#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <QObject>
#include <QGraphicsItem>
#include "figure.h"

class Ellips : public Figure
{
    Q_OBJECT

public:

    explicit Ellips(QPointF point, QObject *parent = 0);
    ~Triangle();

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // ELLIPS_H
