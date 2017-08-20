#ifndef ELLIPS_H
#define ELLIPS_H

#include <QWidget>
#include <QGraphicsItem>
#include "figure.h"

class ellips : public Figure
{
    Q_OBJECT
public:

    explicit ellips(QPointF point, QObject *parent = 0);
    ~ellips();
private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

signals:

public slots:
};

#endif // ELLIPS_H

