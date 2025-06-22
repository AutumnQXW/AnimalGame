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
    // ��ʾlabel
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

    QEventLoop loop; //����һ���µ��¼�ѭ��
    //QTimer::singleShot(2000, &loop, SLOT(quit())); 
    connect(timer_, &QTimer::timeout, &loop, &QEventLoop::quit);//�������ζ�ʱ�����ۺ���Ϊ�¼�ѭ�����˳�����
    timer_->start(2000);
    loop.exec(); //�¼�ѭ����ʼִ�У�����Ῠ�����ֱ����ʱʱ�䵽����ѭ�����˳�

    //����label
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
