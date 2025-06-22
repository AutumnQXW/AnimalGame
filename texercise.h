#pragma once

#include <QWidget>

#include "tcharacter.h"

class TExercise : public QWidget
{
    Q_OBJECT

    int timer_id_run;
    int timer_id_other;
    TCharacter* character;
    //bool isExercising;

public:
    TExercise(QWidget* parent, TCharacter* character_ = nullptr);
    ~TExercise() override;
    void set_character(TCharacter* character_);
    bool run();
    bool other();
    void timerEvent(QTimerEvent* event) override;
    void stop_working();
    QString get_character_name() { return character->getData(Game::name).toString(); }

signals:
    void workEnd();
};
