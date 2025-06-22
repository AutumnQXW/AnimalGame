#include "tcharacter.h"

#include <iostream>
#include <QApplication>
#include <QMessageBox>
#include <QTimer>

void TCharacter::do_game_end()
{
    QMessageBox::critical(this, "信息", "人物被饿昏了！游戏结束！");
    emit game_end_event();
    //QApplication* app;
    //app->quit();
}

void TCharacter::do_power_decrease()
{
    power -= 1;
}

TCharacter::TCharacter(QWidget* parent, int weight_, int heart_, int money_, const QString& name_)
    : QWidget(parent)
{
    weight = weight_;
    power = 10;
    heart = heart_;
    exp = 0;
    money = money_;
    level = 1;
    max_power = 10;
    isWorking = false;
    name = name_;
    canWork = true;
    qDebug() << "character构造函数被调用\n";
    //timer_end = new QTimer(this);
    timer_powerDec = new QTimer(this);
    //timer_end->setTimerType(Qt::CoarseTimer);
    timer_powerDec->setTimerType(Qt::CoarseTimer);
    timer_powerDec->setSingleShot(false);
    timer_powerDec->start(times::power_decrease_time * 1000); // 体力计时，每120s下降1
    //connect(timer_end, &QTimer::timeout, this, &TCharacter::do_game_end);
    connect(timer_powerDec, &QTimer::timeout, this, &TCharacter::do_power_decrease);
    // 状态监控定时
    timer_id_monitor = startTimer(100);
}

TCharacter::TCharacter(const TCharacter& character)
    : timer_id_monitor(character.timer_id_monitor)
      , timer_powerDec(new QTimer(this))
{
    weight = character.weight;
    power = character.power;
    heart = character.heart;
    exp = character.exp;
    money = character.money;
    level = character.level;
    max_power = character.max_power;
    isWorking = character.isWorking;
    name = character.name;
}

TCharacter::TCharacter(): weight(0), power(0), heart(0), exp(0), money(0), level(0),
                          timer_id_monitor(0),
                          timer_powerDec(new QTimer(this)),
                          max_power(0),
                          isWorking(false)
{
}

TCharacter::~TCharacter()
{
    //delete timer_end;
    delete timer_powerDec;
}

QVariant TCharacter::getData(Game::data data)
{
    switch (data)
    {
    case Game::name:
        return name;
    case Game::weight:
        return weight;
    case Game::power:
        return power;
    case Game::heart:
        return heart;
    case Game::exp:
        return exp;
    case Game::level:
        return level;
    case Game::money:
        return money;
    case Game::status:
        QString status_text;
        Game::status_flags flags;
        flags = statusJudge();
        if (flags.testFlag(Game::fat))
        {
            status_text.append("fat");
        }
        if (flags.testFlag(Game::hungry))
        {
            status_text.append(status_text.isEmpty() ? "hungry" : " and hungry");
        }
        if (flags.testFlag(Game::tired))
        {
            status_text.append(status_text.isEmpty() ? "tired" : " and tired");
        }
        if (flags.testFlag(Game::none))
        {
            status_text.append(status_text.isEmpty() ? "none" : "");
        }
        return status_text;
    }
}

void TCharacter::weightUpDown(bool isDecrease, int i)
{
    isDecrease ? weight -= i : weight += i;
    statusJudge();
    emit data_changed_event(*this, Game::weight, weight);
}

bool TCharacter::powerUpDown(bool isDecrease, int i)
{
    bool ok = false;
    if (!isDecrease)
    {
        if (power == max_power)
        {
            QMessageBox::critical(this, "注意", "体力值已经到达上限！");
            timer_powerDec->stop();
            timer_powerDec->start(times::power_decrease_time * 1000);
            ok = true;
        }
        else if (power + i > max_power && power < max_power)
        {
            qDebug() << "体力值溢出！\n";
            power = max_power;
            timer_powerDec->stop();
            timer_powerDec->start(times::power_decrease_time * 1000);
            ok = true;
        }
        else
        {
            power += i;
            ok = true;
        }
    }
    else
    {
        if (power >= i)
        {
            power -= i;
            ok = true;
        }
        else if (power < i)
        {
            qDebug() << "体力不足！\n";
            ok = false;
        }
    }
    if (power < 0)
    {
        power = 0;
    }
    statusJudge();
    emit data_changed_event(*this, Game::power, power);
    return ok;
}

void TCharacter::heartUpDown(bool isDecrease, int i)
{
    isDecrease ? heart -= i : heart += i;
    if (heart >= level * 10)
    {
        moneyUpDown(false, 150);
    }
    emit data_changed_event(*this, Game::heart, heart);
}

void TCharacter::expUpDown(int i, bool isDecrease)
{
    if (!isDecrease)
    {
        if (exp + i >= 50 && level < 6)
        {
            level++;
            moneyUpDown(false, 100);
            exp = exp + i - 50;
        }
        else if (level == 6)
        {
            qDebug() << "等级已经到达上限\n";
            exp = 50;
        }
        else if (exp + i < 50 && level < 6)
        {
            exp += i;
            emit level_up_event(level);
        }
    }
    else
    {
            exp -= i;
            if (exp < 0)
                exp = 0;
    }
    emit data_changed_event(*this, Game::exp, exp);
}

void TCharacter::levelUpDown(bool isDecrease, int i) // 仅测试用
{
    if (!isDecrease)
    {
        level += i;
    }
    else
    {
        level -= i;
        if (level < 0)
            level = 0;
    }
    emit level_up_event(level);
}

bool TCharacter::moneyUpDown(bool isDecrease, int i)
{
    bool ok = false;
    if (money - i < 0 && isDecrease)
    {
        qDebug() << "金钱不足！\n";
        ok = false;
    }
    if (money - i >= 0 && isDecrease)
    {
        money -= i;
        qDebug() << QString("支出成功，余额：%1").arg(money);
        ok = true;
    }
    if (!isDecrease)
    {
        qDebug() << QString("\n挣钱了！\n\t原金钱数：%1\n\t现金钱数：%2").arg(money).arg(money + i);
        money += i;
        ok = true;
    }
    emit data_changed_event(*this, Game::money, money);
    return ok;
}

void TCharacter::setWorking(bool set)
{
    isWorking = set;
}

void TCharacter::help(TCharacter& character)
{
    if (isWorking == false)
    {
        powerUpDown(true, 5);
        character.powerUpDown(false, 2);
        heartUpDown(false, 10);
    }
}

Game::status_flags TCharacter::statusJudge()
{
    Game::status_flags flags = Game::none;
    bool flag = false;
    if (power == 0)
    {
        emit hungry_event();
        flags |= Game::hungry;
        flag = true;
    }
    if (weight >= FAT_CRITICAL)
    {
        emit fat_event();
        flags |= Game::fat;
        flag = true;
    }
    if (power <= TIRED_CRITICAL)
    {
        emit tired_event();
        flags |= Game::tired;
        flag = true;
    }
    if (!flag)
    {
        emit none_event();
    }
    return flags;
}

bool TCharacter::help(TCharacter& helper, TCharacter& helpee)
{
    if (!helper.powerUpDown(true, 2))
    {
        return false;
    }
    helper.heartUpDown(false, HEART_HELP);
    helpee.powerUpDown(false, 2);
    return true;
}

void TCharacter::do_timer_reset(const int msec) const
{
    timer_powerDec->setInterval(msec);
}

void TCharacter::timerEvent(QTimerEvent* event)
{
    //if (event->timerId() == timer_id_monitor)
    //{
    //    statusJudge();
    //}
}

//Game::status_flags static_statusJudge(const TCharacter& character)
//{
//    Game::status_flags flags = Game::none;
//    if (character.power == 0)
//    {
//        flags |= Game::hungry;
//    }
//    if (character.weight >= FAT_CRITICAL)
//    {
//        flags |= Game::fat;
//    }
//    if (character.power <= TIRED_CRITICAL)
//    {
//        flags |= Game::tired;
//    }
//    return flags;
//}
