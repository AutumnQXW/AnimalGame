#include "mainroom.h"

#include <QPainter>
#include <QPaintEvent>

Mainroom::Mainroom(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainroomClass())
    , backgrounds_id(Game::backgrounds::mainroom)
{
    ui->setupUi(this);
}

Mainroom::~Mainroom()
{
    delete ui;
}

void Mainroom::paintEvent(QPaintEvent* event)
{
    QPainter painter1(this);
    painter1.setOpacity(0.7);
    painter1.drawPixmap(0, 0, this->width(), this->height(), QPixmap(":/background/images/mainroom.jpg"));
    event->accept();
}
