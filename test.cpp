#include "test.h"

#include <iostream>
#include <stdexcept>

void Test::showEvent(QShowEvent* event)
{
    event->accept();
}

void Test::closeEvent(QCloseEvent* event)
{
    event->accept();
}

Test::Test(QWidget* parent)
    : QMainWindow(parent)
      , shop_(this)
      , exercise_(this, nullptr)
      , work_(this)
      , housework_(this)
      , ui(new Ui::TestClass())
{
    ui->setupUi(this);
    shop_.setValue(Game::items::bread, 10, 50, 1, 1, 60);
    shop_.setValue(Game::items::spam, 5, 100, 1, 3, 90);
    shop_.setValue(Game::items::hamburger, 5, 200, 1, 5, 120);
    ui->comboBoxItem->addItem(to_string(Game::items::bread));
    ui->comboBoxItem->addItem(to_string(Game::items::spam));
    ui->comboBoxItem->addItem(to_string(Game::items::hamburger));
    item_map_.insert(std::pair(0, Game::items::bread));
    item_map_.insert(std::pair(1, Game::items::spam));
    item_map_.insert(std::pair(2, Game::items::hamburger));
    connect(&exercise_, &TExercise::workEnd, this, &Test::do_workEnd);
    connect(&work_, &TWork::workEnd, this, &Test::do_workEnd);
    connect(&housework_, &THousework::workEnd, this, &Test::do_workEnd);
    connect(&shop_, &TShop::stock, this, &Test::do_stock);
    connect(&shop_, &TShop::no_money, this, &Test::do_no_money);
    connect(&shop_, &TShop::sell_out, this, &Test::do_sell_out);
    ui->comboBoxBackground->addItem("Mainroom");
    ui->comboBoxBackground->addItem("park");
}

Test::~Test()
{
    delete ui;
    if (mainroom_ != nullptr)
        delete mainroom_;
}

void Test::on_btnAddChara_clicked()
{
    static int num = 0;
    characters_.emplace_back(this, 10, 0, 0, QString("%0").arg(num));
    statuses_.emplace_back(characters_.at(num), this);
    ui->comboBoxChara->addItem(QString("character %0").arg(num)); // comboBox的index即是character的编号
    ui->comboBoxChara->setCurrentIndex(num);
    ui->comboBoxChara_Help->addItem(QString("character %0").arg(num)); // comboBox的index即是character的编号
    ui->comboBoxChara_Help->setCurrentIndex(num);
    connect(&characters_.at(num), &TCharacter::game_end_event, this, &Test::do_gameOver);
    num++;
}

void Test::on_btnStatus_clicked()
{
    try
    {
        TCharacter& character_(characters_.at(ui->comboBoxChara->currentIndex()));
        QString text =
            QString("name = %0\nweight = %1\npower = %2\nheart = %3\nexp = %4\nlevel = %5\nmoney = %6\nstatus = %7")
            .arg(character_.getData(Game::data::name).toString())
            .arg(character_.getData(Game::data::weight).toInt())
            .arg(character_.getData(Game::data::power).toInt())
            .arg(character_.getData(Game::data::heart).toInt())
            .arg(character_.getData(Game::data::exp).toInt())
            .arg(character_.getData(Game::data::level).toInt())
            .arg(character_.getData(Game::data::money).toInt())
            .arg(character_.getData(Game::data::status).toString());
        ui->plainTextEdit->appendPlainText(text);
    }
    catch (std::out_of_range& o)
    {
        ui->plainTextEdit->appendPlainText(QString("未添加角色！错误信息：%1").arg(o.what()));
        std::cerr << o.what();
    }
}

void Test::on_btnUse_clicked()
{
    try
    {
        TCharacter& character_(characters_.at(ui->comboBoxChara->currentIndex()));
        int index = ui->comboBoxItem->currentIndex();
        Game::items items = item_map_.find(index)->second;
        if (shop_.get_good(items).useItems(character_))
        {
            ui->plainTextEdit->appendPlainText(
                QString("使用道具%1成功，剩余道具数：%2").arg(to_string(items)).arg(shop_.get_good(items).get_num()));
        }
    }
    catch (std::out_of_range& o)
    {
        ui->plainTextEdit->appendPlainText(QString("未添加角色！错误信息：%1").arg(o.what()));
        std::cerr << o.what();
    }
}

void Test::on_btnOpenBackground_clicked()
{
    int index = ui->comboBoxBackground->currentIndex();
    switch (index)
    {
    case static_cast<int>(Game::backgrounds::mainroom):
        mainroom_ = new Mainroom(this);
        mainroom_->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint | Qt::Window);
        mainroom_->show();
        break;
    case static_cast<int>(Game::backgrounds::park):
        park_ = new park(this);
        park_->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint | Qt::Window);
        park_->show();
        break;
    }
}

void Test::do_workEnd()
{
    ui->plainTextEdit->appendPlainText("工作已完成");
}

void Test::do_dataChange(Game::data data, bool is_decrease, int value)
{
    try
    {
        TCharacter &character_(characters_.at(ui->comboBoxChara->currentIndex()));
        switch (data)
        {
        case Game::weight:
            character_.weightUpDown(is_decrease, value);
            break;
        case Game::power:
            character_.powerUpDown(is_decrease, value);
            break;
        case Game::heart:
            character_.heartUpDown(is_decrease, value);
            break;
        case Game::exp:
            character_.expUpDown(value, is_decrease);
            break;
        case Game::level:
            character_.levelUpDown(is_decrease, value);
            break;
        case Game::money:
            character_.moneyUpDown(is_decrease, value);
            break;
        default:
            break;
        }
    }
    catch (std::out_of_range &o)
    {
        ui->plainTextEdit->appendPlainText(QString("未添加角色！错误信息：%1").arg(o.what()));
        std::cerr << o.what();
    }
}

void Test::do_stopWork()
{
    try
    {
        TCharacter &character_(characters_.at(ui->comboBoxChara->currentIndex()));
        character_.setWorking(false);
        exercise_.stop_working();
        work_.stop_working();
        housework_.stop_working();
    }
    catch (std::out_of_range &o)
    {
        ui->plainTextEdit->appendPlainText(QString("未添加角色！错误信息：%1").arg(o.what()));
        std::cerr << o.what();
    }
}

void Test::do_gameOver()
{
    this->destroy();
}

void Test::do_stock(Game::items item)
{
    ui->plainTextEdit->appendPlainText(QString("%0进货完成，现有数量%1").arg(Game::to_string(item)).arg(shop_.get_num(item)));
}

void Test::do_no_money()
{
    ui->plainTextEdit->appendPlainText("钱不够了！");
}

void Test::do_sell_out()
{
    ui->plainTextEdit->appendPlainText("该商品已售罄！");
}

void Test::on_btnBuy_clicked()
{
    TCharacter &character_(characters_.at(ui->comboBoxChara->currentIndex()));
    int index = ui->comboBoxItem->currentIndex();
    Game::items items = item_map_.find(index)->second;
    if (shop_.sell(items, 1, character_))
    {
        ui->plainTextEdit->appendPlainText(
            QString("购买道具%1成功，商店剩余道具数：%2").arg(to_string(items)).arg(shop_.get_num(items)));
    }
}

void Test::on_btnItemNum_clicked()
{
    int index = ui->comboBoxItem->currentIndex();
    Game::items items = item_map_.find(index)->second;
    ui->plainTextEdit->appendPlainText(
        QString("%1持有数：%2，商店现有数：%3").arg(to_string(items)).arg(shop_.get_good(items).get_num()).arg(
            shop_.get_num(items)));
}

void Test::on_btnExercise_clicked()
{
    try
    {
        TCharacter& character_(characters_.at(ui->comboBoxChara->currentIndex()));
        if (!character_.set_canWork())
        {
            ui->plainTextEdit->appendPlainText("该角色处在劳累状态，无法开始任务");
            return;
        }
        exercise_.set_character(&character_);
        int index = ui->comboBoxWork->currentIndex();
        switch (index)
        {
        case Game::run:
            if (exercise_.run())
                ui->plainTextEdit->appendPlainText(QString("正在跑步。。。"));
            else
                ui->plainTextEdit->appendPlainText("已有工作任务，请等待其它工作完成。。。");
            break;
        case Game::other:
            if (exercise_.other())
                ui->plainTextEdit->appendPlainText(QString("正在运动。。。"));
            else
                ui->plainTextEdit->appendPlainText("已有工作任务，请等待其它工作完成。。。");
            break;
        default: break;
        }
    }
    catch (std::out_of_range& o)
    {
        ui->plainTextEdit->appendPlainText(QString("未添加角色！错误信息：%1").arg(o.what()));
        std::cerr << o.what();
    }
}

void Test::on_btnWork_clicked()
{
    try
    {
        TCharacter& character_(characters_.at(ui->comboBoxChara->currentIndex()));
        if (!character_.set_canWork())
        {
            ui->plainTextEdit->appendPlainText("该角色处在劳累状态，无法开始任务");
            return;
        }
        work_.set_character(&character_);
        int index = ui->comboBoxExercise->currentIndex();
        switch (index)
        {
        case Game::zuoban:
            if (work_.zuoban()) 
                ui->plainTextEdit->appendPlainText(QString("正在坐班。。。"));
            else
                ui->plainTextEdit->appendPlainText("已有工作任务，请等待其它工作完成。。。");
            break;
        case Game::banzhuan:
            if (work_.banzhuan())
                ui->plainTextEdit->appendPlainText(QString("正在搬砖。。。"));
            else
                ui->plainTextEdit->appendPlainText("已有工作任务，请等待其它工作完成。。。");
            break;
        }
    }
    catch (std::out_of_range& o)
    {
        ui->plainTextEdit->appendPlainText(QString("未添加角色！错误信息：%1").arg(o.what()));
        std::cerr << o.what();
    }
}

void Test::on_btnHelp_clicked()
{
    try
    {
        int index1{ui->comboBoxChara->currentIndex()}, index2{ui->comboBoxChara_Help->currentIndex()};
        if (index1 == index2)
        {
            ui->plainTextEdit->appendPlainText("不能帮助自己！");
            return;
        }
        TCharacter &character1{characters_.at(index1)}, &character2{characters_.at(index2)};
        if (TCharacter::help(character1, character2))
        {
            ui->plainTextEdit->appendPlainText(QString("%1帮助%2成功！%1爱心上升%3")
                                               .arg(character1.getData(Game::data::name).toString())
                                               .arg(character2.getData(Game::data::name).toString())
                                               .arg(HEART_HELP));
        }
        else
        {
            ui->plainTextEdit->appendPlainText("帮助失败");
        }
    }
    catch (std::out_of_range& o)
    {
        ui->plainTextEdit->appendPlainText(QString("未添加角色！错误信息：%1").arg(o.what()));
        std::cerr << o.what();
    }
}

void Test::on_btnHouseWork_clicked()
{
    try
    {
        TCharacter& character_(characters_.at(ui->comboBoxChara->currentIndex()));
        if (!character_.set_canWork())
        {
            ui->plainTextEdit->appendPlainText("该角色处在劳累状态，无法开始任务");
            return;
        }
        housework_.set_character(&character_);
        int index = ui->comboBoxHouseWork->currentIndex();
        switch (index)
        {
        case Game::clean:
            if (housework_.clean())
                ui->plainTextEdit->appendPlainText(QString("正在打扫。。。"));
            else
                ui->plainTextEdit->appendPlainText(QString("已有工作任务，请等待工作完成。。。"));
            break;
        case Game::cook:
            if (housework_.cook()) 
                ui->plainTextEdit->appendPlainText(QString("正在做饭。。。"));
            else
                ui->plainTextEdit->appendPlainText(QString("已有工作任务，请等待工作完成。。。"));
            break;
        case Game::wash:
            if (housework_.wash()) 
                ui->plainTextEdit->appendPlainText(QString("正在洗碗。。。"));
            else
                ui->plainTextEdit->appendPlainText(QString("已有工作任务，请等待工作完成。。。"));
            break;
        }
    }
    catch (std::out_of_range& o)
    {
        ui->plainTextEdit->appendPlainText(QString("未添加角色！错误信息：%1").arg(o.what()));
        std::cerr << o.what();
    }
}
