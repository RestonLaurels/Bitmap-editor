#include "paint.h"
#include "ui_paint.h"
#include <QPainter>
#include <QPushButton>
#include <iostream>
#include <QString>
#include <QPen>
#include <QLineEdit>
#include <QPixmap>

Paint::Paint(QWidget *parent) :QWidget(parent), ui(new Ui::Paint)

{
    button = new QPushButton(this);
    button->setMaximumWidth(70);
    button->setText("Карандаш");
    button->move(0, 120); // Координаты относительно виджета, в который вложен button.
    QObject:connect(button, &QPushButton::clicked,this, &Paint::pencil);

    fillbutton = new QPushButton(this);
    fillbutton->setText("Заливка");
    fillbutton->move(0, 150);
    connect(fillbutton, &QPushButton::clicked,this, &Paint::fill);

    //толщина маркера
    inputA = new QDoubleSpinBox(this);
    inputA->move(4, 40);
    inputA->setMaximum(50.0);
    inputA->setMinimum(0.5);
    //
    //линия для загрузки и сохранения
    specialline = new QLineEdit(this);
    specialline->move(0,200);
    specialline->setMaximumWidth(80);
    specialline->setText("D:/");

    //Цвет из градиента
    {
        hardcolorbutton = new QPushButton(this);
        hardcolorbutton->move(420,5);
        hardcolorbutton->setMaximumWidth(30);
        hardcolorbutton->setText("RGB");
        //hardcolorbutton
        redgrad = new QSpinBox(this);
        redgrad->setMaximum(255);
        redgrad->setMaximumWidth(40);
        redgrad->move(300,5);

        bluegrad = new QSpinBox(this);
        bluegrad->setMaximum(255);
        bluegrad->setMaximumWidth(40);
        bluegrad->move(340,5);

        greengrad = new QSpinBox(this);
        greengrad->setMaximum(255);
        greengrad->setMaximumWidth(40);
        greengrad->move(380,5);
        connect(hardcolorbutton, &QPushButton::clicked,this, &Paint::hardcolor);

    }
    //загрузка

    {
    loadbutton = new QPushButton(this);
    loadbutton->setText("load from");
    loadbutton->move(4,120);
    loadbutton->setMaximumWidth(80);
    connect(loadbutton, &QPushButton::clicked,this,&Paint::load);
    }
    //сохранение
    {
    savebutton = new QPushButton(this);
    savebutton->setText("save to");
    savebutton->move(4,180);
    savebutton->setMaximumWidth(80);
    connect(savebutton, &QPushButton::clicked,this, &Paint::save);
    }
    //кнопки цветов:
    //Стёрка
    {
    eraserbutton = new QPushButton(this);
    eraserbutton->setMaximumWidth(30);
    eraserbutton->move(455,5);
    connect(eraserbutton, &QPushButton::clicked,this, &Paint::eras);
    eraserbutton->setText("Стерка");
    }

    {
        //красный
    {
    redbutton = new QPushButton(this);
    redbutton->setMaximumWidth(20);
    redbutton->move(95,5);
    connect(redbutton, &QPushButton::clicked,this, &Paint::red);

    redbutton->setStyleSheet(
                    "QPushButton{"
                    "background-color: rgb(250, 0, 0);"
                    "border-radius: 4px transparent;"
                    "border-bottom: 3px transparent;"
                    "border-right: 2px transparent;"
                    "border-left: 2px transparent;}"
                    "QPushButton:hover{"
                    "background-color: rgb(250,0,0);} "
                    "QPushButton:pressed  {"
                    "background-color: rgb(200,0,0); } "
                    );
    }
        //Оранжевый
    {
    orangebutton = new QPushButton(this);
    orangebutton->move(117,5);
    orangebutton->setMaximumWidth(20);
    connect(orangebutton, &QPushButton::clicked,this, &Paint::orange);
    orangebutton->setStyleSheet(
                    "QPushButton{"
                    "background-color: rgb(255,140,0);"
                    "border-radius: 4px transparent;"
                    "border-bottom: 3px transparent;"
                    "border-right: 2px transparent;"
                    "border-left: 2px transparent;}"
                    "QPushButton:hover{"
                    "background-color: rgb(255,140,0);} "
                    "QPushButton:pressed  {"
                    "background-color: rgb(200,100,0); } "
                    );
    }
        //желтый
    {
    yellowbutton = new QPushButton(this);
    connect(yellowbutton, &QPushButton::clicked,this, &Paint::yellow);
    yellowbutton->move(139,5);
    yellowbutton->setMaximumWidth(20);
    yellowbutton->setStyleSheet(
                    "QPushButton{"
                    "background-color: rgb(255,255,0);"
                    "border-radius: 4px transparent;"
                    "border-bottom: 3px transparent;"
                    "border-right: 2px transparent;"
                    "border-left: 2px transparent;}"
                    "QPushButton:hover{"
                    "background-color: rgb(255,255,0);} "
                    "QPushButton:pressed  {"
                    "background-color: rgb(200,200,0); } "
                    );
    }
        //зеленый
    {
    greenbutton = new QPushButton(this);
    connect(greenbutton, &QPushButton::clicked,this, &Paint::green);
    greenbutton->move(161,5);
    greenbutton->setMaximumWidth(20);
    greenbutton->setStyleSheet(
                    "QPushButton{"
                    "background-color: rgb(50, 205, 50);"
                    "border-radius: 4px transparent;"
                    "border-bottom: 3px transparent;"
                    "border-right: 2px transparent;"
                    "border-left: 2px transparent;}"
                    "QPushButton:hover{"
                    "background-color: rgb(50,205,50);} "
                    "QPushButton:pressed  {"
                    "background-color: rgb(10,165,10); } "
                    );
    }
        //Голубой
    {
    lbluebutton = new QPushButton(this);
    connect(lbluebutton, &QPushButton::clicked,this, &Paint::lblue);
    lbluebutton->move(183,5);
    lbluebutton->setMaximumWidth(20);
    lbluebutton->setStyleSheet(
                    "QPushButton{"
                    "background-color: rgb(100,149,237);"
                    "border-radius: 4px transparent;"
                    "border-bottom: 3px transparent;"
                    "border-right: 2px transparent;"
                    "border-left: 2px transparent;}"
                    "QPushButton:hover{"
                    "background-color: rgb(100,149,237);} "
                    "QPushButton:pressed  {"
                    "background-color: rgb(60,109,197); } "
                    );
    }
        //Синий
    {
    bluebutton = new QPushButton(this);
    connect(bluebutton, &QPushButton::clicked,this, &Paint::blue);
    bluebutton->move(205,5);
    bluebutton->setMaximumWidth(20);
    bluebutton->setStyleSheet(
                    "QPushButton{"
                    "background-color: rgb(0,0,139);"
                    "border-radius: 4px transparent;"
                    "border-bottom: 3px transparent;"
                    "border-right: 2px transparent;"
                    "border-left: 2px transparent;}"
                    "QPushButton:hover{"
                    "background-color: rgb(0,0,139);} "
                    "QPushButton:pressed  {"
                    "background-color: rgb(0,0,99); } "
                    );
    }
        //Фиолетовый
    {
    purpurebutton = new QPushButton(this);
    connect(purpurebutton, &QPushButton::clicked,this, &Paint::purpure);
    purpurebutton->move(227,5);
    purpurebutton->setMaximumWidth(20);
    purpurebutton->setStyleSheet(
                    "QPushButton{"
                    "background-color: rgb(138, 43, 226);"
                    "border-radius: 4px transparent;"
                    "border-bottom: 3px transparent;"
                    "border-right: 2px transparent;"
                    "border-left: 2px transparent;}"
                    "QPushButton:hover{"
                    "background-color: rgb(138,43,226);} "
                    "QPushButton:pressed  {"
                    "background-color: rgb(98,03,186); } "
                    );
    }
        //Серый
    {
    greybutton = new QPushButton(this);
    connect(greybutton, &QPushButton::clicked,this, &Paint::grey);
    greybutton->move(249,5);
    greybutton->setMaximumWidth(20);
    greybutton->setStyleSheet(
                    "QPushButton{"
                    "background-color: rgb(139, 139, 139);"
                    "border-radius: 4px transparent;"
                    "border-bottom: 3px transparent;"
                    "border-right: 2px transparent;"
                    "border-left: 2px transparent;}"
                    "QPushButton:hover{"
                    "background-color: rgb(139,139,139);} "
                    "QPushButton:pressed  {"
                    "background-color: rgb(99,99,99); } "
                    );
    }
        //черный
    {
    blackbutton = new QPushButton(this);
    connect(blackbutton, &QPushButton::clicked,this, &Paint::black);
    blackbutton->move(271,5);
    blackbutton->setMaximumWidth(20);
    blackbutton->setStyleSheet(
                    "QPushButton{"
                    "background-color: rgb(0, 0, 0);"
                    "border-radius: 4px transparent;"
                    "border-bottom: 3px transparent;"
                    "border-right: 2px transparent;"
                    "border-left: 2px transparent;}"
                    "QPushButton:hover{"
                    "background-color: rgb(0,0,0);} "
                    "QPushButton:pressed  {"
                    "background-color: rgb(40,40,40); } "
                    );
    }
    }
    ui->setupUi(this);
    scene = new paintScene();       // Инициализируем графическую сцену

    ui->graphicsView->setScene(scene);  // Устанавливаем графическую сцену

    timer = new QTimer();       // Инициализируем таймер
    connect(timer, &QTimer::timeout, this, &Paint::slotTimer);
    timer->start(50);          // Запускаем таймер
}

Paint::~Paint()
{
    delete ui;
}

void Paint::slotTimer()
{
    // Переопределяем размеры графической сцены в зависимости от размеров окна
    timer->stop();
    scene->setSceneRect(15,15, ui->graphicsView->width()-20, ui->graphicsView->height()-20);
}
void Paint::resizeEvent(QResizeEvent *event)
{
    timer->start(100);
    QWidget::resizeEvent(event);
}
void Paint::pencil()
{
    int a = inputA->value();
    scene->r=a;
    scene->style=0;
}

void Paint::fill()
{
    scene->style=1;
    scene->r=inputA->value();
}

void Paint::red()
{
    scene->lever = 1;
    scene->r = inputA->value();
    scene->color.setRgb(250,0,0,scene->transparency);
}
void Paint::orange()
{
    scene->lever = 2;
    scene->r = inputA->value();
    scene->color.setRgb(255,140,0,scene->transparency);
}
void Paint::yellow()
{
    scene->lever = 3;
    scene->r = inputA->value();
    scene->color.setRgb(255,255,0,scene->transparency);
}
void Paint::green()
{
    scene->lever = 4;
    scene->r = inputA->value();
    scene->color.setRgb(50,205,50,scene->transparency);
}
void Paint::lblue()
{
    scene->lever = 5;
    scene->r = inputA->value();
    scene->color.setRgb(100,149,237,scene->transparency);
}
void Paint::blue()
{
    scene->lever = 6;
    scene->r = inputA->value();
    scene->color.setRgb(0,0,139,scene->transparency);
}
void Paint::purpure()
{
    scene->lever = 7;
    scene->r = inputA->value();
    scene->color.setRgb(138,43,226,scene->transparency);
}
void Paint::black()
{
    scene->lever = 8;
    scene->r = inputA->value();
    scene->color.setRgb(0,0,0,scene->transparency);
}
void Paint::grey()
{
    scene->lever = 9;
    scene->r = inputA->value();
    scene->color.setRgb(139,139,139,scene->transparency);
}
void Paint::eras()
{
    scene->lever = 0;
    scene->r = inputA->value()*1.5+4;
    scene->color.setRgb(255,255,255,scene->transparency);
}
void Paint::hardcolor()
{
    int r=redgrad->value(),
        g=greengrad->value(),
        b=bluegrad->value();
    scene->color.setRgb(r,g,b,scene->transparency);
    scene->r = inputA->value();

}

void Paint::save(){
    QImage image(scene->width(), scene->height(), QImage::Format_ARGB32_Premultiplied);
    QPainter painter(&image);
    //image.fill(NULL);
    scene->render(&painter);
    image.save(specialline->text());
}
void Paint::load(){
    QPixmap painter;
    painter.load(specialline->text());
    scene->addPixmap(painter);

}
