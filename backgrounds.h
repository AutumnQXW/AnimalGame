#pragma once

#include <QWidget>

#include "defines.h"

class Backgrounds  : public QWidget
{
    Q_OBJECT

protected:
    const Game::backgrounds backgrounds_id_;

public:
    Backgrounds(QWidget *parent, Game::backgrounds backgrounds);
    ~Backgrounds();
    void paintEvent(QPaintEvent* event) override = 0;
    constexpr Game::backgrounds getId() { return backgrounds_id_; }
};

class park : public Backgrounds
{
public:
    park(QWidget *parent = nullptr);
    ~park();
    void paintEvent(QPaintEvent* event) override;
};

class Mainroom : public Backgrounds
{
public:
    Mainroom(QWidget *parent = nullptr);
    ~Mainroom();
    void paintEvent(QPaintEvent* event) override;
};

class shop_background : public Backgrounds
{
public:
    shop_background(QWidget *parent = nullptr);
    ~shop_background();
    void paintEvent(QPaintEvent* event) override;
};

class zuoban : public Backgrounds
{
public:
    zuoban(QWidget *parent = nullptr);
    ~zuoban(){}
    void paintEvent(QPaintEvent* event) override;
};

class banzhuan : public Backgrounds
{
public:
    banzhuan(QWidget *parent = nullptr);
    ~banzhuan(){}
    void paintEvent(QPaintEvent* event) override;
};

class gym : public Backgrounds
{
public:
    gym(QWidget *parent = nullptr);
    ~gym(){}
    void paintEvent(QPaintEvent* event) override;
};