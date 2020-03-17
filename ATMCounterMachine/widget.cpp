#include "widget.h"
#include "ui_widget.h"
#include "Config/helper.h"
#include "Config/sqloperate.h"
#include <QDebug>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    InitWindow();
}

Widget::~Widget()
{
    delete ui;
}
void Widget::InitWindow()
{
    //ui->label_Head->setAttribute(Qt::WA_TranslucentBackground);

    //初始化控件
    ui->btn_to_deposit->setText("存款\nDeposit");
    ui->btn_transfer->setText("转账\nBankTransfer");
    ui->btn_out_deposit->setText("取款\nWithdraw");
    ui->btn_MoneyQeury->setText("查询\nQueryBalance");
    ui->btn_updatePWD->setText("修改密码\nChangePassword");
    ui->btn_close->setText("退卡\nRefundCards");
    ui->btn_print->setText("打印凭条\nPrintVoucher");

    //进入初始页面
    ui->stackedWidget->setCurrentWidget(ui->InitPage);
    ui->cob_bank->hide();
    ui->label_zrBank->hide();

    timer=new QTimer(this);
    connect(timer,&QTimer::timeout,this,&Widget::updateTimer);
    timer->start(1000);//启动1秒更新一次

    this->setWindowIcon(QIcon(":/images/img/ATM.ico"));//生成窗口图标

    //初始化计时器
    count=0;

    //存款信号和槽函数绑定
    connect(ui->btn_CR100,&QPushButton::clicked, this, &Widget::Deposit_clicked);
    connect(ui->btn_CR300,&QPushButton::clicked, this, &Widget::Deposit_clicked);
    connect(ui->btn_CR3000,&QPushButton::clicked, this, &Widget::Deposit_clicked);
    connect(ui->btn_CR1500,&QPushButton::clicked, this, &Widget::Deposit_clicked);
    connect(ui->btn_CR1000,&QPushButton::clicked, this, &Widget::Deposit_clicked);
    //取款信号和槽函数绑定
    connect(ui->btn_QK100,&QPushButton::clicked, this, &Widget::Withdraw_clicked);
    connect(ui->btn_QK200,&QPushButton::clicked, this, &Widget::Withdraw_clicked);
    connect(ui->btn_QK300,&QPushButton::clicked, this, &Widget::Withdraw_clicked);
    connect(ui->btn_QK500,&QPushButton::clicked, this, &Widget::Withdraw_clicked);
    connect(ui->btn_QK1000,&QPushButton::clicked, this, &Widget::Withdraw_clicked);
    connect(ui->btn_QK2000,&QPushButton::clicked, this, &Widget::Withdraw_clicked);

    this->setWindowFlags(windowFlags()&~Qt::WindowMaximizeButtonHint);// 禁止最大化按钮
    this->setFixedSize(this->width(),this->height());//禁止拖拽

}
//窗口显示事件
void Widget::showEvent(QShowEvent *event)
{
    if(Helper::CurrentBank=="中国工商银行")
    {
        this->setWindowTitle("中国工商银行ATM柜台服务机");
    }
    else if(Helper::CurrentBank=="中国农业银行")
    {
        this->setWindowTitle("中国农业银行ATM柜台服务机");
    }
    else if(Helper::CurrentBank=="中国建设银行")
    {
        this->setWindowTitle("中国建设银行ATM柜台服务机");
    }

    else if(Helper::CurrentBank=="交通银行")
    {
        this->setWindowTitle("交通银行ATM柜台服务机");
    }
    else if(Helper::CurrentBank=="中国银行")
    {
        this->setWindowTitle("中国银行ATM柜台服务机");
    }
}

//绘图事件
void Widget::paintEvent(QPaintEvent *event)
{
    QString imgPath="";
    QString HeadImgPath="";
    QString MidImgPath="";
    QString BtnImgPath="";
    if(Helper::CurrentBank=="中国工商银行")
    {
        imgPath=":/images/img/OrangeYellow.jpg";
        HeadImgPath="border-image: url(:/images/img/ChinaGSBank.jpg);";
        MidImgPath="border-image: url(:/images/img/OrangeYellow1.jpg);color: rgb(0, 0, 0);";
        BtnImgPath="color: rgb(255, 255, 255);background-image: url(:/images/img/OrangeYellow2.jpg);";;
    }
    else if(Helper::CurrentBank=="中国农业银行")
    {
        imgPath=":/images/img/greeBackground.jpg";
        HeadImgPath="border-image: url(:/images/img/nyBank.png);";
        MidImgPath="border-image: url(:/images/img/greed3.jpg);color: rgb(255, 255, 255);";
        BtnImgPath="color: rgb(255, 255, 255);background-image: url(:/images/img/Greed5.jpg);";;
    }
    else if(Helper::CurrentBank=="中国建设银行")
    {
        imgPath=":/images/img/blue5.jpg";
        HeadImgPath="border-image: url(:/images/img/ChinaJSBank6.png);";
        MidImgPath="border-image: url(:/images/img/blackBackground.jpg);color: rgb(255, 255, 255);";
        BtnImgPath="color: rgb(255, 255, 255);background-image: url(:/images/img/blueBackgroud3.jpg);";
    }

    else if(Helper::CurrentBank=="交通银行")
    {
        imgPath=":/images/img/blueBackgroud2.jpg";
        HeadImgPath="border-image: url(:/images/img/JTBank.png);";
        MidImgPath="border-image: url(:/images/img/blue5.jpg);color: rgb(255, 255, 255);";;
        BtnImgPath="color: rgb(255, 255, 255);background-image: url(:/images/img/blackBackground.jpg);";
    }
    else if(Helper::CurrentBank=="中国银行")
    {
        imgPath=":/images/img/Yellow.png";
        HeadImgPath="border-image: url(:/images/img/ChinaBank.png);";
        MidImgPath="border-image: url(:/images/img/tuYellow.jpg);color: rgb(255, 255, 255);";
        BtnImgPath="color: rgb(255, 255, 255);background-image: url(:/images/img/OrangeYellow1.jpg);";
    }

    //定义画家
    QPainter painter(this);
    painter.drawPixmap(0,0,this->width(),this->height(),QPixmap(imgPath));

    //设置相关样式
    ui->label_Head->setStyleSheet(HeadImgPath);
    ui->label_mid->setStyleSheet(MidImgPath);
    ui->btn_to_deposit->setStyleSheet(BtnImgPath);
    ui->btn_transfer->setStyleSheet(BtnImgPath);
    ui->btn_out_deposit->setStyleSheet(BtnImgPath);
    ui->btn_MoneyQeury->setStyleSheet(BtnImgPath);
    ui->btn_updatePWD->setStyleSheet(BtnImgPath);
    ui->btn_close->setStyleSheet(BtnImgPath);
    ui->btn_print->setStyleSheet(BtnImgPath);


}
//计时器事件
void Widget::updateTimer()
{
    count++;
    ui->label_timer->setText(QString::number(count));


}

//查询银行卡余额事件
void Widget::on_btn_MoneyQeury_clicked()
{
    //进行查询页面
    ui->stackedWidget->setCurrentWidget(ui->balancepage);

    //进行余额查询
    QString CardBalance=Sqloperate::GetBankBalance(Helper::CurrentBankNum);
    ui->label_balance->setText(CardBalance);
    ui->label_kybalance->setText(CardBalance);
    ui->label_dtkqbalance->setText("20000");
}
//修改银行卡事件
void Widget::on_btn_updatePWD_clicked()
{
    //进入修改密码页面
    ui->stackedWidget->setCurrentWidget(ui->changepwdpage);


}
//退卡事件
void Widget::on_btn_close_clicked()
{
    //进入修改密码页面
    //ui->stackedWidget->setCurrentWidget(ui->TransactionInfopage);

    //加载GIF图
    movie=new QMovie(":/images/img/loding.gif");
    ui->label_loading->setMovie(movie);
    movie->start();
    ui->stackedWidget->setCurrentWidget(ui->LoadingPage);

    ui->btn_MoneyQeury->setEnabled(false);
    ui->btn_updatePWD->setEnabled(false);
    ui->btn_to_deposit->setEnabled(false);
    ui->btn_transfer->setEnabled(false);
    ui->btn_out_deposit->setEnabled(false);
    ui->btn_print->setEnabled(false);
    //休息
    QTime time;
    time.start();
    while(time.elapsed() < 3000) //等待时间流逝3秒钟
        QCoreApplication::processEvents();
    this->close();


}
//存款事件
void Widget::on_btn_to_deposit_clicked()
{
    //进入存款页面
    ui->stackedWidget->setCurrentWidget(ui->DepositPage);
}
//转账事件
void Widget::on_btn_transfer_clicked()
{
    //进入转账页面
    ui->stackedWidget->setCurrentWidget(ui->BankTransferPage);

    if(ui->radio_hnzz->isChecked())
    {
        ui->cob_bank->hide();
        ui->label_zrBank->hide();
    }else if(ui->radio_hwzz->isChecked())
    {
        ui->cob_bank->show();
        ui->label_zrBank->show();
    }
}

//取款事件
void Widget::on_btn_out_deposit_clicked()
{
    //进入转账页面
    ui->stackedWidget->setCurrentWidget(ui->WithdrawPage);


}
//打印凭条事件
void Widget::on_btn_print_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->PrintVoucherPage);
    VoucherTake="存款凭条";
    ui->Btn_QKVoucher->setEnabled(true);
    ui->Btn_CKVoucher->setEnabled(false);
    ui->Btn_ZZVoucher->setEnabled(true);

    QString sql="select * from Deposit;";
    QString colName[]={"操作单号","操作卡号","操作时间","操作金额","存款"};
    int colWidth[]={200,180,200,160,100};
    BindTableViewInfo(sql,ui->tableView,colName,colWidth);
}
//确定修改密码
void Widget::on_btn_changepwd_clicked()
{
    if(ui->led_oldpwd->text().isEmpty()||ui->led_newpwd->text().isEmpty() || ui->led_renewpwd->text().isEmpty())
    {
        Helper::ShowMessageBoxError("密码不能为空!请重新尝试");
        return;
    }

    //修改密码
    if(ui->led_newpwd->text()!=ui->led_renewpwd->text())
    {
        Helper::ShowMessageBoxError("两次输入密码不相同!请重新尝试");
        on_btn_pwdclear_clicked();
        return;
    }
    if(Sqloperate::ChangePwd(ui->led_oldpwd->text(),ui->led_newpwd->text()))
    {
        Helper::ShowMessageBoxInfo("密码修改成功!");
        return;
    }else
    {
        Helper::ShowMessageBoxInfo("当前密码不正确,请重新输入!");
        on_btn_pwdclear_clicked();
        return;
    }
}

//存款事件
void Widget::Deposit_clicked()
{
    //获取发送者信息
    QObject *object = QObject::sender();
    QPushButton *BtnDepositNum = qobject_cast<QPushButton *>(object);
    QString DepositMoneyCount=BtnDepositNum->text();

    //进行存款处理

    bool ok=Sqloperate::Deposit(DepositMoneyCount,Helper::CurrentBankNum);
    if(ok)
    {
        /*ui->stackedWidget->setCurrentWidget(ui->TransactionInfopage);
        QString CardBalance=Sqloperate::GetBankBalance(Helper::CurrentBankNum);
        ui->label_ckinfobalance->setText("存款金额:"+DepositMoneyCount+"元");
        ui->label_ckinfokybalance->setText("账户当前余额:"+CardBalance+"元");*/
        QString CardBalance=Sqloperate::GetBankBalance(Helper::CurrentBankNum);
        ui->stackedWidget->setCurrentWidget(ui->DepositOKINFOPage);
        ui->label_ckcardid->setText("存款账号:"+Helper::CurrentBankNum);
        ui->label_ckBalance->setText("账户当前余额:"+CardBalance+"元");
    }
}
//取款事件
void Widget::Withdraw_clicked()
{
    //获取发送者信息
    QObject *object = QObject::sender();
    QPushButton *BtnWithdrawNum = qobject_cast<QPushButton *>(object);
    QString WithdrawMoneyCount=BtnWithdrawNum->text();

    if(Sqloperate::GetBankBalance(Helper::CurrentBankNum).toInt()<WithdrawMoneyCount.toInt())
    {
        Helper::ShowMessageBoxError("当前银行卡余额不够,不能取款");
        return;
    }
    //进行取款处理
    bool ok=Sqloperate::Withdraw(WithdrawMoneyCount,Helper::CurrentBankNum);
    if(ok)
    {
        /*ui->stackedWidget->setCurrentWidget(ui->TransactionInfopage);
        QString CardBalance=Sqloperate::GetBankBalance(Helper::CurrentBankNum);
        ui->label_ckinfobalance->setText("存款金额:"+DepositMoneyCount+"元");
        ui->label_ckinfokybalance->setText("账户当前余额:"+CardBalance+"元");*/
        QString CardBalance=Sqloperate::GetBankBalance(Helper::CurrentBankNum);
        ui->stackedWidget->setCurrentWidget(ui->DepositOKINFOPage);
        ui->label_30->setText("取款成功");
        ui->label_ckcardid->setText("取款金额:"+WithdrawMoneyCount);
        ui->label_ckBalance->setText("账户当前余额:"+CardBalance+"元");
    }
}

//存/取 返回信息
void Widget::on_btn_ckreturn_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->InitPage);
}
//行外转账
void Widget::on_radio_hwzz_clicked()
{
    ui->cob_bank->show();
    ui->label_zrBank->show();
    Helper::TransferState="行外转账";
}
//行内转账
void Widget::on_radio_hnzz_clicked()
{
    ui->cob_bank->hide();
    ui->label_zrBank->hide();
    Helper::TransferState="行内转账";
}

//确定转账
void Widget::on_btn_zr_clicked()
{
    QString DFCird=ui->lineEdit_zrCird->text();
    QString Money=ui->led_zrMoney->text();
    if(DFCird.isEmpty() || Money.isEmpty())
    {
        Helper::ShowMessageBoxError("卡号或转账金额,不能为空!");
        return;
    }
    qDebug()<<Money.toInt();
    if(Money.toInt()<=0)
    {
        Helper::ShowMessageBoxError("转账金额不能小于等于0!");
        return;
    }
    qDebug()<<Helper::Luhn(DFCird);
    if(!Helper::Luhn(DFCird) || DFCird.length()!=19)
    {
        Helper::ShowMessageBoxError("请输入正确的银行卡号");
        return;
    }
    //未查到密码就表示不存在
    if(Sqloperate::GetBankCardPwd(DFCird)=="")
    {
        Helper::ShowMessageBoxError("当前银行卡不存在,请重新输入");
        return;
    }
    if(Sqloperate::GetBankState(DFCird)!="正常")
    {
        Helper::ShowMessageBoxError("对方银行卡处于"+Sqloperate::GetBankState(DFCird)+"状态,不能进行转账!");
        return;
    }
    if(Helper::TransferState=="行内转账")
    {

        //查找当前账户余额 不足就不能转账。
        if(Sqloperate::GetBankBalance(Helper::CurrentBankNum).toInt()<Money.toInt())
        {
            Helper::ShowMessageBoxError("当前银行卡余额不够,不能进行转账");
            return;
        }
        QString DFBankName=Sqloperate::GetBankName(DFCird);
        QString ZJBankName=Sqloperate::GetBankName(Helper::CurrentBankNum);
        if(ZJBankName!=DFBankName)
        {
            Helper::ShowMessageBoxError("该账户所属银行并非"+ZJBankName+" 请重新输入");
            return;
        }
        ZZInfo[0]=DFCird;//对方卡号
        ZZInfo[1]=Money;//金额
        ui->stackedWidget->setCurrentWidget(ui->BankTransferInFoPage);
        ui->label_CardID->setText("收 款 人:"+Sqloperate::GetBankCaridName(DFCird));
        ui->label_CKName->setText("收 款 金 额:"+Money);
        ui->label_ZKMoney->setText("转入的银行卡号:"+DFCird);
        /**/
    }else
    {
        QString BankName=Sqloperate::GetBankName(DFCird);
        qDebug()<<BankName;
        if(ui->cob_bank->currentText()!=BankName)
        {
            Helper::ShowMessageBoxError("当前所属银行并无此银行卡号,请重新尝试");
            return;
        }
        //查找当前账户余额 不足就不能转账。
        if(Sqloperate::GetBankBalance(Helper::CurrentBankNum).toInt()<Money.toInt())
        {
            Helper::ShowMessageBoxError("当前银行卡余额不够,不能进行转账");
            return;
        }
        ui->stackedWidget->setCurrentWidget(ui->BankTransferInFoPage);
        ZZInfo[0]=DFCird;//对方卡号
        ZZInfo[1]=Money;//金额
        ui->label_CardID->setText("收 款 人:"+Sqloperate::GetBankCaridName(DFCird));
        ui->label_CKName->setText("收 款 金 额:"+Money);
        ui->label_ZKMoney->setText("转入的银行卡号:"+DFCird);
    }
}
//自定义金额取款
void Widget::on_btn_QK_clicked()
{
    QString WithdrawMoneyCount=ui->led_qkNum->text();
    if(WithdrawMoneyCount.isEmpty())
    {
        Helper::ShowMessageBoxError("取款金额不能为空");
        return;
    }
    if(WithdrawMoneyCount.toInt()<=0 || WithdrawMoneyCount.toInt()>5000 || WithdrawMoneyCount.toInt()%100!=0)
    {
        Helper::ShowMessageBoxError("请输入正确的取款金额");
        return;
    }
    if(Sqloperate::GetBankBalance(Helper::CurrentBankNum).toInt()<WithdrawMoneyCount.toInt())
    {
        Helper::ShowMessageBoxError("当前银行卡余额不够,不能取款");
        return;
    }
    //进行取款处理
    bool ok=Sqloperate::Withdraw(WithdrawMoneyCount,Helper::CurrentBankNum);
    if(ok)
    {
        /*ui->stackedWidget->setCurrentWidget(ui->TransactionInfopage);
        QString CardBalance=Sqloperate::GetBankBalance(Helper::CurrentBankNum);
        ui->label_ckinfobalance->setText("存款金额:"+DepositMoneyCount+"元");
        ui->label_ckinfokybalance->setText("账户当前余额:"+CardBalance+"元");*/
        QString CardBalance=Sqloperate::GetBankBalance(Helper::CurrentBankNum);
        ui->stackedWidget->setCurrentWidget(ui->DepositOKINFOPage);
        ui->label_30->setText("取款成功");
        ui->label_ckcardid->setText("取款金额:"+WithdrawMoneyCount);
        ui->label_ckBalance->setText("账户当前余额:"+CardBalance+"元");
    }
}
//自定义存款
void Widget::on_btn_Deposit_clicked()
{
    QString DepositMoneyCount=ui->led_DepositMoney->text();

    if(DepositMoneyCount.isEmpty())
    {
        Helper::ShowMessageBoxError("存款金额不能为空");
        return;
    }
    if(DepositMoneyCount.toInt()<=0 || DepositMoneyCount.toInt()>20000 || DepositMoneyCount.toInt()%100!=0)
    {
        Helper::ShowMessageBoxError("请输入正确的存款金额");
        return;
    }
    //进行存款处理
    bool ok=Sqloperate::Deposit(DepositMoneyCount,Helper::CurrentBankNum);
    if(ok)
    {
        /*ui->stackedWidget->setCurrentWidget(ui->TransactionInfopage);
        QString CardBalance=Sqloperate::GetBankBalance(Helper::CurrentBankNum);
        ui->label_ckinfobalance->setText("存款金额:"+DepositMoneyCount+"元");
        ui->label_ckinfokybalance->setText("账户当前余额:"+CardBalance+"元");*/
        QString CardBalance=Sqloperate::GetBankBalance(Helper::CurrentBankNum);
        ui->stackedWidget->setCurrentWidget(ui->DepositOKINFOPage);
        ui->label_ckcardid->setText("存款账号:"+Helper::CurrentBankNum);
        ui->label_ckBalance->setText("账户当前余额:"+CardBalance+"元");
    }

}
//确定转账
void Widget::on_btn_ZKOK_clicked()
{

    bool ok=Sqloperate::TransferState(ZZInfo[1],ZZInfo[0],Helper::TransferState);
    if(ok)
    {
        ui->stackedWidget->setCurrentWidget(ui->TransactionInfopage);
        ui->label_ckinfobalance->setText("转账金额:"+ZZInfo[1]+"元");
        QString CardBalance=Sqloperate::GetBankBalance(Helper::CurrentBankNum);
        ui->label_ckinfokybalance->setText("账户当前余额:"+CardBalance+"元");
    }

}
//绑定视图显示
void Widget::BindTableViewInfo(QString Sql, QTableView *tableView, QString columnNames[], int columnWidths[])
{
    QueryModel=new QSqlQueryModel(this);
    QString sql=Sql;
    QueryModel->setQuery(sql);//进行查询,数据保存到模型中
    tableView->setModel(QueryModel);//把数据添加到表格内

    //依次设置列标题、列宽等
    for (int i = 0;i<tableView->model()->columnCount();i++)
    {
        QueryModel->setHeaderData(i,Qt::Horizontal,columnNames[i]);     //设置列标题
        tableView->setColumnWidth(i,columnWidths[i]);                   //设置列宽
    }

    tableView->horizontalHeader()->setHighlightSections(false);         //点击表头时不对表头光亮
    tableView->setSelectionMode(QAbstractItemView::ContiguousSelection);//选中模式为多行选中
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);     //选中整行
    /*tableView->setStyleSheet( "QTableView::item:hover{background-color:rgb(92,188,227,200)}"
                              "QTableView::item:selected{background-color:#1B89A1}");*/
}
//凭条视图显示单击
void Widget::on_tableView_clicked(const QModelIndex &index)
{

    QSqlQueryModel userMode(ui->tableView);
    QString Sql="";
    if(VoucherTake=="取款凭条")
       Sql="select * from Withdraw;";
    else if(VoucherTake=="存款凭条")
        Sql="select * from Deposit;";
    else
        Sql="select Tran_anum,Tran_sidecid,Tran_date,Tran_money from Trandfers;";
    userMode.setQuery(Sql);
    int Row=ui->tableView->currentIndex().row();
    QSqlRecord record=userMode.record(Row);

    ui->led_DanNum->setText(record.value(0).toString());
    VoucherBalance=record.value(3).toString();
}

//取款凭条
void Widget::on_Btn_QKVoucher_clicked()
{
    VoucherTake="取款凭条";
    ui->Btn_QKVoucher->setEnabled(false);
    ui->Btn_CKVoucher->setEnabled(true);
    ui->Btn_ZZVoucher->setEnabled(true);

    QString sql="select * from Withdraw;";
    QString colName[]={"操作单号","操作卡号","操作时间","操作金额","取款"};
    int colWidth[]={200,180,200,160,100};
    BindTableViewInfo(sql,ui->tableView,colName,colWidth);
}

//存款凭条
void Widget::on_Btn_CKVoucher_clicked()
{
    VoucherTake="存款凭条";
    ui->Btn_QKVoucher->setEnabled(true);
    ui->Btn_CKVoucher->setEnabled(false);
    ui->Btn_ZZVoucher->setEnabled(true);

    QString sql="select * from Deposit;";
    QString colName[]={"操作单号","操作卡号","操作时间","操作金额","取款"};
    int colWidth[]={200,180,200,160,100};
    BindTableViewInfo(sql,ui->tableView,colName,colWidth);
}

//转账凭条
void Widget::on_Btn_ZZVoucher_clicked()
{
    VoucherTake="转账凭条";
    ui->Btn_QKVoucher->setEnabled(true);
    ui->Btn_CKVoucher->setEnabled(true);
    ui->Btn_ZZVoucher->setEnabled(false);

    QString sql="select Tran_anum,Tran_sidecid,Tran_date,Tran_money from Trandfers;";
    QString colName[]={"操作单号","操作卡号","操作时间","操作金额","取款","冠字号"};
    int colWidth[]={200,180,180,160,100,100};
    BindTableViewInfo(sql,ui->tableView,colName,colWidth);
}

//打印凭条
void Widget::on_btn_printVoucher_clicked()
{
    QString DanNum=ui->led_DanNum->text();
    if(DanNum.isEmpty())
    {
        Helper::ShowMessageBoxError("单号不能为空");
        return;
    }

    QString UserID=Sqloperate::GetUserID(Helper::CurrentBankNum);
    if(Sqloperate::PrintVoucher(Helper::CurrentBankNum,UserID,VoucherBalance,VoucherTake,"101001"," "))
    {
        Helper::ShowMessageBoxError("打印凭条成功,请领取凭条,屏幕将在3秒后返回！");
        //休息
        QTime time;
        time.start();
        while(time.elapsed() < 2000) //等待时间流逝2秒钟
            QCoreApplication::processEvents();
        ui->stackedWidget->setCurrentWidget(ui->InitPage);
        return;
    }
}
//密码重置
void Widget::on_btn_pwdclear_clicked()
{
    ui->led_oldpwd->clear();
    ui->led_newpwd->clear();
    ui->led_renewpwd->clear();
}
