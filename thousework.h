#pragma once

#include <QWidget>
#include "tcharacter.h"

class THousework : public QWidget
{
    Q_OBJECT

    //bool isWorking;
    int timer_id_clean;
    int timer_id_cook;
    int timer_id_wash;
    TCharacter* character;

public:
    THousework(QWidget* parent, TCharacter* character_ = nullptr);
    ~THousework() override;
    void set_character(TCharacter* character_);
    void timerEvent(QTimerEvent* event) override;
    void stop_working();
    bool clean();
    bool cook();
    bool wash();
    QString get_character_name() { return character->getData(Game::name).toString(); }

signals:
    void workEnd();
};
