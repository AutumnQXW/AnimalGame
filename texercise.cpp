#include "texercise.h"

#include <QTimerEvent>

TExercise::TExercise(QWidget* parent, TCharacter* character_)
    : QWidget(parent),
      character(character_)
//isExercising(false)
{
    qDebug() << "TExercise初始化\n";
}

TExercise::~TExercise()
{
    qDebug() << "TExercise删除\n";
}

void TExercise::set_character(TCharacter* character_)
{
    character = character_;
}

bool TExercise::run()
{
    if (!character->getWorking())
    {
        if (character->powerUpDown(true, 3))
        {
            qDebug() << "run函数调用";
            character->setWorking(true);
            timer_id_run = startTimer(210 * 1000);
            character->weightUpDown(true, 5);
            return true;
        }
        else
        {
            qDebug() << "体力不足！\n";
            return false;
        }
    }
    else
    {
        qDebug() << "正在运动中！\n";
        return false;
    }
}

bool TExercise::other()
{
    if (!character->getWorking())
    {
        if (character->powerUpDown(true, 3))
        {
            qDebug() << "other函数调用";
            character->setWorking(true);
            timer_id_other = startTimer(210 * 1000);
            character->weightUpDown(true, 5);
            return true;
        }
        else
        {
            qDebug() << "体力不足！\n";
            return false;
        }
    }
    else
    {
        qDebug() << "正在运动中！\n";
        return false;
    }
}

void TExercise::timerEvent(QTimerEvent* event)
{
    if (event->timerId() == timer_id_run)
    {
        character->expUpDown(20);
        character->setWorking(false);
        emit workEnd();
    }
    if (event->timerId() == timer_id_other)
    {
        character->expUpDown(15);
        character->setWorking(false);
        emit workEnd();
    }
}

void TExercise::stop_working()
{
    killTimer(timer_id_other);
    killTimer(timer_id_run);
}
