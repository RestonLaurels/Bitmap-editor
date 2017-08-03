#include "paint.h"
#include "ui_paint.h"

#include <QPushButton>
#include <iostream>
#include <QString>

Paint::Paint(QWidget *parent) :QWidget(parent), ui(new Ui::Paint)

{     // this -- это указатель на контекстный объект,
     // то есть тот объект класса MyWidget, который
    // в данный момент конструируем.
    button = new QPushButton(this);
    button->setText("Ok!");
    QObject:connect(button, &QPushButton::clicked,this, &Paint::printOk);

    button->move(0, 120); // Координаты относительно виджета, в который вложен button.

    inputA = new QSpinBox(this);
    inputA->move(0, 40);
    inputB = new QSpinBox(this);
    inputB->move(0, 80);
    result = new QLabel(this);
    result->move(0, 160);
    result->setText("hello");

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
    /* Переопределяем размеры графической сцены в зависимости
     * от размеров окна
     * */
    timer->stop();
    scene->setSceneRect(0,0, ui->graphicsView->width()-20, ui->graphicsView->height() -20);
}

void Paint::resizeEvent(QResizeEvent *event)
{
    timer->start(100);
    QWidget::resizeEvent(event);
}

