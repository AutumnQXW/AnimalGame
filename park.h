#pragma once

#include <QWidget>

#include "defines.h"
#include "ui_park.h"

QT_BEGIN_NAMESPACE
namespace Ui { class parkClass; };
QT_END_NAMESPACE

class park : public QWidget
{
    Q_OBJECT

public:
    park(QWidget *parent = nullptr);
    ~park();
    const Game::backgrounds backgrounds_id;

public:
    void paintEvent(QPaintEvent *event) override;

private:
    Ui::parkClass *ui;
};
