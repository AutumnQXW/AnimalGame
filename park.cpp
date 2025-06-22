#include "park.h"

#include <QPainter>
#include <QPaintEvent>

park::park(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::parkClass())
    , backgrounds_id(Game::backgrounds::park)
{
    ui->setupUi(this);
}

park::~park()
{
    delete ui;
}

void park::paintEvent(QPaintEvent* event)
{
    QPainter painter1(this);
    painter1.setOpacity(0.7);
    painter1.drawPixmap(0, 0, this->width(), this->height(), QPixmap(":/background/images/park.jpg"));
    event->accept();

}
