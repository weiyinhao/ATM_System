#include "widget.h"
#include "ui_widget.h"
#include "Config/sqlserver.h"
#include <QDebug>
#include <QMessageBox>
#include "Config/helper.h"
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->InitWindow();
}

Widget::~Widget()
{
    delete ui;
}
//初始化
void Widget::InitWindow()
{
    //默认为首页
    ui->stackedWidget->setCurrentWidget(ui->FirstPage);
    ui->label_title->setText("首页");

    //绑定计时器信号
    timer=new QTimer(this);
    connect(timer,&QTimer::timeout,this,&Widget::updateTimer);
    timer->start(1000);//启动1秒更新一次

    this->setWindowFlags(windowFlags()&~Qt::WindowMaximizeButtonHint);// 禁止最大化按钮
    this->setFixedSize(this->width(),this->height());//禁止拖拽
    this->setWindowIcon(QIcon(":/img/ATM.ico"));//生成窗口图标
}
void Widget::updateTimer()
{
    //获取当前时间
    QString currentTime="当前时间: "+QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")+"   ";
    ui->label_time->setText(currentTime);
}
//首页
void Widget::on_Btn_FirstPage_clicked()
{
    //设置按钮状态
    ui->Btn_FirstPage->setEnabled(false);
    ui->Btn_ATM->setEnabled(true);
    ui->Btn_Close->setEnabled(true);
    ui->BtnBankCard->setEnabled(true);
    ui->Btn_Money->setEnabled(true);

    ui->label_title->setText("首页");

    ui->stackedWidget->setCurrentWidget(ui->FirstPage);
}

//银行卡管理
void Widget::on_BtnBankCard_clicked()
{
    ui->Btn_FirstPage->setEnabled(true);
    ui->Btn_ATM->setEnabled(true);
    ui->Btn_Close->setEnabled(true);
    ui->BtnBankCard->setEnabled(false);
    ui->Btn_Money->setEnabled(true);

    ui->label_title->setText("银行卡管理");

    ui->stackedWidget->setCurrentWidget(ui->BankCardPage);

    //设置视图
    QString Sql="select BankCard.Card_cid,BankCard.Card_pwd,BankCard.User_sid,Customer.User_name,Bank.Bank_name,Card_balance,Card_date,Card_state,Provincial.Provincial_name,City.City_name from BankCard,Bank,Provincial,City,Customer where BankCard.Ban_id=Bank.Bank_id and BankCard.Provincial_anum=Provincial.Provincial_anum and BankCard.City_anum=City.City_anum and Bank.Bank_id=BankCard.Ban_id and Customer.User_sid=BankCard.User_sid";
    QString colName[]={"银行卡号","银行卡密","开户人身份证","开户人姓名","所属银行","余额","办卡时间","银行卡状态","开通省份","开通地区"};
    int colWidth[]={180,160,190,130,160,100,140,100,100,100};
    BindTableViewInfo(Sql,ui->tableView_BankCard,colName,colWidth);
}

//ATM管理
void Widget::on_Btn_ATM_clicked()
{
    ui->Btn_FirstPage->setEnabled(true);
    ui->Btn_ATM->setEnabled(false);
    ui->Btn_Close->setEnabled(true);
    ui->BtnBankCard->setEnabled(true);
    ui->Btn_Money->setEnabled(true);

    ui->label_title->setText("ATM管理");

    ui->stackedWidget->setCurrentWidget(ui->ATMPage);

    //初始化ATM视图
    QString Sql="select * from ATMEquipment;";
    QString colName[]={"ATM机设备编号","ATM机设备名称","当前设备余额","设备状态","设备信息备注"};
    int colWidth[]={200,180,200,160,160};
    BindTableViewInfo(Sql,ui->tableView_ATMEquit,colName,colWidth);
}

//钞票管理
void Widget::on_Btn_Money_clicked()
{
    ui->Btn_FirstPage->setEnabled(true);
    ui->Btn_ATM->setEnabled(true);
    ui->Btn_Close->setEnabled(true);
    ui->BtnBankCard->setEnabled(true);
    ui->Btn_Money->setEnabled(false);

    ui->label_title->setText("钞票管理");

    ui->stackedWidget->setCurrentWidget(ui->MoneyPage);
}

//注销
void Widget::on_Btn_Close_clicked()
{
    this->close();
}
//将数据绑定到表格视图种
void Widget::BindTableViewInfo(QString Sql, QTableView *tableView,QString columnNames[], int columnWidths[])
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
//单击表格内容
void Widget::on_tableView_BankCard_clicked(const QModelIndex &index)
{
    QSqlQueryModel userMode(ui->tableView_BankCard);
    QString Sql="select BankCard.Card_cid,BankCard.Card_pwd,BankCard.User_sid,Customer.User_name,Bank.Bank_name,Card_balance,Card_date,Card_state,Provincial.Provincial_name,City.City_name from BankCard,Bank,Provincial,City,Customer where BankCard.Ban_id=Bank.Bank_id and BankCard.Provincial_anum=Provincial.Provincial_anum and BankCard.City_anum=City.City_anum and Bank.Bank_id=BankCard.Ban_id and Customer.User_sid=BankCard.User_sid";
    userMode.setQuery(Sql);
    int Row=ui->tableView_BankCard->currentIndex().row();
    QSqlRecord record=userMode.record(Row);

    ui->led_BankCarid_2->setText(record.value(0).toString());
    ui->led_UserID->setText(record.value(2).toString());
    ui->led_pwd->setText(record.value(1).toString());
    ui->led_BankMoney->setText(record.value(5).toString());
    ui->cob_BankState_2->setCurrentText(record.value(7).toString());
    ui->cob_Province->setCurrentText(record.value(8).toString());
    ui->cob_city->setCurrentText(record.value(9).toString());
}

//更新银行卡
void Widget::on_btn_Banjupdate_clicked()
{
    QString BankPwd=ui->led_pwd->text();
    QString BankMoney=ui->led_BankMoney->text();
    QString BankState=ui->cob_BankState_2->currentText();

    //更新信息不能为空
    if(BankPwd.isEmpty() || BankMoney.isEmpty() || BankState.isEmpty())
    {
        return;
    }
    //进行银行卡数据更新
    //QString sql="update BankCard  set Card_pwd='"+BankPwd+"',Card_balance='"+BankMoney+"',Card_state='"+BankState+"' where Card_cid='"+ui->led_BankCarid_2->text()+"';";
    if(SqlServer::BankDateUpdate(BankPwd,BankMoney,BankState,ui->led_BankCarid_2->text()))
    {
        QMessageBox::information(this,"提示","更新成功",QMessageBox::Yes);
        //设置视图
        QString Sql="select BankCard.Card_cid,BankCard.Card_pwd,BankCard.User_sid,Customer.User_name,Bank.Bank_name,Card_balance,Card_date,Card_state,Provincial.Provincial_name,City.City_name from BankCard,Bank,Provincial,City,Customer where BankCard.Ban_id=Bank.Bank_id and BankCard.Provincial_anum=Provincial.Provincial_anum and BankCard.City_anum=City.City_anum and Bank.Bank_id=BankCard.Ban_id and Customer.User_sid=BankCard.User_sid";
        QString colName[]={"银行卡号","银行卡密","开户人身份证","开户人姓名","所属银行","余额","办卡时间","银行卡状态","开通省份","开通地区"};
        int colWidth[]={180,160,190,130,160,100,140,100,100,100};
        BindTableViewInfo(Sql,ui->tableView_BankCard,colName,colWidth);
    }
}

//开通新银行卡
void Widget::on_btn_BankKT_clicked()
{
    QString BankCardID=ui->led_BankCaridid->text();
    QString UserID=ui->led_UserID_2->text();
    QString BankPwd=ui->led_BankPwd->text();
    QString BankBalance=ui->led_BankMoeny->text();
    QString Provincial=ui->cob_Province_2->currentText();
    QString City=ui->cob_city_2->currentText();
    QString SSBank=ui->cob_SSBank->currentText();

    if(BankCardID.isEmpty() || UserID.isEmpty() || BankPwd.isEmpty() || BankBalance.isEmpty() || Provincial.isEmpty())
    {
        QMessageBox::information(this,"提示","银行卡相关信息不能为空!",QMessageBox::Yes);
        return;
    }
    if(BankCardID.length()!=19)
    {
        QMessageBox::information(this,"提示","请输入正确的银行卡!",QMessageBox::Yes);
        return;
    }
    if(BankPwd.length()!=6)
    {
        QMessageBox::information(this,"提示","银行卡密码必须为6位!",QMessageBox::Yes);
        return;
    }
    if(SqlServer::isBankCard(BankCardID))
    {
        QMessageBox::information(this,"提示","当前银行卡已经存在,无法开卡!",QMessageBox::Yes);
        return;
    }
    if(!Helper::Luhn(BankCardID))
    {
        QMessageBox::information(this,"提示","请输入正确的银行卡号!",QMessageBox::Yes);
        return;
    }
    SqlServer::KTNewBankCard(BankCardID,BankPwd,UserID,BankBalance,"正常",SSBank,Provincial,City);
    //设置视图
    QString Sql="select BankCard.Card_cid,BankCard.Card_pwd,BankCard.User_sid,Customer.User_name,Bank.Bank_name,Card_balance,Card_date,Card_state,Provincial.Provincial_name,City.City_name from BankCard,Bank,Provincial,City,Customer where BankCard.Ban_id=Bank.Bank_id and BankCard.Provincial_anum=Provincial.Provincial_anum and BankCard.City_anum=City.City_anum and Bank.Bank_id=BankCard.Ban_id and Customer.User_sid=BankCard.User_sid";
    QString colName[]={"银行卡号","银行卡密","开户人身份证","开户人姓名","所属银行","余额","办卡时间","银行卡状态","开通省份","开通地区"};
    int colWidth[]={180,160,190,130,160,100,140,100,100,100};
    BindTableViewInfo(Sql,ui->tableView_BankCard,colName,colWidth);

}

//注销卡
void Widget::on_btn_Bankcancel_clicked()
{
    QString BankCirdID=ui->led_BankCird->text();

    if(BankCirdID.isEmpty())
    {
        QMessageBox::information(this,"提示","银行卡信息不能为空!",QMessageBox::Yes);
        return;
    }
    if(BankCirdID.length()!=19)
    {
        QMessageBox::information(this,"提示","请输入正确的银行卡!",QMessageBox::Yes);
        return;
    }
    if(SqlServer::isBankCard(BankCirdID))
    {
        QMessageBox::information(this,"提示","当前银行卡不存在,无法注销!",QMessageBox::Yes);
        return;
    }
    if(SqlServer::deleteBankCard(BankCirdID))
    {
        QMessageBox::information(this,"提示","注销成功!",QMessageBox::Yes);
        //设置视图
        QString Sql="select BankCard.Card_cid,BankCard.Card_pwd,BankCard.User_sid,Customer.User_name,Bank.Bank_name,Card_balance,Card_date,Card_state,Provincial.Provincial_name,City.City_name from BankCard,Bank,Provincial,City,Customer where BankCard.Ban_id=Bank.Bank_id and BankCard.Provincial_anum=Provincial.Provincial_anum and BankCard.City_anum=City.City_anum and Bank.Bank_id=BankCard.Ban_id and Customer.User_sid=BankCard.User_sid";
        QString colName[]={"银行卡号","银行卡密","开户人身份证","开户人姓名","所属银行","余额","办卡时间","银行卡状态","开通省份","开通地区"};
        int colWidth[]={180,160,190,130,160,100,140,100,100,100};
        BindTableViewInfo(Sql,ui->tableView_BankCard,colName,colWidth);
        return;
    }

}

//银行卡条件查询
void Widget::on_btn_conditionQuery_clicked()
{
    QString BankCarid=ui->led_BankCarid->text();
    QString UserID=ui->led_ID->text();
    QString BankState=ui->cob_BankState->currentText();

    QString Sql="select BankCard.Card_cid,BankCard.Card_pwd,BankCard.User_sid,Customer.User_name,Bank.Bank_name,Card_balance,Card_date,Card_state,Provincial.Provincial_name,City.City_name from BankCard,Bank,Provincial,City,Customer where BankCard.Ban_id=Bank.Bank_id and BankCard.Provincial_anum=Provincial.Provincial_anum and BankCard.City_anum=City.City_anum and Bank.Bank_id=BankCard.Ban_id and Customer.User_sid=BankCard.User_sid and BankCard.Card_cid LIKE '%"+BankCarid+"%' and BankCard.User_sid LIKE '%"+UserID+"%' and Card_state='"+BankState+"';";
    qDebug()<<Sql;
    QString colName[]={"银行卡号","银行卡密","开户人身份证","开户人姓名","所属银行","余额","办卡时间","银行卡状态","开通省份","开通地区"};
    int colWidth[]={180,160,190,130,160,100,140,100,100,100};
    BindTableViewInfo(Sql,ui->tableView_BankCard,colName,colWidth);
}

//银行卡查询全部
void Widget::on_btn_QeuryQBBank_clicked()
{
    QString Sql="select BankCard.Card_cid,BankCard.Card_pwd,BankCard.User_sid,Customer.User_name,Bank.Bank_name,Card_balance,Card_date,Card_state,Provincial.Provincial_name,City.City_name from BankCard,Bank,Provincial,City,Customer where BankCard.Ban_id=Bank.Bank_id and BankCard.Provincial_anum=Provincial.Provincial_anum and BankCard.City_anum=City.City_anum and Bank.Bank_id=BankCard.Ban_id and Customer.User_sid=BankCard.User_sid";
    QString colName[]={"银行卡号","银行卡密","开户人身份证","开户人姓名","所属银行","余额","办卡时间","银行卡状态","开通省份","开通地区"};
    int colWidth[]={180,160,190,130,160,100,140,100,100,100};
    BindTableViewInfo(Sql,ui->tableView_BankCard,colName,colWidth);
}

//ATM设备条件查询
void Widget::on_btn_ATMTJCX_clicked()
{
    QString ATMEquitID=ui->led_ATMEquiID->text();
    QString ATMEquitState=ui->cob_ATMState->currentText();


    //初始化ATM视图
    QString Sql="select * from ATMEquipment where Equipment_id LIKE '%"+ATMEquitID+"%' and Equipment_state='"+ATMEquitState+"';";
    QString colName[]={"ATM机设备编号","ATM机设备名称","当前设备余额","设备状态","设备信息备注"};
    int colWidth[]={200,180,200,160,160};
    BindTableViewInfo(Sql,ui->tableView_ATMEquit,colName,colWidth);
}

//查询全部ATM设备
void Widget::on_Btn_QBATM_clicked()
{
    //清空其它控件
    ui->led_ATMEquiID->clear();
    ui->cob_ATMState->setCurrentIndex(0);

    //初始化ATM视图
    QString Sql="select * from ATMEquipment;";
    QString colName[]={"ATM机设备编号","ATM机设备名称","当前设备余额","设备状态","设备信息备注"};
    int colWidth[]={200,180,200,160,160};
    BindTableViewInfo(Sql,ui->tableView_ATMEquit,colName,colWidth);
}

//ATM视图被单击
void Widget::on_tableView_ATMEquit_clicked(const QModelIndex &index)
{
    QSqlQueryModel userMode(ui->tableView_ATMEquit);
    QString Sql="select * from ATMEquipment;";
    userMode.setQuery(Sql);
    int Row=ui->tableView_ATMEquit->currentIndex().row();
    QSqlRecord record=userMode.record(Row);

    ui->led_ATMEquiID_2->setText(record.value(0).toString());
    ui->cob_ATMEquiState->setCurrentText(record.value(3).toString());
    ui->led_balance->setText(record.value(2).toString());
}

//ATM设备更新
void Widget::on_btn_ATMEquitUpdate_clicked()
{
    QString ATMEquiID=ui->led_ATMEquiID_2->text();
    QString ATMEquiState=ui->cob_ATMEquiState->currentText();
    QString ATMEquitbalance=ui->led_balance->text();

    if(ATMEquiID.isEmpty() || ATMEquiState.isEmpty() || ATMEquitbalance.isEmpty())
    {
        QMessageBox::information(this,"错误","ATM设备信息不能为空!",QMessageBox::Yes);
        return;
    }
    if(SqlServer::UpdateATMEquit(ATMEquiID,ATMEquiState,ATMEquitbalance))
    {
        QMessageBox::information(this,"提示","设备更新成功!",QMessageBox::Yes);
        //初始化ATM视图
        QString Sql="select * from ATMEquipment;";
        QString colName[]={"ATM机设备编号","ATM机设备名称","当前设备余额","设备状态","设备信息备注"};
        int colWidth[]={200,180,200,160,160};
        BindTableViewInfo(Sql,ui->tableView_ATMEquit,colName,colWidth);
        return;
    }else
    {
        QMessageBox::information(this,"错误","该设备不存在,无法更新!",QMessageBox::Yes);
    }


}
//添加ATM设备
void Widget::on_btn_TJATMQuit_clicked()
{
    QString ATMEquiID=ui->led_ATMEquitID->text();
    QString ATMEquitName=ui->led_ATMEquitName->text();
    QString ATMEquitbalance=ui->led_ATMBalance->text();

    if(ATMEquiID.isEmpty() || ATMEquitName.isEmpty() || ATMEquitbalance.isEmpty())
    {
        QMessageBox::information(this,"错误","ATM设备信息不能为空!",QMessageBox::Yes);
        return;
    }
    if(SqlServer::AddATMEquit(ATMEquiID,ATMEquitName,ATMEquitbalance))
    {
        QMessageBox::information(this,"提示","添加新设备成功!",QMessageBox::Yes);
        //初始化ATM视图
        QString Sql="select * from ATMEquipment;";
        QString colName[]={"ATM机设备编号","ATM机设备名称","当前设备余额","设备状态","设备信息备注"};
        int colWidth[]={200,180,200,160,160};
        BindTableViewInfo(Sql,ui->tableView_ATMEquit,colName,colWidth);
        return;
    }else
    {
        QMessageBox::information(this,"提示","该设备已存在,无法添加!",QMessageBox::Yes);
    }

}

//删除设备
void Widget::on_btn_ATMEquitDelete_clicked()
{
    QString ATMEquitID=ui->led_ATMEquitID_2->text();

    if(ATMEquitID.isEmpty())
    {
        QMessageBox::information(this,"提示","请输入设备编号!",QMessageBox::Yes);
        return;
    }
    if(SqlServer::isATMEquit(ATMEquitID))
    {
         QMessageBox::information(this,"提示","不存在该设备,无法删除!",QMessageBox::Yes);
         return;
    }
    if(SqlServer::DeleteATMEquit(ATMEquitID))
    {
        QMessageBox::information(this,"提示","设备删除成功!",QMessageBox::Yes);
        //初始化ATM视图
        QString Sql="select * from ATMEquipment;";
        QString colName[]={"ATM机设备编号","ATM机设备名称","当前设备余额","设备状态","设备信息备注"};
        int colWidth[]={200,180,200,160,160};
        BindTableViewInfo(Sql,ui->tableView_ATMEquit,colName,colWidth);
        return;
    }

}
//清空
void Widget::on_Btn_ATMClear_clicked()
{
    ui->led_ATMEquitID->clear();
    ui->led_ATMEquitName->clear();
    ui->led_ATMBalance->clear();
}

//存入钞票
void Widget::on_Btn_MoneyCR_clicked()
{
    QString MonyeId=ui->led_MoneyID->text();
    QString MoneyNum=ui->led_MoneyNum->text();
    QString MonyeState=ui->cob_MoneyState->currentText();

    if(MonyeId.isEmpty() || MoneyNum.isEmpty())
    {
        QMessageBox::information(this,"错误","设备编号或数量不能为空!",QMessageBox::Yes);
        return;
    }

    if(MoneyNum.toInt()<=0)
    {
        QMessageBox::information(this,"错误","钞票数量不能小于等于0!",QMessageBox::Yes);
        return;
    }
    map[MonyeState]=MoneyNum;//保存到集合类种
    QString Item=QDateTime::currentDateTime().toString("yyyy-MM-dd")+":<"+MonyeState+","+MoneyNum+">";
    ui->textEdit->append(Item);
    on_btn_MoneyClear_clicked();
}
//清空
void Widget::on_btn_MoneyClear_clicked()
{
    ui->led_MoneyID->clear();
    ui->led_MoneyNum->clear();
    ui->cob_MoneyState->setCurrentText("正常");
}
