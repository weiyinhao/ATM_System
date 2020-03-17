#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <QDateTime>
#include "widget.h"
namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();

    void InitFont();//初始化窗口
protected:
    void paintEvent(QPaintEvent *event);
private slots:
    void on_comboBox_activated(const QString &arg1);

    void getNumber();//获取输入的卡号数字槽函数

    void on_btn_clear_clicked();

    void on_btn_Back_clicked();

    void updateTimer();//计时器槽函数

    void on_led_BankNum_textChanged(const QString &arg1);

    void on_btn_OK_clicked();

    void on_btn_refundcards_clicked();

    void on_btn_Help_clicked();

private:
    Ui::Login *ui;

    QTimer *timer;//计时器

    //Widget *widget;//主页面

};

#endif // LOGIN_H
