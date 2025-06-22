#include "tshop.h"

#include <QTimerEvent>

#include "tcharacter.h"

TShop::TShop(QWidget* parent)
    : QWidget(parent)
      , timer_id_stock(ITEM_NUM + 1, 0)
      , goods_(ITEM_NUM + 1)
{
}

TShop::TShop(const TShop& shop)
{
    timer_id_stock = shop.timer_id_stock;
    goods_ = shop.goods_;
    shop_map_ = shop.shop_map_;
}

TShop::~TShop()
{
}

void TShop::setValue(Game::items items, int num_, int price_, int weight_up_, int power_up_, int interval_time_)
{
    goods_[items].setValue(price_, weight_up_, power_up_, interval_time_);
    timer_id_stock[items] = startTimer(interval_time_ * 1000);
    for (int i = 0; i < ITEM_NUM; ++i)
    {
        shop_map_.insert(std::pair<QString, int>(to_string(items), num_));
    }
}

bool TShop::sell(Game::items items, int sell_num, TCharacter &character)
{
    QString string = to_string(items);
    bool ok = false;
    if (sell_num <= shop_map_.at(string) && character.moneyUpDown(true, goods_.at(items).price * sell_num))
    {
        //shop_map_[string] -= sell_num;
        const auto iterator = shop_map_.find(string);
        iterator->second -= sell_num;
        goods_.at(items).num += sell_num;
        ok = true;
    }
    else if(!character.moneyUpDown(true, goods_.at(items).price * sell_num))
    {
        emit no_money();
        ok = false;
    }
    else if(sell_num > shop_map_.at(string))
    {
        emit sell_out();
        ok = false;
    }
    return ok;
}

TGood& TShop::get_good(Game::items items)
{
    return goods_[items];
}

void TShop::do_stockWithGoods(Game::items items) // 进货
{
    const QString string = to_string(items);
    shop_map_[string] += 2;
    qDebug() << "商店进货成功，目前商品数：" << shop_map_[string] << "\n";
    emit stock(items, shop_map_.at(string));

}

void TShop::timerEvent(QTimerEvent* event)
{
    if (event->timerId() == timer_id_stock[Game::bread])
    {
        do_stockWithGoods(Game::bread);
    }
    else if (event->timerId() == timer_id_stock[Game::hamburger])
    {
        do_stockWithGoods(Game::hamburger);
    }
    else if (event->timerId() == timer_id_stock[Game::spam])
    {
        do_stockWithGoods(Game::spam);
    }
}
