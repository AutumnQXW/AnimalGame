#pragma once

#include <QWidget>
#include "defines.h"
#include "tstatus.h"


class TCharacter : public QWidget
{
    Q_OBJECT

protected:
    int weight; // 体重，单位kg
    int power; // 体力
    int heart; // 爱心
    int exp; // 经验
    int money; // 金钱
    int level; // 等级
    QString name; // 名字
    //TStatus status_;

private:
    int timer_id_monitor; //状态监控
    //QTimer* timer_end;
    QTimer* timer_powerDec;
    int max_power; // 经验值上限
    bool isWorking;
    bool canWork;

public slots:
    void do_game_end();
    void do_power_decrease();
    void do_timer_reset(int msec) const;
    void timerEvent(QTimerEvent* event) override;

public:
    TCharacter(QWidget* parent, int weight_, int heart_, int money_, const QString& name_);
    TCharacter(const TCharacter& character);
    TCharacter();
    ~TCharacter() override;
    QVariant getData(Game::data data);
    void weightUpDown(bool isDecrease, int i); // 体重上升、下降函数
    bool powerUpDown(bool isDecrease, int i); // 体力上升、下降函数
    void heartUpDown(bool isDecrease, int i); // 爱心上升、下降函数
    void expUpDown(int i, bool isDecrease = false); // 经验上升及升级函数
    void levelUpDown(bool isDecrease, int i);
    bool moneyUpDown(bool isDecrease, int i); // 金钱上升、下降函数
//    static friend Game::status_flags static_statusJudge(const TCharacter& character); // 状态判断函数
    void setWorking(bool set);
    constexpr bool getWorking() const;
    void help(TCharacter& character);
    Game::status_flags statusJudge();
    static bool help(TCharacter& helper, TCharacter& helpee);
    constexpr bool &set_canWork();

signals:
    void game_end_event();
    void fat_event();
    void tired_event();
    void hungry_event();
    void none_event();
    void data_changed_event(const TCharacter &character, Game::data data, int value);
    void level_up_event(int level);
};

constexpr bool TCharacter::getWorking() const
{
    return isWorking;
}

constexpr bool& TCharacter::set_canWork()
{
    return canWork;
}
