#pragma once

#include <qpropertyanimation.h>
#include <QWidget>

class TAnimWidget  : public QWidget
{
    Q_OBJECT

    bool eject_flag_;
    QPropertyAnimation* propertyAnimation;
    QTimer *timer_;

public:
    TAnimWidget(QWidget *parent);
    ~TAnimWidget();
    void eject_anim(); //  µ¯³ö¶¯»­
    void enterEvent(QEnterEvent* event) override;
    void leaveEvent(QEvent* event) override;
    //bool eventFilter(QObject* watched, QEvent* event) override;
};
