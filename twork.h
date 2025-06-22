#pragma once

#include <QWidget>
#include "tcharacter.h"

class TWork : public QWidget
{
    Q_OBJECT

    TCharacter* character;
    int timer_id_banzhuan;
    int timer_id_zuoban;
    bool isWorking; // 判断是否在工作

public:
    TWork(QWidget* parent, TCharacter* character_ = nullptr);
    ~TWork() override;
    void set_character(TCharacter* character_);
    bool banzhuan(); // 搬砖
    bool zuoban(); // 坐班
    void timerEvent(QTimerEvent* event) override;
    void stop_working();
    QString get_character_name() { return character->getData(Game::name).toString(); }

signals:
    void workEnd();
};
