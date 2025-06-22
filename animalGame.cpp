#include "animalGame.h"
#include "test.h"
#include "admin.h"
#include <QTimer>
#include <QToolButton>
#include <QVBoxLayout>
#include <QPainter>
#include <QWidget>
#include <QPropertyAnimation>
#include <QThread>
#include <QInputDialog>
#include <QMessageBox>

animalGame::animalGame(QMainWindow *parent)
    : QMainWindow(parent)
      , ui(new Ui::animalGameClass())
      , mainroom_(new Mainroom())
      , park_(new park())
      , shop_background_(new shop_background())
      , gym_(new gym())
      , zuoban_(new zuoban())
      , banzhuan_(new banzhuan())

      , rabbit_character_(new TCharacter(nullptr, 10, 0, 100, "小兔子"))
      , dog_character_(new TCharacter(nullptr, 12, 0, 100, "小狗"))
      , cat_character_(new TCharacter(nullptr, 10, 0, 150, "小猫"))
      , p_character_(nullptr)

      , btn_rabbit_(new TCharacterButton(nullptr, *rabbit_character_))
      , btn_dog_(new TCharacterButton(nullptr, *dog_character_))
      , btn_cat_(new TCharacterButton(nullptr, *cat_character_))
      , btn_pointer_(nullptr)

      , rabbit_status_(new TStatus(*rabbit_character_))
      , dog_status_(new TStatus(*dog_character_))
      , cat_status_(new TStatus(*cat_character_))

      , action_(nullptr)
      , shop_(this)
      , exercise_(this)
      , work_(this)

      , housework_(new THousework(this))
      , status_widget_(new TAnimWidget(this))
      , label_(new QLabel(status_widget_))
{
    ui->setupUi(this);
    this->setWindowState(Qt::WindowMaximized); // 窗口最大化显示
    QSize availableSize = QApplication::primaryScreen()->availableVirtualSize(); // 获取屏幕最大可占用尺寸
    this->setFixedSize(availableSize.width(), availableSize.height()); // 设置固定尺寸

    QString style_fat = QString::fromUtf8("QToolButton::menu-indicator{image:none;}\n"
                                          "QToolButton\n"
                                          "{\n"
                                          "   border-image: url(:/characters/images/%0_fat.png);\n"
                                          "   border-radius: 70px;\n"
                                          "   min-height: 140px;\n"
                                          "   min-width: 140px;\n"
                                          "}\n");
    QString style_tired = QString::fromUtf8("QToolButton::menu-indicator{image:none;}\n"
                                          "QToolButton\n"
                                          "{\n"
                                          "   border-image: url(:/characters/images/%0_tired.png);\n"
                                          "   border-radius: 70px;\n"
                                          "   min-height: 140px;\n"
                                          "   min-width: 140px;\n"
                                          "}\n");
    QString style_hungry = QString::fromUtf8("QToolButton::menu-indicator{image:none;}\n"
                                          "QToolButton\n"
                                          "{\n"
                                          "   border-image: url(:/characters/images/%0_hungry.png);\n"
                                          "   border-radius: 70px;\n"
                                          "   min-height: 140px;\n"
                                          "   min-width: 140px;\n"
                                          "}\n");
    QString style = QString::fromUtf8("QToolButton::menu-indicator{image:none;}\n"
                                      "QToolButton:!hover\n"
                                      "{\n"
                                      "   border-image: url(:/characters/images/%0.png);\n"
                                      "   border-radius: 70px;\n"
                                      "   min-height: 140px;\n"
                                      "   min-width: 140px;\n"
                                      "}\n"
                                      "QToolButton:hover\n"
                                      "{\n"
                                      "   border-image: url(:/characters/images/%0_happy.png);\n"
                                      "   border-radius: 70px;\n"
                                      "   min-height: 140px;\n"
                                      "   min-width: 140px;\n"
                                      "}");


    // 信号/槽连接
    exercise_.setObjectName("exercise");
    work_.setObjectName("work");
    housework_.setObjectName("housework");
    connect(&exercise_, &TExercise::workEnd, this, &animalGame::do_workEnd);
    connect(&work_, &TWork::workEnd, this, &animalGame::do_workEnd);
    connect(&housework_, &THousework::workEnd, this, &animalGame::do_workEnd);

    connect(&shop_, &TShop::stock, this, &animalGame::do_stock);
    connect(&shop_, &TShop::no_money, this, &animalGame::do_no_money);
    connect(&shop_, &TShop::sell_out, this, &animalGame::do_sell_out);

    connect(rabbit_status_, &TStatus::fatEvent, this, [=]()
    {
        btn_rabbit_->setStyleSheet(style_fat.arg("rabbit"));
    });
    connect(dog_status_, &TStatus::fatEvent, this, [=]()
    {
        btn_dog_->setStyleSheet(style_fat.arg("dog"));
    });
    connect(cat_status_, &TStatus::fatEvent, this, [=]()
    {
        btn_cat_->setStyleSheet(style_fat.arg("cat"));
    });

    connect(rabbit_status_, &TStatus::tiredEvent, this, [=]()
    {
        btn_rabbit_->setStyleSheet(style_tired.arg("rabbit"));
    });
    connect(dog_status_, &TStatus::tiredEvent, this, [=]()
    {
        btn_dog_->setStyleSheet(style_tired.arg("dog"));
    });
    connect(cat_status_, &TStatus::tiredEvent, this, [=]()
    {
        btn_cat_->setStyleSheet(style_tired.arg("cat"));
    });

    connect(rabbit_status_, &TStatus::hungryEvent, this, [=]()
    {
        btn_rabbit_->setStyleSheet(style_hungry.arg("rabbit"));
    });
    connect(dog_status_, &TStatus::hungryEvent, this, [=]()
    {
        btn_dog_->setStyleSheet(style_hungry.arg("dog"));
    });
    connect(cat_status_, &TStatus::hungryEvent, this, [=]()
    {
        btn_cat_->setStyleSheet(style_hungry.arg("cat"));
    });

    connect(rabbit_status_, &TStatus::noneEvent, this, [=]()
    {
        btn_rabbit_->setStyleSheet(style.arg("rabbit"));
    });
    connect(dog_status_, &TStatus::noneEvent, this, [=]()
    {
        btn_dog_->setStyleSheet(style.arg("dog"));
    });
    connect(cat_status_, &TStatus::noneEvent, this, [=]()
    {
        btn_cat_->setStyleSheet(style.arg("cat"));
    });

    // 物品初始化
    item_map_.insert(std::pair(QString("面包"), Game::bread));
    item_map_.insert(std::pair(QString("午餐肉"), Game::spam));
    item_map_.insert(std::pair(QString("汉堡包"), Game::hamburger));
    shop_.setValue(Game::items::bread, 10, 50, 1, 5, 60);
    shop_.setValue(Game::items::spam, 5, 100, 2, 6, 90);
    shop_.setValue(Game::items::hamburger, 5, 200, 3, 7, 120);

    // tabwidget初始化

    btn_rabbit_->setStyleSheet(style.arg("rabbit"));
    btn_cat_->setStyleSheet(style.arg("cat"));
    btn_dog_->setStyleSheet(style.arg("dog"));

    setMenu(btn_rabbit_);
    setMenu(btn_cat_);
    setMenu(btn_dog_);

    QVector<QVBoxLayout *> layouts;
    for (int i = 0; i < 6; i++)
    {
        layouts.push_back(new QVBoxLayout(this));
    }
    layouts[static_cast<int>(Game::backgrounds::mainroom)]->addWidget(btn_rabbit_);
    layouts[static_cast<int>(Game::backgrounds::mainroom)]->addWidget(btn_cat_);
    layouts[static_cast<int>(Game::backgrounds::mainroom)]->addWidget(btn_dog_);

    connect(btn_rabbit_, &TCharacterButton::clicked, this, [this]()
    {
        p_character_ = rabbit_character_;
        btn_pointer_ = btn_rabbit_;
        btn_rabbit_->showMenu();
    });
    connect(btn_cat_, &TCharacterButton::clicked, this, [this]()
    {
        p_character_ = cat_character_;
        btn_pointer_ = btn_cat_;
        btn_cat_->showMenu();
    });
    connect(btn_dog_, &TCharacterButton::clicked, this, [this]()
    {
        p_character_ = dog_character_;
        btn_pointer_ = btn_dog_;
        btn_dog_->showMenu();
    });

    ui->tabWidget->addTab(mainroom_, "主房间");
    ui->tabWidget->addTab(park_, "公园");
    ui->tabWidget->addTab(shop_background_, "商店");
    ui->tabWidget->addTab(gym_, "健身房");
    ui->tabWidget->addTab(banzhuan_, "工地");
    ui->tabWidget->addTab(zuoban_, "办公室");
    mainroom_->setLayout(layouts.at(static_cast<int>(Game::backgrounds::mainroom)));
    park_->setLayout(layouts.at(static_cast<int>(Game::backgrounds::park)));
    shop_background_->setLayout(layouts.at(static_cast<int>(Game::backgrounds::shop)));
    gym_->setLayout(layouts.at(static_cast<int>(Game::backgrounds::gym)));
    banzhuan_->setLayout(layouts.at(static_cast<int>(Game::backgrounds::banzhuan)));
    zuoban_->setLayout(layouts.at(static_cast<int>(Game::backgrounds::zuoban)));

    //提示窗口
    status_widget_->setStyleSheet(QString::fromUtf8("TAnimWidget\n"
                                                    "{\n"
                                                    "min-width:371px;\n"
                                                    "min-height:131px;\n"
                                                    "background-color: rgb(255, 164, 67);\n"
                                                    "border-width:10px;\n"
                                                    "border-style:solid;\n"
                                                    "border-color:rgb(255, 215, 95)\n"
                                                    "}\n"
                                                    "QLabel\n"
                                                    "{\n"
                                                    "	font: 20pt \"\351\273\221\344\275\223\";\n"
                                                    "	border-color: rgba(0,0,0,0);\n"
                                                    "	background-color: rgba(0,0,0,0)\n"
                                                    "}")); // 提示窗口样式表

    status_widget_->raise();
    status_widget_flag_ = true;
    label_->setText("abc");
    label_->setAlignment(Qt::AlignCenter);
    QVBoxLayout *layout1 = new QVBoxLayout(status_widget_);
    layout1->addWidget(label_);
    status_widget_->setLayout(layout1);

    // 移动提示窗口使其隐藏
    QRect a = this->rect();
    status_widget_->move(this->rect().width() + status_widget_->width(), this->rect().height() + status_widget_->height());
    status_widget_->setWindowFlags(Qt::Widget);

}

animalGame::~animalGame()
{
    delete ui;
    delete mainroom_;
    delete park_;
    delete shop_background_;
    delete gym_;
    delete zuoban_;
    delete banzhuan_;
    delete rabbit_character_;
    delete dog_character_;
    delete cat_character_;
    delete rabbit_status_;
    delete dog_status_;
    delete cat_status_;
    delete status_widget_;
}

void animalGame::on_actionTest_triggered()
{
    test = new Test(this);
    test->setWindowFlags(test->windowFlags());
    test->show();
}

void animalGame::on_actionAdmin_triggered()
{
    a = new admin(this);
    a->setWindowFlags(Qt::Window);
    connect(a, &admin::data_change, test, &Test::do_dataChange);
    connect(a, &admin::stop_work, test, &Test::do_stopWork);
    a->show();
}

void animalGame::setMenu(TCharacterButton* button)
{
    QMenu *menu = new QMenu();
    QAction *action_eat = new QAction("吃东西");
    QAction *action_buy = new QAction("购买");
    QAction *action_work = new QAction("工作");
    QAction *action_exercise = new QAction("锻炼");
    QAction *action_housework = new QAction("做家务");
    QAction *action_help = new QAction("帮助别人");

    connect(action_eat, &QAction::triggered, this, &animalGame::on_action_eat_triggered);
    connect(action_buy, &QAction::triggered, this, &animalGame::on_action_buy_triggered);
    connect(action_work, &QAction::triggered, this, &animalGame::on_action_work_triggered);
    connect(action_exercise, &QAction::triggered, this, &animalGame::on_action_exercise_triggered);
    connect(action_housework, &QAction::triggered, this, &animalGame::on_action_housework_triggered);
    connect(action_help, &QAction::triggered, this, &animalGame::on_action_help_triggered);

    QList<QAction *> list;
    list.append(action_eat);
    list.append(action_buy);
    list.append(action_work);
    list.append(action_exercise);
    list.append(action_housework);
    list.append(action_help);
    menu->addActions(list);
    button->setMenu(menu);
}

void animalGame::on_action_buy_triggered()
{
    btn_pointer_->setParent(shop_background_);
    shop_background_->layout()->addWidget(btn_pointer_);
    if (!btn_pointer_->menu()->actions().contains(action_)) // 检测是否已经有回家action
        action_ = btn_pointer_->menu()->addAction("回家", this, &animalGame::on_action_backHome_triggered);
    btn_pointer_->show();
    QStringList item_list;
    item_list << "面包" << "午餐肉" << "汉堡包";
    QString item = QInputDialog::getItem(this, "角色操作", QString("要购买哪个商品？"), item_list, 0, false);
    Game::items items = item_map_.find(item)->second;
    if (shop_.sell(items, 1, *p_character_))
    {
        label_->setText(
            QString("购买道具%1成功！\n商店剩余道具数：%2").arg(item).arg(shop_.get_num(items)));
        anim_label();
    }
}

void animalGame::on_action_exercise_triggered()
{

    if (!p_character_->set_canWork())
    {
        label_->setText("该角色处在劳累状态，无法开始任务");
        return;
    }
    exercise_.set_character(p_character_);
    QStringList exercise_list;
    exercise_list << "跑步" << "健身";
    QInputDialog input(this);
    input.setComboBoxItems(exercise_list);
    input.setComboBoxEditable(false);
    QString item = QInputDialog::getItem(this, "角色操作", QString("要进行哪项运动？"), exercise_list, 0, false);
    if (item == "跑步")
    {
        if (exercise_.run())
        {
            label_->setText("正在跑步。。。");
            btn_pointer_->setParent(park_);
            park_->layout()->addWidget(btn_pointer_);
            action_ = btn_pointer_->menu()->addAction("回家", this, &animalGame::on_action_backHome_triggered);
            action_->setCheckable(false);
            btn_pointer_->show();
        }
        else
            label_->setText("已有工作任务，请等待其它工作完成。。。");
    }
    else if (item == "健身")
    {
        if (exercise_.other())
        {
            label_->setText("正在健身。。。");
            btn_pointer_->setParent(gym_);
            gym_->layout()->addWidget(btn_pointer_);
            action_ = btn_pointer_->menu()->addAction("回家", this, &animalGame::on_action_backHome_triggered);
            btn_pointer_->show();
        }
        else
            label_->setText("已有工作任务，请等待其它工作完成。。。");
    }
    anim_label();
}

void animalGame::on_action_backHome_triggered()
{
    btn_pointer_->setParent(mainroom_);
    mainroom_->layout()->addWidget(btn_pointer_);
    btn_pointer_->menu()->removeAction(action_);
    btn_pointer_->show();
}

void animalGame::on_action_work_triggered()
{
    if (!p_character_->set_canWork())
    {
        label_->setText("该角色处在劳累状态，无法开始任务");
        return;
    }
    work_.set_character(p_character_);
    QStringList work_list;
    work_list << "坐班" << "搬砖";
    QInputDialog input(this);
    input.setComboBoxItems(work_list);
    input.setComboBoxEditable(false);
    QString item = QInputDialog::getItem(this, "角色操作", QString("要去打什么工？"), work_list, 0, false);
    if (item == "坐班")
    {
        if (work_.zuoban())
        {
            label_->setText("正在坐班。。。");
            btn_pointer_->setParent(zuoban_);
            zuoban_->layout()->addWidget(btn_pointer_);
            action_ = btn_pointer_->menu()->addAction("回家", this, &animalGame::on_action_backHome_triggered);
            btn_pointer_->show();
        }
        else
            label_->setText("已有工作任务，请等待其它工作完成。。。");
    }
    else if (item == "搬砖")
    {
        if (work_.banzhuan())
        {
            label_->setText("正在搬砖。。。");
            btn_pointer_->setParent(banzhuan_);
            banzhuan_->layout()->addWidget(btn_pointer_);
            action_ = btn_pointer_->menu()->addAction("回家", this, &animalGame::on_action_backHome_triggered);
            btn_pointer_->show();
        }
        else
            label_->setText("已有工作任务，请等待其它工作完成。。。");
    }
    anim_label();
}

void animalGame::on_action_help_triggered()
{
    QStringList help_list;
    help_list << "小猫" << "小狗" << "小兔子";
    help_list.removeOne(p_character_->getData(Game::name).toString());
    QInputDialog input(this);
    input.setComboBoxItems(help_list);
    input.setComboBoxEditable(false);
    QString item = QInputDialog::getItem(this, "角色操作", QString("要帮助谁？"), help_list, 0, false);
    if (item == "小猫")
    {
        TCharacter::help(*p_character_, *cat_character_);
    }
    else if (item == "小狗")
    {
        TCharacter::help(*p_character_, *dog_character_);
    }
    else if (item == "小兔子")
    {
        TCharacter::help(*p_character_, *rabbit_character_);
    }
    anim_label();
}

void animalGame::on_action_housework_triggered()
{
    if (!p_character_->set_canWork())
    {
        label_->setText("该角色处在劳累状态，无法开始任务");
        return;
    }
    housework_.set_character(p_character_);
    QStringList exercise_list;
    exercise_list << "洗碗" << "打扫卫生" << "炒菜";
    QInputDialog input(this);
    input.setComboBoxItems(exercise_list);
    input.setComboBoxEditable(false);
    QString item = QInputDialog::getItem(this, "角色操作", QString("要进行哪项家务？").arg(p_character_->getData(Game::name).toString()), exercise_list, 0, false);
    if (item == "洗碗")
    {
        if (housework_.wash())
        {
            label_->setText("正在洗碗。。。");
            btn_pointer_->setParent(mainroom_);
            mainroom_->layout()->addWidget(btn_pointer_);
            btn_pointer_->show();
        }
        else
            label_->setText("已有工作任务，请等待其它工作完成。。。");
    }
    else if (item == "打扫卫生")
    {
        if (housework_.clean())
        {
            label_->setText("正在打扫。。。");
            btn_pointer_->setParent(mainroom_);
            mainroom_->layout()->addWidget(btn_pointer_);
            btn_pointer_->show();
        }
        else
            label_->setText("已有工作任务，请等待其它工作完成。。。");
    }
    else if (item == "炒菜")
    {
        if (housework_.cook())
        {
            label_->setText("正在炒菜。。。");
            btn_pointer_->setParent(mainroom_);
            mainroom_->layout()->addWidget(btn_pointer_);
            btn_pointer_->show();
        }
        else
            label_->setText("已有工作任务，请等待其它工作完成。。。");
    }
    anim_label();
}

void animalGame::on_action_eat_triggered()
{
    QStringList food_list;
    food_list << "面包" << "汉堡包" << "午餐肉";
    QInputDialog input(this);
    input.setComboBoxItems(food_list);
    input.setComboBoxEditable(false);
    QString item = QInputDialog::getItem(this, "角色操作", QString("要吃点什么？").arg(p_character_->getData(Game::name).toString()), food_list, 0, false);
    if (item == "面包")
    {
        if (shop_.get_good(Game::bread).useItems(*p_character_))
            label_->setText(QString("%1使用成功，剩余%2个").arg(item).arg(shop_.get_good(Game::bread).get_num()));
        else
            label_->setText(QString("没有剩余%1了，先去买一个吧").arg(item));
    }
    if (item == "汉堡包")
    {
        if (shop_.get_good(Game::bread).useItems(*p_character_))
            label_->setText(QString("%1使用成功，剩余%2个").arg(item).arg(shop_.get_good(Game::hamburger).get_num()));
        else
            label_->setText(QString("没有剩余%1了，先去买一个吧").arg(item));
    }
    if (item == "午餐肉")
    {
        if (shop_.get_good(Game::bread).useItems(*p_character_))
            label_->setText(QString("%1使用成功，剩余%2个").arg(item).arg(shop_.get_good(Game::spam).get_num()));
        else
            label_->setText(QString("没有剩余%1了，先去买一个吧").arg(item));
    }
    anim_label();
}

void animalGame::do_workEnd()
{
    QObject *a = sender();
    QString s = a->objectName();
    QString name;
    if (s == "work")
    {
        name = work_.get_character_name();
        s = "工作";
    }
    else if (s == "exercise")
    {
        name = exercise_.get_character_name();
        s = "运动";
    }
    else if (s == "housework")
    {
        name = housework_.get_character_name();
        s = "家务";
    }
    label_->setText(QString("%1的%2任务已完成！").arg(name).arg(s));
    anim_label();

}

void animalGame::do_stopWork()
{
}

void animalGame::do_gameOver()
{
    QMessageBox::critical(this, "游戏失败", "小动物们都被饿晕了TwT\n游戏结束……");
    QApplication::quit();
}

void animalGame::do_stock(Game::items item, int left)
{
    QString string{ "物品%0在商店完成进货了！快来看看吧~\n目前该商品剩余：%1" };
    switch (item)
    {
    case Game::bread:
        label_->setText(string.arg("面包").arg(left));
    case Game::hamburger:
        label_->setText(string.arg("汉堡包").arg(left));
    case Game::spam:
        label_->setText(string.arg("午餐肉").arg(left));
    }
    anim_label();
}

void animalGame::do_no_money()
{
    label_->setText("哎呀，没钱了！先去赚点钱吧~");
    anim_label();
}

void animalGame::do_sell_out()
{
    label_->setText("卖完了！马上进货，稍等~");
    anim_label();
}

void animalGame::anim_label()
{
    status_widget_->eject_anim();
}

void animalGame::mouseDoubleClickEvent(QMouseEvent* event)
{
    status_widget_->eject_anim();
}

