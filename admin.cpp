#include "admin.h"

admin::admin(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::adminClass())
{
    ui->setupUi(this);
}

admin::~admin()
{
    delete ui;
}

void admin::on_btnWeight_clicked()
{
    int value = ui->spinBox->value();
    bool is = ui->checkBox->isChecked();
    emit data_change(Game::weight, is, value);
}

void admin::on_btnPower_clicked()
{
    int value = ui->spinBox_2->value();
    bool is = ui->checkBox_2->isChecked();
    emit data_change(Game::power, is, value);
}

void admin::on_btnHeart_clicked()
{
    int value = ui->spinBox_3->value();
    bool is = ui->checkBox_3->isChecked();
    emit data_change(Game::heart, is, value);
}

void admin::on_btnExp_clicked()
{
    int value = ui->spinBox_4->value();
    bool is = ui->checkBox_4->isChecked();
    emit data_change(Game::exp, is, value);
}

void admin::on_btnMoney_clicked()
{
    int value = ui->spinBox_5->value();
    bool is = ui->checkBox_5->isChecked();
    emit data_change(Game::money, is, value);
}

void admin::on_btnLevel_clicked()
{
    int value = ui->spinBox_6->value();
    bool is = ui->checkBox_6->isChecked();
    emit data_change(Game::level, is, value);
}

void admin::on_btnStopWork_clicked()
{
    emit stop_work();
}


