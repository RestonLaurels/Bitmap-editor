#ifndef PAINTSCENE_H
#define PAINTSCENE_H

#include "figure.h"

#include <QRgb>
#include <QPixmap>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QTimer>
#include <QDebug>
#include <QPainter>
#include <QPen>
#include <QPainter>
#include <QPen>
#include <QColor>
#include <QMouseEvent>\



#include <QLineEdit>

class paintScene : public QGraphicsScene
{
    Q_OBJECT
    //Свойство текущего типа используемой фигуры
    Q_PROPERTY(int typeFigure
               READ typeFigure WRITE setTypeFigure
               NOTIFY typeFigureChanged)

public:

    //QColor p;
    QColor color=Qt::blue;
    QColor specialcol;
    int transparency=255;
    double r = 0.5;
    int lever = 0;
    int style=0;

    int deep = 0;
    int maxdeep = 3;

    //QImage image;
    //QPainter painter;

    explicit paintScene(QObject *parent = 0);
    ~paintScene();

    void filling(int x, int y, QColor specialcol,QColor color,QImage *image, QPainter *painter, int deep);


    int typeFigure() const;                 // Возвращение текщего типа
    void setTypeFigure(const int type);     // Установка текущего типа

    // Перечисление типов используемых фигур
    enum FigureTypes {
        SquareType,
        RombType,
        TriangleType,
        EllipsType,
        LineType
    };
signals:
    void typeFigureChanged();

public slots:

private:

    Figure *tempFigure;
    int m_typeFigure;   // текущий тип фигуры

    QPointF     previousPoint;      // Координаты предыдущей точки

private:
    // Для рисования используем события мыши
    void mousePressEvent(QGraphicsSceneMouseEvent * event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

};

#endif // PAINTSCENE_H
