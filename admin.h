#pragma once

#include <QWidget>
#include "ui_admin.h"
#include "defines.h"

QT_BEGIN_NAMESPACE
namespace Ui { class adminClass; };
QT_END_NAMESPACE

class admin : public QWidget
{
    Q_OBJECT

public:
    admin(QWidget *parent = nullptr);
    ~admin();

private:
    Ui::adminClass *ui;

public slots:
    void on_btnWeight_clicked();
    void on_btnPower_clicked();
    void on_btnHeart_clicked();
    void on_btnExp_clicked();
    void on_btnMoney_clicked();
    void on_btnLevel_clicked();
    void on_btnStopWork_clicked();

signals:
    void data_change(Game::data data, bool is_decrease, int value);
    void stop_work();
};
