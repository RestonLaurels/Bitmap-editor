#ifndef PAINTSCENE_H
#define PAINTSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QTimer>
#include <QDebug>

class paintScene : public QGraphicsScene
{
    Q_OBJECT

public:
    double r;
    explicit paintScene(QObject *parent = 0);
    ~paintScene();
public slots:

private:
    QPointF     previousPoint;      // Координаты предыдущей точки

private:
    // Для рисования используем события мыши
    void mousePressEvent(QGraphicsSceneMouseEvent * event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

};

#endif // PAINTSCENE_H