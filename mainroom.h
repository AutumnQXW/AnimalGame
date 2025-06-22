#pragma once

#include <QWidget>

#include "defines.h"
#include "ui_mainroom.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainroomClass; };
QT_END_NAMESPACE

class Mainroom : public QWidget
{
    Q_OBJECT

public:
    Mainroom(QWidget *parent = nullptr);
    ~Mainroom();
    const Game::backgrounds backgrounds_id;

private:
    Ui::MainroomClass *ui;

public:
    void paintEvent(QPaintEvent* event) override;
};
