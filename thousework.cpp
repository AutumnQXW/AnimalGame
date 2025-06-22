#include "thousework.h"

#include <QTimerEvent>

THousework::THousework(QWidget* parent, TCharacter* character_)
    : QWidget(parent),
      //isWorking(false),
      character(character_)
{
}

THousework::~THousework()
{
}

void THousework::set_character(TCharacter* character_)
{
    character = character_;
}

void THousework::timerEvent(QTimerEvent* event)
{
    if (event->timerId() == timer_id_clean)
    {
        qDebug() << "打扫卫生工作结束\n";
        character->heartUpDown(false, 5);
        character->setWorking(false);
        emit workEnd();
    }
    if (event->timerId() == timer_id_cook)
    {
        qDebug() << "炒菜工作结束\n";
        character->heartUpDown(false, 5);
        character->setWorking(false);
        emit workEnd();
    }
    if (event->timerId() == timer_id_wash)
    {
        qDebug() << "洗碗工作结束\n";
        character->heartUpDown(false, 5);
        character->setWorking(false);
        emit workEnd();
    }
}

void THousework::stop_working()
{
    killTimer(timer_id_clean);
    killTimer(timer_id_cook);
    killTimer(timer_id_wash);
}

bool THousework::clean()
{
    bool b;
    if (!character->getWorking())
    {
        if (character->powerUpDown(true, 2))
        {
            character->setWorking(true);
            timer_id_clean = startTimer(210 * 1000);
            b = true;
        }
        else
        {
            qDebug() << "体力不足！\n";
            b = false;
        }
    }
    else
    {
        qDebug() << "正在工作中\n";
        b = false;
    }
    return b;
}

bool THousework::cook()
{
    bool b;
    if (!character->getWorking())
    {
        if (character->powerUpDown(true, 2))
        {
            character->setWorking(true);
            timer_id_clean = startTimer(210 * 1000);
            b = true;
        }
        else
        {
            qDebug() << "体力不足！\n";
            b = false;
        }
    }
    else
    {
        qDebug() << "正在工作中\n";
        b = false;
    }
    return b;
}

bool THousework::wash()
{
    bool b;
    if (!character->getWorking())
    {
        if (character->powerUpDown(true, 1))
        {
            character->setWorking(true);
            timer_id_clean = startTimer(210 * 1000);
            b = true;
        }
        else
        {
            qDebug() << "体力不足！\n";
            b = false;
        }
    }
    else
    {
        qDebug() << "正在工作中\n";
        b = false;
    }
    return b;
}
