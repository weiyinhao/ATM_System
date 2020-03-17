#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>
#include <QDateTime>
#include <QSqlQueryModel>
#include <QTableView>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QListWidgetItem>
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
   //explicit Widget(QWidget *parent = 0);
    ~Widget();


private slots:

    void on_Btn_FirstPage_clicked();

    void on_BtnBankCard_clicked();

    void on_Btn_ATM_clicked();

    void on_Btn_Money_clicked();

    void on_Btn_Close_clicked();

    void updateTimer();

    void on_tableView_BankCard_clicked(const QModelIndex &index);

    void on_btn_Banjupdate_clicked();

    void on_btn_BankKT_clicked();

    void on_btn_Bankcancel_clicked();

    void on_btn_conditionQuery_clicked();

    void on_btn_QeuryQBBank_clicked();

    void on_btn_ATMTJCX_clicked();

    void on_Btn_QBATM_clicked();

    void on_tableView_ATMEquit_clicked(const QModelIndex &index);

    void on_btn_ATMEquitUpdate_clicked();

    void on_btn_TJATMQuit_clicked();

    void on_btn_ATMEquitDelete_clicked();

    void on_Btn_ATMClear_clicked();

    void on_Btn_MoneyCR_clicked();

    void on_btn_MoneyClear_clicked();

private:
    //构造函数以及拷贝构造函数设置为私有(即封锁入口)
    explicit Widget(QWidget *parent = 0);
    Widget(const Widget &);

    Ui::Widget *ui;

    QTimer *timer;//计时器

    QSqlQueryModel *QueryModel;//数据库查询模型
    QTableView *TableView;//显示数据的表格对象

    QMap<QString,QString> map;

public:
    void InitWindow();

    void BindTableViewInfo(QString Sql, QTableView *tableView,QString columnNames[], int columnWidths[]);//表格视图信息
    static Widget *GetInstance()//获取Widget对象
    {
        static Widget *m_pInstance;
        if(m_pInstance == NULL) //判断是否第一次调用
            m_pInstance = new Widget();
        return m_pInstance;
    }
};

#endif // WIDGET_H
