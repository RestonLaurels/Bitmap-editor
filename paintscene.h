#ifndef PAINTSCENE_H
#define PAINTSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QTimer>
#include <QDebug>
#include <QPainter>
#include <QPen>
#include <QPainter>
#include <QPen>
#include <QColor>
#include <QMouseEvent>
class paintScene : public QGraphicsScene
{
    Q_OBJECT

public:

    //QColor p;
    QColor color;
    int transparency=255;
    double r = 0.5;
    int lever = 0;
    int style=0;

    explicit paintScene(QObject *parent = 0);
    ~paintScene();

    void filling();
public slots:

private:
    QPointF     previousPoint;      // Координаты предыдущей точки

private:
    // Для рисования используем события мыши
    void mousePressEvent(QGraphicsSceneMouseEvent * event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

};

#endif // PAINTSCENE_H
