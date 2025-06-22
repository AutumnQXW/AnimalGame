#pragma once

#include <QWidget>

class TCharacter;
class TShop;
class QTimer;

class TGood : public QWidget
{
    Q_OBJECT

protected:
    int num;
    int price;
    int weightUp; // 体重上升量
    int powerUp; // 体力上升量
    int intervalTime; // 间隔时间
    //QTimer* timer_;

public:
    friend TShop;
    TGood(QWidget* parent);
    TGood();
    TGood(const TGood& t_good);
    ~TGood() override;
    TGood& operator=(const TGood& good);
    void setValue(int price_, int weight_up_, int power_up_, int interval_time_); // 数量、价格、体重上升量、体力上升量、间隔时间
    bool useItems(TCharacter& character);
    constexpr int get_weightUp();
    constexpr int get_powerUp();
    constexpr int get_num();

    //public slots:
    //    void start_timer();
};

constexpr int TGood::get_weightUp()
{
    return weightUp;
}

constexpr int TGood::get_powerUp()
{
    return powerUp;
}

constexpr int TGood::get_num()
{
    return num;
}
