#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>
#include <QMovie>
#include <QTimer>
#include <QTableView>
#include <QSqlQueryModel>
#include <QSqlRecord>
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    //explicit Widget(QWidget *parent = 0);

    void InitWindow();//初始化窗口

    ~Widget();
protected:
    void paintEvent(QPaintEvent *event);//绘画事件
    void showEvent(QShowEvent *event);//显示窗口事件
private slots:
    void on_btn_MoneyQeury_clicked();

    void on_btn_updatePWD_clicked();

    void on_btn_close_clicked();

    void on_btn_to_deposit_clicked();

    void on_btn_transfer_clicked();

    void on_btn_out_deposit_clicked();

    void on_btn_print_clicked();

    void updateTimer();//计时器槽函数

    void on_btn_changepwd_clicked();

    void Deposit_clicked();//存款事件
    void Withdraw_clicked();//取款事件

    void on_btn_ckreturn_clicked();

    void on_radio_hwzz_clicked();

    void on_radio_hnzz_clicked();

    void on_btn_zr_clicked();

    void on_btn_QK_clicked();

    void on_btn_Deposit_clicked();

    void on_btn_ZKOK_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_Btn_QKVoucher_clicked();

    void on_Btn_CKVoucher_clicked();

    void on_Btn_ZZVoucher_clicked();

    void on_btn_printVoucher_clicked();

    void on_btn_pwdclear_clicked();

private:
    //构造函数以及拷贝构造函数设置为私有(即封锁入口)
    explicit Widget(QWidget *parent = 0);
    Widget(const Widget &);

    Ui::Widget *ui;

    QMovie *movie;//加载GIF图
    QTimer *timer;//计时器

    int closeCount;//退出计时器
    int count;

    QString VoucherTake;
    QString VoucherBalance;//凭条余额信息


    //临时保存转账信息
    QString ZZInfo[2];

    QSqlQueryModel *QueryModel;//数据库查询模型
    QTableView *TableView;//显示数据的表格对象
public:
    void BindTableViewInfo(QString sql, QTableView *tableView,QString columnNames[], int columnWidths[]);//表格视图信息
    static Widget *GetInstance()//获取Widget对象
    {
        static Widget *m_pInstance;
        if(m_pInstance == NULL) //判断是否第一次调用
            m_pInstance = new Widget();
        return m_pInstance;
    }
};

#endif // WIDGET_H
