#include "login.h"
#include "ui_login.h"
#include "widget.h"
#include <QMessageBox>
Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

    this->setWindowFlags(windowFlags()&~Qt::WindowMaximizeButtonHint);// 禁止最大化按钮
    this->setFixedSize(this->width(),this->height());//禁止拖拽
    this->setWindowIcon(QIcon(":/img/ATM.ico"));//生成窗口图标
}

Login::~Login()
{
    delete ui;
}

void Login::on_Btn_close_clicked()
{
    this->close();
}

void Login::on_Btn_Login_clicked()
{
    QString AdminNum=ui->led_UserNum->text();
    QString AdminPwd=ui->Led_UserPwd->text();

    if(AdminNum.isEmpty() || AdminPwd.isEmpty())
    {
        QMessageBox::information(this,"错误","账号或密码错误,请重新尝试",QMessageBox::Yes);
        return;
    }
    if(AdminNum=="Admin" && AdminPwd=="Admin")
    {
        //使用单例模式创建
        Widget *w=Widget::GetInstance();
        w->show();
        this->close();
    }
}
