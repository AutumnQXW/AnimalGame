#pragma once

#include <QWidget>

class TCharacter;
class TStatus : public QWidget
{
    Q_OBJECT

private:
    //static int num_alert;

    int timer_id_alert;

    //int timer_id_recovery;
    //QTimer *timer_;

    TCharacter &character_;
    static QVector<QString> name_list_; // 创建姓名表

public:
    TStatus(TCharacter &character, QWidget *parent = nullptr);
    TStatus(const TStatus &status);
    ~TStatus();

    void alert();

    void hungry();  // power==0 && items==0

    void fat();     // weight>=20

    void tired();   // power<=5

    void none();

    void timerEvent(QTimerEvent* event) override;

    TStatus &operator=(const TStatus &status) = delete;
signals:
    void fatEvent(int msec);
    void hungryEvent();
    void tiredEvent();
    void noneEvent();
};
