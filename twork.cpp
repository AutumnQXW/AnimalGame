#include "twork.h"

#include <QTimerEvent>

TWork::TWork(QWidget* parent, TCharacter* character_)
    : QWidget(parent),
      character(character_),
      isWorking(false)
{
}

TWork::~TWork()
{
}

void TWork::set_character(TCharacter* character_)
{
    character = character_;
}

bool TWork::banzhuan()
{
    if (!character->powerUpDown(true, 3))
    {
        qDebug() << "体力不足！\n";
        return false;
    }
    if (!character->getWorking())
    {
        character->setWorking(true);
        timer_id_banzhuan = startTimer(300 * 1000);
        qDebug() << "搬砖开始\n";
        return true;
    }
    else
    {
        qDebug() << "已经在工作了！\n";
        return false;
    }
}

bool TWork::zuoban()
{
    if (character->powerUpDown(true, 2))
    {
        if (!character->getWorking())
        {
            character->setWorking(true);
            timer_id_zuoban = startTimer(240 * 1000);
            qDebug() << "坐班开始\n";
            return true;
        }
        else
        {
            qDebug() << "已经在工作了！\n";
            return false;
        }
    }
    else
    {
        qDebug() << "体力不足！\n";
        return false;
    }
}

void TWork::timerEvent(QTimerEvent* event)
{
    if (event->timerId() == timer_id_banzhuan)
    {
        character->heartUpDown(true, 5);
        character->expUpDown(20);
        character->moneyUpDown(true, 150);
        character->setWorking(false);
        qDebug() << "工作结束\n";
    }
    if (event->timerId() == timer_id_zuoban)
    {
        character->heartUpDown(true, 5);
        character->expUpDown(40);
        character->moneyUpDown(true, 250);
        character->setWorking(false);
        qDebug() << "工作结束\n";
    }
    emit workEnd();
}

void TWork::stop_working()
{
    killTimer(timer_id_banzhuan);
    killTimer(timer_id_zuoban);
}
