#include "tstatus.h"

#include <QApplication>
#include <QTimer>
#include "tcharacter.h"

//int TStatus::num_alert = 0;
QVector<QString> TStatus::name_list_{};
TStatus::TStatus(TCharacter &character, QWidget *parent)
    : QWidget(parent),
    character_(character)
{
    //timer_ = new QTimer(this);
    /*timer_->setSingleShot(true);
    timer_->setTimerType(Qt::CoarseTimer);
    connect(timer_, &QTimer::timeout, character_, &TCharacter::do_game_end);*/

    connect(this, &TStatus::fatEvent, &character_, &TCharacter::do_timer_reset);
    connect(&character_, &TCharacter::fat_event, this, &TStatus::fat);
    connect(&character_, &TCharacter::tired_event, this, &TStatus::tired);
    connect(&character_, &TCharacter::hungry_event, this, &TStatus::hungry);
    connect(&character_, &TCharacter::none_event, this, &TStatus::none);

    //timer_id_recovery = startTimer(100);
}

TStatus::TStatus(const TStatus& status)
    : timer_id_alert(status.timer_id_alert)
      //, timer_id_recovery(status.timer_id_recovery)
      , character_(status.character_)
{
}

TStatus::~TStatus()
{
    //delete timer_;
}

void TStatus::alert()
{
    QApplication::beep();
    timer_id_alert = startTimer(10 * 1000);
    if (name_list_.isEmpty()) // 若姓名表为空则添加姓名后直接退出
    {
        name_list_.emplace_back( character_.getData(Game::name).toString() );
        return;
    }

    auto f = [this](const QVector<QString> &names)
        {
            for (auto &name : names)
            {
                if (name == character_.getData(Game::name).toString())
                    return true;
            }
        return false;
        };
    if (!f(name_list_)) // 判断名字是否相同，避免num_alert意外自加
    {
        name_list_.emplace_back(character_.getData(Game::name).toString());
    }
    if (name_list_.length() == 3)
    {
        //timer_->stop();
        character_.do_game_end();
    }
}

void TStatus::hungry()
{
    alert();
    // 发送信息
}

void TStatus::fat()
{
    times::power_decrease_time = POWER_TIME_FAT;
    emit fatEvent(times::power_decrease_time * 1000);
}

void TStatus::tired()   // 无法进行活动
{
    character_.set_canWork() = false;
    emit tiredEvent();
}

void TStatus::none()
{
    killTimer(timer_id_alert);
    emit noneEvent();
    QVector<QString>::const_iterator iterator = name_list_.begin();
    for (QVector<QString>::const_iterator i = iterator; i < name_list_.end(); ++i)
    {
        if (*i == character_.getData(Game::name).toString())
        {
            name_list_.erase(i);
        }
    }
}

void TStatus::timerEvent(QTimerEvent* event)
{
    //if (event->timerId() == timer_id_recovery)
    //{
    //    if (character_.statusJudge().testFlag(Game::fat))
    //    {
    //        fat();
    //        qDebug() << "人物进入肥胖状态\n";
    //    }
    //    if(character_.statusJudge().testFlag(Game::hungry))
    //    {
    //        hungry();
    //        qDebug() << "人物进入饥饿状态\n";
    //    }
    //    if(character_.statusJudge().testFlag(Game::tired))
    //    {
    //        tired();
    //        qDebug() << "人物进入疲惫状态\n";
    //    }
    //    if(character_.statusJudge() == Game::none)
    //    {
    //        killTimer(timer_id_alert);
    //        character_.set_canWork() = true;
    //        qDebug() << "人物状态清除\n";
    //    }
    //}
    if (event->timerId() == timer_id_alert)
    {
        character_.do_game_end();
    }
}
