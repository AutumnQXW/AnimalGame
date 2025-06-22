#pragma once
#include <chrono>
class gameTime
{
private:
    std::chrono::system_clock::time_point start;
    std::chrono::system_clock::time_point end;

public:
    gameTime()
    {
        start = std::chrono::system_clock::now();
    }
    double get_duration() // 以秒计算间隔
    {
        end = std::chrono::system_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        return double(duration.count()) * std::chrono::microseconds::period::num / std::chrono::microseconds::period::den;
    }
    void restart() // 重启计时
    {
        start = std::chrono::system_clock::now();
    }
    //void operator()(int s, bool &isEnd)
    //{
    //    isEnd = false;
    //    while (1)
    //    {
    //        if (get_duration() >= s)
    //        {
    //            isEnd = true;
    //            break;
    //        }
    //        break;
    //    }
    //}
    void timer(int s, bool *isEnd) // 计时器
    {
        *isEnd = false;
        while (1)
        {
            if (get_duration() >= s)
            {
                *isEnd = true;
                break;
            }
        }
    }
};