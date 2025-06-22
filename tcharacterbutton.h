#pragma once

#include <QToolButton>

class TCharacter;

class TCharacterButton  : public QToolButton
{
    Q_OBJECT


private:
    TCharacter &character_;

public:
    TCharacterButton(QWidget *parent, TCharacter &character);
    ~TCharacterButton();
    void enterEvent(QEnterEvent* event) override;
};
