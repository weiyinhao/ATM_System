#ifndef SQLOPERATE_H
#define SQLOPERATE_H
#include <QObject>
#include <QSqlQuery>
#include <QVariant>
#include <QTime>
#include <Config/helper.h>
#include <QDebug>
class Sqloperate : public QObject
{
    Q_OBJECT
public:
    explicit Sqloperate(QObject *parent = nullptr);

signals:

public slots:

public:
    //获取银行卡密码
    static QString GetBankCardPwd(QString BankCardID)
    {

        QSqlQuery query;
        QString sql="select Card_pwd from BankCard where Card_cid='"+BankCardID+"';";
        query.exec(sql);
        query.next();
        QString BankCardPwd=query.value(0).toString();
        return BankCardPwd;
    }
    //获取银行卡余额
    static QString GetBankBalance(QString BankCardID)
    {
        QSqlQuery query;
        //QString sql="select Card_balance from BankCard where Card_cid='6215982920990003922';";
        QString sql="select Card_balance from BankCard where Card_cid='"+BankCardID+"';";
        query.exec(sql);
        query.next();
        QString Card_balance=query.value(0).toString();
        return Card_balance;
    }
    //获取银行卡状态
    static QString GetBankState(QString BankCardID)
    {
        QSqlQuery query;
        //QString sql="select Card_balance from BankCard where Card_cid='6215982920990003922';";
        QString sql="select Card_state from BankCard where Card_cid='"+BankCardID+"';";
        query.exec(sql);
        query.next();
        QString Card_state=query.value(0).toString();
        return Card_state;
    }
    //获取银行卡所处银行
    static QString GetBankName(QString BankCardID)
    {
        QSqlQuery query;
        //QString sql="select Card_balance from BankCard where Card_cid='6215982920990003922';";
        QString sql="select Bank_name from BankCard,Bank where Bank.Bank_id=BankCard.Ban_id and Card_cid='"+BankCardID+"';";
        query.exec(sql);
        query.next();
        QString BankName=query.value(0).toString();
        return BankName;
    }
    //获取银行卡持有人
    static QString GetBankCaridName(QString BankCardID)
    {
        QSqlQuery query;
        //QString sql="select Card_balance from BankCard where Card_cid='6215982920990003922';";
        QString sql="select User_name from BankCard,Customer where Customer.User_sid=BankCard.User_sid and Card_cid='"+BankCardID+"';";
        query.exec(sql);
        query.next();
        QString UserName=query.value(0).toString();
        return UserName;
    }
    //获取用户身份证号
    static QString GetUserID(QString BankCardID)
    {
        QSqlQuery query;

        QString sql="select Customer.User_sid from BankCard,Customer where Customer.User_sid=BankCard.User_sid and Card_cid='"+Helper::CurrentBankNum+"';";
        query.exec(sql);
        query.next();
        QString User_sid=query.value(0).toString();
        return User_sid;
    }
    //修改密码
    static bool ChangePwd(QString oldpwd,QString newpwd)
    {
        QSqlQuery query;
        QString sql="update BankCard set Card_pwd='"+newpwd+"' where Card_pwd='"+oldpwd+"';";
        if(query.exec(sql))
            return true;
        return false;
    }
    //存款处理
    static bool Deposit(QString MoneyCount,QString BankNum)
    {
        //把存款信息插入存款表内
        int Count=Sqloperate::GetTableDateCount("Deposit");
        QString DepNum= "D"+QDateTime::currentDateTime().toString("yyyyMMdd")+QString::number(Count);
        //QString BankNum=Helper::CurrentBankNum;
        QString currentTime=QDateTime::currentDateTime().toString("yyyy-MM-dd");
        QSqlQuery query;
        QString sql="insert into Deposit values('"+DepNum+"','"+Helper::CurrentBankNum+"','"+currentTime+"','"+MoneyCount+"');";
        if(query.exec(sql))
        {
            //更新银行卡余额
            QSqlQuery query2;
            QString sql2="update BankCard set Card_balance+="+MoneyCount+" where Card_cid='"+Helper::CurrentBankNum+"';";
            if(query2.exec(sql2))
                return true;
            return false;
        }
        return false;

    }
    //取款处理
    static bool Withdraw(QString WithdrawMoneyCount,QString BankNum)
    {
        //把取款信息插入存款表内
        int Count=Sqloperate::GetTableDateCount("Withdraw");
        QString DepNum= "W"+QDateTime::currentDateTime().toString("yyyyMMdd")+QString::number(Count);
        //QString BankNum=Helper::CurrentBankNum;
        QString currentTime=QDateTime::currentDateTime().toString("yyyy-MM-dd");
        QSqlQuery query;
        QString sql="insert into Withdraw values('"+DepNum+"','"+Helper::CurrentBankNum+"','"+currentTime+"','"+WithdrawMoneyCount+"');";
        if(query.exec(sql))
        {
            //更新银行卡余额
            QSqlQuery query2;
            QString sql2="update BankCard set Card_balance-="+WithdrawMoneyCount+" where Card_cid='"+Helper::CurrentBankNum+"';";
            if(query2.exec(sql2))
                return true;
            return false;
        }
        return false;

    }
    //获取存款金额
    static QString GetCKMonecy(QString Dep_anum)
    {
        QSqlQuery query;
        QString sql="select Dep_money from Deposit where Dep_anum='"+Dep_anum+"';";
        query.exec(sql);
        query.next();
        QString CKMonecy=query.value(0).toString();
        return CKMonecy;
    }
    //获取表中数据个数
    static int GetTableDateCount(QString Table)
    {
        QSqlQuery query;
        QString sql="";
        if(Table=="Deposit")
            sql="select COUNT(*) from Deposit;";
        else if(Table=="Withdraw")
            sql="select COUNT(*) from Withdraw;";
        else if(Table=="Trandfers")
            sql="select COUNT(*) from Trandfers";
        else if(Table=="Voucher")
            sql="select COUNT(*) from Voucher";
        query.exec(sql);
        query.next();
        int count=query.value(0).toInt();
        qDebug()<<count;
        return count;
    }
    //转账操作
    static bool TransferState(QString MoneyCount,QString DFBankCardID,QString remark)
    {
        //添加转账表
        int Count=Sqloperate::GetTableDateCount("Trandfers");
        QString TransNum= "T"+QDateTime::currentDateTime().toString("yyyyMMdd")+QString::number(Count);
        //QString BankNum=Helper::CurrentBankNum;
        QString currentTime=QDateTime::currentDateTime().toString("yyyy-MM-dd");
        QSqlQuery query;
        QString sql="insert into Trandfers values('"+TransNum+"','"+Helper::CurrentBankNum+"','"+DFBankCardID+"','"+currentTime+"','"+MoneyCount+"','"+remark+"');";
        if(query.exec(sql))
        {
            QSqlQuery query2;
            QString sql2="";
            if(remark=="行内转账")
            {
                //自己账户减少
                sql2="update BankCard set Card_balance-="+MoneyCount+" where Card_cid='"+Helper::CurrentBankNum+"';";
            }
            else
            {
                //自己账户减少，并减少额外手续费
                sql2="update BankCard set Card_balance-="+QString::number(MoneyCount.toInt()-Helper::GetCommissionCharge(MoneyCount))+" where Card_cid='"+Helper::CurrentBankNum+"';";
            }
            if(query2.exec(sql2))
            {
                //对方账户增加
                QSqlQuery query3;
                QString sql3="update BankCard set Card_balance+="+MoneyCount+" where Card_cid='"+DFBankCardID+"';";
                if(query3.exec(sql3))
                    return true;
                return false;
            }
            return false;

        }
        return false;
    }
    //打印凭条
    static bool PrintVoucher(QString Card_cid,QString User_sid,QString Balance,QString type,QString Equipment_id, QString Voucher_Crown)
    {
        int Count=Sqloperate::GetTableDateCount("Voucher");
        QString VoucherNum= "V"+QDateTime::currentDateTime().toString("yyyyMMdd")+QString::number(Count);
        QString currentTimer=QDateTime::currentDateTime().toString("yyyy-MM-dd");
        QString sql="insert into Voucher values('"+VoucherNum+"','"+Card_cid+"','"+User_sid+"',"+Balance+",'"+currentTimer+"','"+type+"','"+Equipment_id+"','"+Voucher_Crown+"');";
        qDebug()<<sql;
        QSqlQuery query;
        if(query.exec(sql))
        {
            return true;
        }
        return false;
    }
};

#endif // SQLOPERATE_H
