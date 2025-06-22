#include "tgood.h"
#include "tcharacter.h"

TGood::TGood(QWidget* parent)
    : QWidget(parent)
      , num(0),
      price(0),
      weightUp(0),
      powerUp(0),
      intervalTime(0)

{
}

TGood::TGood()
    : num(0),
      price(0),
      weightUp(0),
      powerUp(0),
      intervalTime(0)

{
}

TGood::TGood(const TGood& t_good)
    : num(t_good.num),
      price(t_good.price),
      weightUp(t_good.weightUp),
      powerUp(t_good.powerUp),
      intervalTime(t_good.intervalTime)
//timer_(t_good.timer_)
{
}


TGood::~TGood()
{
}

TGood& TGood::operator=(const TGood& good)
{
    this->num = good.num;
    this->price = good.price;
    this->weightUp = good.weightUp;
    this->powerUp = good.powerUp;
    this->intervalTime = good.intervalTime;
    return *this;
}

void TGood::setValue(int price_, int weight_up_, int power_up_, int interval_time_)
{
    num = 0;
    price = price_;
    weightUp = weight_up_;
    powerUp = power_up_;
    intervalTime = interval_time_;
}

bool TGood::useItems(TCharacter& character)
{
    if (num >= 1)
    {
        num--;
        character.weightUpDown(false, weightUp);
        character.powerUpDown(false, powerUp);
        return true;
    }
    return false;
}

//void TGood::start_timer()
//{
//    timer_ = new QTimer;
//    timer_->setTimerType(Qt::CoarseTimer);
//    timer_->setSingleShot(false);
//    timer_->start(intervalTime * 1000);
//}
