#include <iostream>
#include <thread>
#include "animalGame.h"
#include "defines.h"
#include "gametime.h"
int power_decrease_time = POWER_TIME;
class Status
{
private:
    static int num_alert;
    bool isEnd;

public:
    Status() : isEnd(false) {}
    void alert() // 该部分需要大修
    {
        /*操作界面报警代码*/
        bool isAlert{false};

        //auto f = [isAlert]() mutable -> void
        //{
        //    gameTime gt;
        //    while (1)
        //    {
        //        if (gt.get_duration() >= 60)
        //        {
        //            isAlert = true;
        //            break;
        //        }

        //        if (isAlert || num_alert == 3)
        //        {
        //            /*游戏结束*/
        //        }
        //    }
        //};
        //std::thread th(f);
        //th.detach();
        
    }
    void hungry() // 未完成
    {
        alert();
    }
    void fat()
    {
        power_decrease_time = POWER_TIME_FAT;
    }
    void tired()
    {
        /*无法进行活动*/
    }
};
int Status::num_alert = 0;
class Goods
{
protected:
    int num;
    int price;
    int weightUp;     // 体重上升量
    int powerUp;      // 体力上升量
    int intervalTime; // 间隔时间

public:
    Goods(int n, int pr, int w, int po, int i) // 数量、价格、体重上升量、体力上升量、间隔时间
    {
        num = n;
        price = pr;
        weightUp = w;
        powerUp = po;
        intervalTime = i;
    }

    void stockWithGoods() // 配合thread一起使用
    {
        num += 2;
    }
    int sell(int sellNum) // 1=成功卖出，0=未成功卖出
    {
        if (sellNum <= num)
        {
            num -= sellNum;
            return 1;
        }
        else
        {
            return 0;
        }
    }
    int get_weightUp()
    {
        return weightUp;
    }
    int get_powerUp()
    {
        return powerUp;
    }
};
class Shop
{
private:
    Goods powerCat;            // 帕瓦的猫
    Goods friedPorkWithGinger; // 生姜炒肉
    Goods yonezuKenshi;        // 米津玄师

public:
    friend class Character;
    Shop() : powerCat(10, 50, 1, 5, 180), friedPorkWithGinger(5, 100, 1, 3, 300), yonezuKenshi(5, 200, 1, 5, 360) {}
    Goods get_goods(int i)
    {
        switch (i)
        {
        case 1:
            return powerCat;
            break;

        case 2:
            return friedPorkWithGinger;
            break;

        case 3:
            return yonezuKenshi;
            break;

        default:
            break;
        }
    }
};
class Character
{
protected:
    float weight; // 体重，单位kg
    int power;    // 体力
    int heart;    // 爱心
    int exp;      // 经验
    int money;    // 金钱
    Status sta;
    std::string status_name;
    Shop sh;

public:
    Character(float a, int b, int c, int d, int e)
    {
        weight = a;
        power = b;
        heart = c;
        exp = d;
        money = e;
        status_name = "none";
    }
    friend std::ostream &operator<<(std::ostream &o, Character &ch)
    {
        o << ch.weight << " " << ch.power << " " << ch.heart << " " << ch.exp << " " << ch.money << " " << ch.status_name;
        return o;
    }
    void useItems(int i)
    {
        weightUpDown(false, sh.get_goods(i).get_weightUp());
        powerUpDown(false, sh.get_goods(i).get_powerUp());
    }
    void statusJudge(bool *isEnd) // 状态判断函数
    {
        while (1)
        {
            if (power == 0)
            {
                status_name = "hungry";
                sta.hungry();
            }
            else if (weight >= FAT_CRITICAL)
            {
                status_name = "fat";
                sta.fat();
            }
            else if (power <= TIRED_CRITICAL)
            {
                status_name = "tired";
                sta.tired();
            }
            else
            {
                status_name = "none";
            }
            if (*isEnd)
                break;
        }
    }
    void weightUpDown(bool isDecrease, int i) // 体重上升、下降函数
    {
        if (isDecrease)
            weight -= i;
        else
            weight += i;
    }
    void powerUpDown(bool isDecrease, int i) // 体力上升、下降函数
    {
        if (isDecrease)
            power -= i;
        else
            power += i;
    }
    void heartUpDown(bool isDecrease, int i) // 爱心上升、下降函数
    {
        if (isDecrease)
            heart -= i;
        else
            heart += i;
    }
    void expUpDownDown(bool isDecrease, int i) // 爱心上升、下降函数
    {
        if (isDecrease)
            exp -= i;
        else
            exp += i;
    }
    void moneyUpDown(bool isDecrease, int i) // 爱心上升、下降函数
    {
        if (isDecrease)
            money -= i;
        else
            money += i;
    }
};
class Exercise:public Character
{
public:
    Exercise();
    void run() // 跑步
    {
        gameTime gt;
        std::thread thrtime(&gameTime::timer, &gt, 210, false); // 创建单独线程计时
        thrtime.detach();
        weightUpDown(true, 3);
        powerUpDown(true,5);
    }
    int other() // 其他
    {
        gameTime gt;
        std::thread thrtime(&gameTime::timer, &gt, 150, false); // 创建单独线程计时
        thrtime.detach();
        weightUpDown(true, 2);
        powerUpDown(true,6);
    }
};
class Homework:public Character
{
public:
    Homework();
    void clean() // 打扫卫生
    {
        gameTime gt;
        std::thread thrtime(&gameTime::timer, &gt, 210, false); // 创建单独线程计时
        thrtime.detach();
        heartUpDown(true, 5);
        powerUpDown(false,2);
    }
    int cook() // 炒菜
    {
        gameTime gt;
        std::thread thrtime(&gameTime::timer, &gt, 210, false); // 创建单独线程计时
        thrtime.detach();
        heartUpDown(true, 5);
        powerUpDown(false,2);
    }
    int wash() // 洗碗
    {
        gameTime gt;
        std::thread thrtime(&gameTime::timer, &gt, 150, false); // 创建单独线程计时
        thrtime.detach();
        heartUpDown(true, 3);
        powerUpDown(false,1);
    }
};
class Work:public Character
{
public:
    Work();
    void banzhuan() // 搬砖
    {
        gameTime gt;
        std::thread thrtime(&gameTime::timer, &gt, 300, false); // 创建单独线程计时
        thrtime.detach();
        heartUpDown(true, 5);
        powerUpDown(false,3);
        expUpDownDown(true,20);
        moneyUpDown(true,150);
    }
    int zuoban() // 坐班
    {
        gameTime gt;
        std::thread thrtime(&gameTime::timer, &gt, 240, false); // 创建单独线程计时
        thrtime.detach();
        heartUpDown(true, 5);
        powerUpDown(false,2);
        expUpDownDown(true,40);
        moneyUpDown(true,250);
    }
};
int main(int argc, char const *argv[])
{
    bool *isEnd = new bool;
    *isEnd = false;
    Character chara1(10, 10, 0, 0, 100);
    std::thread thr(&Character::statusJudge, &chara1, isEnd);
    chara1.useItems(1);
    std::cout << chara1;
    *isEnd = true;
    thr.join();
    return 0;
}
