#pragma once

//#include <QtWidgets/QWidget>

#include <QtWidgets/QMainWindow>

// #include "ui_animalGame.h"

#include "ui_animalGame_mw.h"
#include "GameInclude.h"

class QLabel;
class admin;
class Test;
class QPropertyAnimation;
QT_BEGIN_NAMESPACE

namespace Ui
{
    class animalGameClass;
};

QT_END_NAMESPACE

class animalGame : public QMainWindow
{
    Q_OBJECT

public:
    animalGame(QMainWindow* parent = nullptr);
    ~animalGame() override;

private:
    Ui::animalGameClass* ui;
    Test *test;
    admin *a;

    Backgrounds *mainroom_;
    Backgrounds *park_;
    Backgrounds *shop_background_;
    Backgrounds *gym_;
    Backgrounds *zuoban_;
    Backgrounds *banzhuan_;

    TCharacter *rabbit_character_;
    TCharacter *dog_character_;
    TCharacter *cat_character_;

    TCharacter *p_character_; // 指向被按下的角色

    TCharacterButton *btn_rabbit_;
    TCharacterButton *btn_dog_;
    TCharacterButton *btn_cat_;
    TCharacterButton *btn_pointer_; // 指向被按下的按钮

    TStatus *rabbit_status_;
    TStatus *dog_status_;
    TStatus *cat_status_;

    QAction *action_;
    TShop shop_;
    TExercise exercise_;
    TWork work_;
    THousework housework_;
    std::map<QString, Game::items> item_map_;

    TAnimWidget *status_widget_;
    bool status_widget_flag_;
    QLabel *label_;
    QPropertyAnimation *propertyAnimation;

public slots:
    void on_actionTest_triggered();
    void on_actionAdmin_triggered();
    void on_action_buy_triggered();
    void on_action_exercise_triggered();
    void on_action_backHome_triggered();
    void on_action_work_triggered();
    void on_action_help_triggered();
    void on_action_housework_triggered();
    void on_action_eat_triggered();
    void do_workEnd();
    void do_stopWork();
    void do_gameOver();
    void do_stock(Game::items item, int left);
    void do_no_money();
    void do_sell_out();
    void anim_label(); // 播放label进出动画
    void mouseDoubleClickEvent(QMouseEvent* event) override;

public:
    void setMenu(TCharacterButton *button);
    
};
