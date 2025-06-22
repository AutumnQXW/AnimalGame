#pragma once

#include <QMainWindow>
#include "ui_test.h"
#include "GameInclude.h"
#include "admin.h"
#include <vector>

QT_BEGIN_NAMESPACE

namespace Ui
{
    class TestClass;
};

QT_END_NAMESPACE

class Test : public QMainWindow
{
    Q_OBJECT

    // backend
    std::vector<TCharacter> characters_;
    std::vector<TStatus> statuses_;
    TShop shop_;
    TExercise exercise_;
    TWork work_;
    THousework housework_;
    std::map<int, Game::items> item_map_;

    // backgrounds
    Mainroom *mainroom_;
    park *park_;

protected:
    void showEvent(QShowEvent* event) override;
    void closeEvent(QCloseEvent* event) override;

public:
    Test(QWidget* parent = nullptr);
    ~Test() override;

public:
    Ui::TestClass* ui;

public slots:
    void on_btnAddChara_clicked();
    void on_btnStatus_clicked();
    void on_btnBuy_clicked();
    void on_btnItemNum_clicked();
    void on_btnExercise_clicked();
    void on_btnWork_clicked();
    void on_btnHelp_clicked();
    void on_btnHouseWork_clicked();
    void on_btnUse_clicked();
    void on_btnOpenBackground_clicked();
    void do_workEnd();
    void do_dataChange(Game::data data, bool is_decrease, int value);
    void do_stopWork();
    void do_gameOver();

private slots:
    void do_stock(Game::items item);
    void do_no_money();
    void do_sell_out();
};
