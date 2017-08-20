#ifndef PAINT_H
#define PAINT_H
#include <QMainWindow>
#include <QRgb>
#include <QPixmap>
#include <QWidget>
#include <QTimer>
#include <QResizeEvent>
#include <QWidget>
#include <QPushButton>
#include <QSpinBox>
#include <QLabel>
#include <QPainter>
#include <QPen>
#include <QLineEdit>
#include <QPainter>

#include <paintscene.h>

namespace Ui {
class Paint;
}

class Paint : public QWidget
{
    Q_OBJECT

public:
    QPushButton *button;

    QPushButton *fillbutton;

    QPushButton *redbutton;
    QPushButton *orangebutton;
    QPushButton *yellowbutton;
    QPushButton *greenbutton;
    QPushButton *lbluebutton;
    QPushButton *bluebutton;
    QPushButton *purpurebutton;
    QPushButton *greybutton;
    QPushButton *blackbutton;

    QPushButton *savebutton;
    QPushButton *loadbutton;

    QPushButton *eraserbutton;

    QLineEdit *specialline;

    QSpinBox *redgrad;
    QSpinBox *bluegrad;
    QSpinBox *greengrad;
    QPushButton *hardcolorbutton;

    QPushButton *trianglebutton;
    QPushButton *rombbutton;
    QPushButton *squarebutton;
    QPushButton *ellipsbutton;



    QDoubleSpinBox *inputA;
    //QLabel *result;

    explicit Paint(QWidget *parent = 0);
    ~Paint();
    void romb();
    void square();
    void ellips();
    void triangle();


    void pencil();
    void fill();

    void red();
    void blue();
    void lblue();
    void orange();

    void grey();
    void black();
    void green();
    void yellow();

    void eras();
    void hardcolor();

    void purpure();

    void save();
    void load();
private:
    Ui::Paint *ui;
    QTimer *timer;      // Определяем таймер для подготовки актуальных размеро граф. сцены
    paintScene *scene;  // Объявляем кастомную графическую сцену

private:
    // Переопределяем событие изменения размера окна
    void resizeEvent(QResizeEvent * event);

private slots:
    void slotTimer();
};

#endif // PAINT_H
