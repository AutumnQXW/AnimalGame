#include "tcharacterbutton.h"
#include <QToolTip>
#include <tcharacter.h>

TCharacterButton::TCharacterButton(QWidget *parent, TCharacter &character)
    : QToolButton(parent)
      , character_(character)
{}

TCharacterButton::~TCharacterButton()
{}

void TCharacterButton::enterEvent(QEnterEvent* event)
{
    QToolTip::showText(this->cursor().pos(), QString::fromUtf8("名称 = %0\n体重 = %1\n体力 = %2\n爱心 = %3\n经验 = %4\n等级 = %5\n金钱 = %6\n状态 = %7")
                       .arg(character_.getData(Game::data::name).toString())
                       .arg(character_.getData(Game::data::weight).toInt())
                       .arg(character_.getData(Game::data::power).toInt())
                       .arg(character_.getData(Game::data::heart).toInt())
                       .arg(character_.getData(Game::data::exp).toInt())
                       .arg(character_.getData(Game::data::level).toInt())
                       .arg(character_.getData(Game::data::money).toInt())
                       .arg(character_.getData(Game::data::status).toString()), this);
}
