#pragma once

#include <QWidget>
#include <vector>
#include <map>

#include "defines.h"
#include "tgood.h"

class TShop : public QWidget
{
    Q_OBJECT

    std::vector<int> timer_id_stock;
    std::vector<TGood> goods_;
    std::map<QString, int> shop_map_;

public:
    TShop(QWidget* parent);
    TShop(const TShop& shop);
    ~TShop() override;
    void setValue(Game::items items, int num_, int price_, int weight_up_, int power_up_, int interval_time_); // 设置初始值
    int get_num(Game::items items);
    bool sell(Game::items items, int sell_num, TCharacter& character); // 卖出
    TGood& get_good(Game::items items);
    void do_stockWithGoods(Game::items items); // 进货
    void timerEvent(QTimerEvent* event) override;

signals:
    void stock(Game::items item, int left); //进货信号
    void no_money(); // 没钱
    void sell_out(); // 商店无货
};

inline int TShop::get_num(const Game::items items)
{
    const QString string = to_string(items);
    return shop_map_[string];
}
