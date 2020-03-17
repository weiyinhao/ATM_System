#include "login.h"
#include "ui_login.h"
#include "Config/helper.h"
#include "Config/sqloperate.h"
#include <QDebug>
#include "helpdlg.h"
Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    InitFont();
}
//初始化窗口
void Login::InitFont()
{
    ui->led_BankNum->setFocus();

    this->setWindowFlags(windowFlags()&~Qt::WindowMaximizeButtonHint);// 禁止最大化按钮
    this->setFixedSize(this->width(),this->height());//禁止拖拽
    this->setWindowIcon(QIcon(":/images/img/ATM.ico"));//生成窗口图标

    //初始化基本信息
    ui->btn_Help->setText("帮助\nHelp");
    ui->btn_OK->setText("确定\nDetermine");
    ui->btn_Back->setText("回退\nRoolBack");
    ui->btn_clear->setText("清空\nClear");
    ui->btn_refundcards->setText("退出\nExit");
    ui->label_Bankstate->setText("当前选定的银行:中国工商银行");

    //约定银行卡条件
    ui->led_BankNum->setMaxLength(19);//卡号最长19位
    ui->led_BankPwd->setMaxLength(6);//密码最长6位
    ui->led_BankPwd->setReadOnly(true);//未输入银行卡禁止输入密码

    //信号和槽函数绑定
    connect(ui->Btn_0,&QPushButton::clicked, this, &Login::getNumber);
    connect(ui->Btn_1,&QPushButton::clicked, this, &Login::getNumber);
    connect(ui->Btn_2,&QPushButton::clicked, this, &Login::getNumber);
    connect(ui->Btn_3,&QPushButton::clicked, this, &Login::getNumber);
    connect(ui->Btn_4,&QPushButton::clicked, this, &Login::getNumber);
    connect(ui->Btn_5,&QPushButton::clicked, this, &Login::getNumber);
    connect(ui->Btn_6,&QPushButton::clicked, this, &Login::getNumber);
    connect(ui->Btn_7,&QPushButton::clicked, this, &Login::getNumber);
    connect(ui->Btn_8,&QPushButton::clicked, this, &Login::getNumber);
    connect(ui->Btn_9,&QPushButton::clicked, this, &Login::getNumber);
    connect(ui->Btn_xh,&QPushButton::clicked, this, &Login::getNumber);
    connect(ui->Btn_jh,&QPushButton::clicked, this, &Login::getNumber);

    timer=new QTimer(this);
    connect(timer,&QTimer::timeout,this,&Login::updateTimer);
    timer->start(1000);//启动1秒更新一次

    //正则表达式
    QRegExp rx("^[0-9]*[1-9][0-9]*$");
    QRegExpValidator *pRevalidotor = new QRegExpValidator(rx, this);
    ui->led_BankNum->setValidator(new QRegExpValidator(rx, this));
    ui->led_BankPwd->setValidator(new QRegExpValidator(rx, this));
}

Login::~Login()
{
    delete ui;
}
//背景绘制
void Login::paintEvent(QPaintEvent *event)
{
    setAttribute(Qt::WA_TranslucentBackground, true);
    //定义画家
    QPainter painter(this);
    painter.drawPixmap(0,0,this->width(),this->height(),QPixmap(":/images/img/FristPage.jpg"));
}

//下拉选择框改变事件
void Login::on_comboBox_activated(const QString &arg1)
{
    //设置状态
    ui->label_Bankstate->setText("当前选定的银行:"+arg1);
}
//获取点击按钮的数字
void Login::getNumber()
{
    //获取发送者信息
    QObject *object = QObject::sender();
    QPushButton *push_button = qobject_cast<QPushButton *>(object);

    //内容设置到输入框内
    if((push_button->text()=="*") || (push_button->text()=="#"))
    {
        Helper::Luhn(ui->led_BankNum->text());
        Helper::ShowMessageBoxError("错误");
        return;
    }
    //是否获取焦点
    if(ui->led_BankNum->text().length()!=19)
    {
        QString currentText=ui->led_BankNum->text();//保存当前
        ui->led_BankNum->setText(currentText+push_button->text());
    }else
    {
        QString currentText=ui->led_BankPwd->text();//保存当前
        ui->led_BankPwd->setText(currentText+push_button->text());
    }

}
//清空事件
void Login::on_btn_clear_clicked()
{
    ui->led_BankNum->clear();
    ui->led_BankPwd->clear();
}
//回退事件
void Login::on_btn_Back_clicked()
{
    //如果为空不能回退
    if(ui->led_BankNum->text().isEmpty())
    {

        return;
    }
    if(ui->led_BankPwd->text().isEmpty())
    {
        QString currentText=ui->led_BankNum->text();//当前字符串
        ui->led_BankNum->setText(currentText.left(currentText.size()-1));
    }else
    {
        QString currentText=ui->led_BankPwd->text();//当前字符串
        ui->led_BankPwd->setText(currentText.left(currentText.size()-1));
    }

}
//时钟事件
void Login::updateTimer()
{
    //获取系统时间
    ui->label_time->setText("当前北京时间: "+QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"));

}
//银行卡号输入文本改变事件
void Login::on_led_BankNum_textChanged(const QString &arg1)
{
    if(ui->led_BankNum->text().length()==19)
    {
       ui->led_BankPwd->setFocus();
       ui->led_BankPwd->setReadOnly(false);
       ui->led_BankPwd->setFocus();
    }else
    {
        ui->led_BankNum->setFocus();
        ui->led_BankPwd->setReadOnly(true);
    }
}
//登入ATM机事件
void Login::on_btn_OK_clicked()
{

    if(ui->led_BankNum->text().isEmpty() || ui->led_BankPwd->text().isEmpty())
    {
        Helper::ShowMessageBoxError("银行卡号或密码不能为空!");
        return;
    }
    //银行卡号验证
    if(!Helper::Luhn(ui->led_BankNum->text()))
    {
        Helper::ShowMessageBoxError("您当前插入的卡并非银行卡,请重试!");
        return;
    }
    //判断银行卡状态
    if(Sqloperate::GetBankState(ui->led_BankNum->text())!="正常")
    {
        Helper::ShowMessageBoxError("您当前银行卡处于"+Sqloperate::GetBankState(ui->led_BankNum->text())+"状态,无法登录!");
        return;
    }
    QString pwd=Sqloperate::GetBankCardPwd(ui->led_BankNum->text());
    if(pwd==ui->led_BankPwd->text())
    {
        //判断是否属于相应的银行
        if(Sqloperate::GetBankName(ui->led_BankNum->text())!=ui->comboBox->currentText())
        {
            Helper::ShowMessageBoxError("此银行卡不属于该银行,无法登录!");
            return;
        }
        //登录成功 记录信息
        Helper::CurrentBank=ui->comboBox->currentText();
        Helper::CurrentBankNum=ui->led_BankNum->text();
        Helper::CurrentBankPwd=ui->led_BankPwd->text();

        //使用单例模式创建Widget对象
        Widget *widget=Widget::GetInstance();
        widget->show();
        this->close();

    }else
    {
        Helper::ShowMessageBoxError("密码错误,请重新输入!");
        return;
    }
}
//退出ATM系统
void Login::on_btn_refundcards_clicked()
{
    this->close();
}
//帮助
void Login::on_btn_Help_clicked()
{
    HelpDlg help;
    help.show();
    help.exec();
}
