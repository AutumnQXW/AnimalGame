#include "backgrounds.h"

#include <QPainter>
#include <QPaintEvent>

Backgrounds::Backgrounds(QWidget *parent, Game::backgrounds backgrounds)
    : QWidget(parent)
    , backgrounds_id_(backgrounds)
{}

Backgrounds::~Backgrounds()
= default;

Mainroom::Mainroom(QWidget* parent)
    : Backgrounds(parent, Game::backgrounds::mainroom)
{}

Mainroom::~Mainroom()
= default;

void Mainroom::paintEvent(QPaintEvent* event)
{
    QPainter painter1(this);
    painter1.setOpacity(0.7);
    painter1.drawPixmap(0, 0, this->width(), this->height(), QPixmap(":/background/images/mainroom.jpg"));
    event->accept();
}

shop_background::shop_background(QWidget *parent)
    : Backgrounds(parent, Game::backgrounds::shop)
{
}

shop_background::~shop_background()
= default;

void shop_background::paintEvent(QPaintEvent* event)
{
    QPainter painter1(this);
    painter1.setOpacity(0.7);
    painter1.drawPixmap(0, 0, this->width(), this->height(), QPixmap(":/background/images/shop.jpg"));
    event->accept();
}

zuoban::zuoban(QWidget* parent)
    : Backgrounds(parent, Game::backgrounds::zuoban)
{
}

void zuoban::paintEvent(QPaintEvent* event)
{
    QPainter painter1(this);
    painter1.setOpacity(0.7);
    painter1.drawPixmap(0, 0, this->width(), this->height(), QPixmap(":/background/images/zuoban.jpg"));
    event->accept();
}

banzhuan::banzhuan(QWidget* parent)
    : Backgrounds(parent, Game::backgrounds::banzhuan)
{
}

void banzhuan::paintEvent(QPaintEvent* event)
{
    QPainter painter1(this);
    painter1.setOpacity(0.7);
    painter1.drawPixmap(0, 0, this->width(), this->height(), QPixmap(":/background/images/banzhuan.jpg"));
    event->accept();
}

gym::gym(QWidget* parent)
    : Backgrounds(parent, Game::backgrounds::gym)
{
}

void gym::paintEvent(QPaintEvent* event)
{
    QPainter painter1(this);
    painter1.setOpacity(0.7);
    painter1.drawPixmap(0, 0, this->width(), this->height(), QPixmap(":/background/images/gym.jpg"));
    event->accept();
}


park::park(QWidget* parent)
    : Backgrounds(parent, Game::backgrounds::park)
{}

park::~park()
= default;

void park::paintEvent(QPaintEvent* event)
{
    QPainter painter1(this);
    painter1.setOpacity(0.7);
    painter1.drawPixmap(0, 0, this->width(), this->height(), QPixmap(":/background/images/park.jpg"));
    event->accept();
}

