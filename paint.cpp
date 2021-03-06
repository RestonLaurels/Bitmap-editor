#include "paint.h"
#include "ui_paint.h"
#include <QPainter>
#include <QPushButton>
#include <iostream>
#include <QString>
#include <QPen>
#include <QLineEdit>
#include <QPixmap>
#include <QRgb>

Paint::Paint(QWidget *parent) :QWidget(parent), ui(new Ui::Paint)

{
    rombbutton = new QPushButton (this);
    rombbutton->setMaximumWidth(45);
    rombbutton->setText("Romb");
    rombbutton->move(255, 35);
    connect(rombbutton, &QPushButton::clicked,this, &Paint::romb);

    deepbutton = new QSpinBox (this);
    deepbutton->setMaximumWidth(45);
    deepbutton->setValue(5);
    deepbutton->move(5,250);

    textbutton = new QLabel(this);
    textbutton->move(2, 280);
    textbutton->setText("Maxdeep");


    trianglebutton = new QPushButton(this);
    trianglebutton->setMaximumWidth(45);
    trianglebutton->setText("Triangle");
    trianglebutton->move(300, 35);
    connect(trianglebutton, &QPushButton::clicked,this, &Paint::triangle);


    ellipsbutton = new QPushButton (this);
    ellipsbutton->setMaximumWidth(45);
    ellipsbutton->setText("Ellips");
    ellipsbutton->move(345, 35);
    connect(ellipsbutton, &QPushButton::clicked,this, &Paint::ellips);

    squarebutton = new QPushButton (this);
    squarebutton->setMaximumWidth (45);
    squarebutton->setText("Square");
    squarebutton->move(390, 35);
    connect(squarebutton, &QPushButton::clicked,this, &Paint::square);

    linebutton = new QPushButton (this);
    linebutton ->setMaximumWidth((45));
    linebutton->setText("Line");
    linebutton->move(435,35);
    connect(linebutton, &QPushButton::clicked,this, &Paint::line);


    button = new QPushButton(this);
    button->setMaximumWidth(70);
    button->setText("brush");
    button->move(0, 100);
    connect(button, &QPushButton::clicked,this, &Paint::pencil);

    fillbutton = new QPushButton(this);
    fillbutton->setText("Filing");
    fillbutton->move(0, 130);
    fillbutton->setMaximumWidth(70);
    connect(fillbutton, &QPushButton::clicked,this, &Paint::fill);

    delebutton = new QPushButton(this);
    delebutton->setText(("Clear screen"));
    delebutton->move(0,210);
    delebutton->setMaximumWidth(70);
    connect(delebutton,&QPushButton::clicked,this, &Paint::dele);


    //толщина маркера
    inputA = new QDoubleSpinBox(this);
    inputA->move(5, 70);
    inputA->setMaximumWidth(50);
    inputA->setMaximum(50.0);
    inputA->setMinimum(0.5);
    inputA->setValue(9.50);

    //линия для загрузки и сохранения
    specialline = new QLineEdit(this);
    specialline->move(5,5);
    specialline->setMinimumWidth(160);
    specialline->setText("D:/Project/Wii/test/");

    loadline = new QLineEdit(this);
    loadline->move(5,35);
    loadline->setMinimumWidth(160);
    loadline->setText("D:/");

    //Цвет из градиента
    {
        hardcolorbutton = new QPushButton(this);
        hardcolorbutton->move(570,5);
        hardcolorbutton->setMaximumWidth(30);
        hardcolorbutton->setText("RGB");
        //hardcolorbutton
        redgrad = new QSpinBox(this);
        redgrad->setMaximum(255);
        redgrad->setMaximumWidth(40);
        redgrad->move(450,5);
        redgrad->setValue(128);

        bluegrad = new QSpinBox(this);
        bluegrad->setMaximum(255);
        bluegrad->setMaximumWidth(40);
        bluegrad->move(490,5);
        bluegrad->setValue(128);

        greengrad = new QSpinBox(this);
        greengrad->setMaximum(255);
        greengrad->setMaximumWidth(40);
        greengrad->move(530,5);
        greengrad->setValue(128);

        connect(hardcolorbutton, &QPushButton::clicked,this, &Paint::hardcolor);

    }
    //загрузка

    {
    loadbutton = new QPushButton(this);
    loadbutton->setText("load from");
    loadbutton->move(170,35);
    loadbutton->setMaximumWidth(80);
    connect(loadbutton, &QPushButton::clicked,this,&Paint::load);
    }
    //сохранение
    {
    savebutton = new QPushButton(this);
    savebutton->setText("save to");
    savebutton->move(170,5);
    savebutton->setMaximumWidth(80);
    connect(savebutton, &QPushButton::clicked,this, &Paint::save);
    }
    //кнопки цветов:
    //Стёрка
    {
    eraserbutton = new QPushButton(this);
    eraserbutton->setMaximumWidth(70);
    eraserbutton->move(0,160);
    connect(eraserbutton, &QPushButton::clicked,this, &Paint::eras);
    eraserbutton->setText("Eraser");
    }

    {
        //красный
    {
    redbutton = new QPushButton(this);
    redbutton->setMaximumWidth(20);
    redbutton->move(257,5);
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
    orangebutton->move(278,5);
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
    yellowbutton->move(299,5);
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
    greenbutton->move(320,5);
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
    lbluebutton->move(341,5);
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
    bluebutton->move(362,5);
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
    purpurebutton->move(383,5);
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
    greybutton->move(404,5);
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
    blackbutton->move(425,5);
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
    //autoFillBackground : 1;
    timer = new QTimer();       // Инициализируем таймер
    connect(timer, &QTimer::timeout, this, &Paint::slotTimer);
    timer->start(50);          // Запускаем таймер
    scene->r=inputA->value();
    //QPainter painter(&(scene->image));

}

Paint::~Paint()
{
    delete ui;
}

void Paint::slotTimer()
{
    // Переопределяем размеры графической сцены в зависимости от размеров окна
    timer->stop();
    scene->setSceneRect(0,0, ui->graphicsView->width()-10, ui->graphicsView->height()-10);
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
void Paint::thick(){

    scene->r = inputA->value();
}
void Paint::fill()
{
    scene->maxdeep = deepbutton->value();
    scene->style=1;
    //scene->image = QImage(scene->width(),scene->height(),QImage::Format_RGB32);

    //scene->painter = QPainter(&scene->image);

    //scene->painter.setRenderHint(QPainter::Antialiasing);

    scene->r=inputA->value();
}

void Paint::dele()
{
    //delete scene;

    //ui->graphicsView->
    scene = new paintScene();       // Инициализируем графическую сцену

    ui->graphicsView->setScene(scene);  // Устанавливаем графическую сцену
    //autoFillBackground : 1;
    timer = new QTimer();       // Инициализируем таймер
    connect(timer, &QTimer::timeout, this, &Paint::slotTimer);
    timer->start(50);          // Запускаем таймер
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
    scene->color.setRgb(1,1,1,scene->transparency);
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
    scene->style=0;
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
    QColor col;
    QRgb rgb;
    rgb = qRgb(255,255,255);
    col.setRgb(0,0,0,255);
    scene->render(&painter);

    for (int x=0; x<=scene->width(); x++){
        for (int y=0; y<=scene->height();y++){

            if (QColor(image.pixel(x,y))==col){
               image.setPixel(x,y,rgb);

            }

        }
    }

    image.save(specialline->text());
}
void Paint::load(){
    QPixmap painter;
    painter.load(loadline->text());
    scene->addPixmap(painter);

}

void Paint::square(){
    scene->style=2;
    scene->setTypeFigure(paintScene::SquareType);
    scene->r=inputA->value();
}
void Paint::ellips(){
    scene->style=2;
    scene->setTypeFigure(paintScene::EllipsType);
    scene->r=inputA->value();
}
void Paint::triangle(){
    scene->style=2;
    scene->setTypeFigure(paintScene::TriangleType);

    scene->r=inputA->value();

}
void Paint::romb(){
    scene->style=2;
    scene->setTypeFigure(paintScene::RombType);
    scene->r=inputA->value();

}

void Paint::line(){
    scene->style = 2;
    scene->setTypeFigure(paintScene::LineType);
    scene->r=inputA->value();

}

