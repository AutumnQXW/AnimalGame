#pragma once
#include <QFlags>
#include <qobjectdefs.h>
#define HEART_HELP 1
#define WEIGHT_EAT 0.1
#define POWER_EAT 2
#define POWER_TRAIN 2
#define WEIGHT_TRAIN 0.1
#define ALERT_TIME 60
#define POWER_TIME_FAT 15
#define POWER_TIME 30
#define FAT_CRITICAL 20     // 肥胖临界值
#define TIRED_CRITICAL 5    // 疲惫临界值
#define CHARA_NUM 3        // 角色数
#define ITEM_NUM 3          // 道具数

namespace Game
{
    Q_NAMESPACE

    enum status
    {
        none = 0x0,
        // 0 : 0000 0000
        hungry = 0x1,
        // 1 : 0000 0001
        fat = 0x2,
        // 2 : 0000 0010
        tired = 0x4,
        // 4 : 0000 0100
    };

    // 自定义QFlag
    Q_ENUM_NS(status)
    Q_DECLARE_FLAGS(status_flags, status)
    Q_FLAG_NS(status_flags)
    Q_DECLARE_OPERATORS_FOR_FLAGS(status_flags)

    enum data
    {
        name = 0,
        weight = 1,
        power = 2,
        heart = 3,
        exp = 4,
        level = 5,
        money = 6,
        status = 7
    };

    enum items
    {
        bread = 1,
        spam = 2,
        hamburger = 3
    };

    inline const char* to_string(items i)
    {
        switch (i)
        {
        case items::bread: return "bread";
        case items::spam: return "spam";
        case items::hamburger: return "hamburger";
        default: return "unknown";
        }
    }

    enum works
    {
        banzhuan = 0,
        zuoban = 1,
    };

    enum exercises
    {
        run = 0,
        other = 1,
    };

    enum houseworks
    {
        clean = 0,
        cook = 1,
        wash = 2,
    };

    enum class backgrounds : int
    {
        mainroom = 0,
        park = 1,
        shop = 2,
        zuoban = 3,
        banzhuan = 4,
        gym = 5
    };
}

struct times
{
    inline static int power_decrease_time = POWER_TIME;
};

//int times::power_decrease_time = POWER_TIME;

struct judge
{
    inline static bool can_activity = true;
};

//bool judge::can_activity = true;
