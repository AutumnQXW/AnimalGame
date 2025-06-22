#include "tanimwidget.h"

#include <QEvent>
#include <QEventLoop>
#include <QPropertyAnimation>
#include <QTimer>

TAnimWidget::TAnimWidget(QWidget *parent)
    : QWidget(parent)
    , timer_(new QTimer)
{
    eject_flag_ = true;
    propertyAnimation = new QPropertyAnimation(this, "geometry");
    propertyAnimation->setEasingCurve(QEasingCurve::InOutQuint);
    propertyAnimation->setDuration(500);
    timer_->setSingleShot(true);
    this->setAttribute(Qt::WA_StyledBackground);
}

TAnimWidget::~TAnimWidget()
{}

void TAnimWidget::eject_anim()
{
    // 显示label
    if (eject_flag_)
    {
        propertyAnimation->setStartValue(QRect(this->parentWidget()->width(), this->parentWidget()->height() - this->height(),
                                               this->width(),
                                               this->height()));
        propertyAnimation->setEndValue(QRect(this->parentWidget()->width() - this->width(),
                                             this->parentWidget()->height() - this->height(), this->width(),
                                             this->height()));
        propertyAnimation->start();
        eject_flag_ = false;
    }

    QEventLoop loop; //定义一个新的事件循环
    //QTimer::singleShot(2000, &loop, SLOT(quit())); 
    connect(timer_, &QTimer::timeout, &loop, &QEventLoop::quit);//创建单次定时器，槽函数为事件循环的退出函数
    timer_->start(2000);
    loop.exec(); //事件循环开始执行，程序会卡在这里，直到定时时间到，本循环被退出

    //隐藏label
    propertyAnimation->setStartValue(QRect(this->parentWidget()->width() - this->width(),
                                           this->parentWidget()->height() - this->height(), this->width(),
                                           this->height()));
    propertyAnimation->setEndValue(QRect(this->parentWidget()->width(), this->parentWidget()->height() - this->height(),
                                         this->width(),
                                         this->height()));
    propertyAnimation->start();
    eject_flag_ = true;
}

void TAnimWidget::enterEvent(QEnterEvent* event)
{
    timer_->stop();
}

void TAnimWidget::leaveEvent(QEvent* event)
{
    timer_->start(2000);
}

//bool TAnimWidget::eventFilter(QObject* watched, QEvent* event)
//{
//    if (event->type() == QEvent::Enter)
//    {
//        killTimer(timer_id_);
//    }
//    else if(event->type() == QEvent::Leave)
//    {
//        timer_->start(2000);
//    }
//    return QWidget::eventFilter(watched, event);
//}
