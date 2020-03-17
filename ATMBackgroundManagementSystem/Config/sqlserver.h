#ifndef SQLSERVER_H
#define SQLSERVER_H
#include <QObject>
#include <QSqlQuery>
#include <QDebug>
#include <QDateTime>
#include <QMessageBox>
class SqlServer : public QObject
{
    Q_OBJECT
public:
    explicit SqlServer(QObject *parent = nullptr);

signals:

public slots:

public:
    //银行卡数据更新
    static bool BankDateUpdate(QString BankPwd,QString BankMoney,QString BankState,QString Card_cid)
    {
        //进行数据更新
        QString sql="update BankCard  set Card_pwd='"+BankPwd+"',Card_balance='"+BankMoney+"',Card_state='"+BankState+"' where Card_cid='"+Card_cid+"';";
        QSqlQuery query;
        if(query.exec(sql))
        {
            return true;
        }
        return false;

    }
    //开通新银行卡
    static bool KTNewBankCard(QString Card_cid,QString card_pwd,QString User_sid,QString Card_balance,QString Card_state,QString SSBank,QString Provincial_name,QString City_name)
    {
        //查询银行,省份，地区编号
        QString sqlBank="select Bank_id from Bank where Bank_name='"+SSBank+"';";
        QString sqlProvincial="select Provincial_anum from Provincial where Provincial_name='"+Provincial_name+"'";
        QString sqlCity="select City_anum from City where City_name='"+City_name+"'";
        QSqlQuery queryBank;
        queryBank.exec(sqlBank);
        queryBank.next();
        QSqlQuery queryProvincial;
        queryProvincial.exec(sqlProvincial);
        queryProvincial.next();
        QSqlQuery queryCity;
        queryCity.exec(sqlCity);
        queryCity.next();
        QString Bank_Id=queryBank.value(0).toString();
        QString Bank_Provincialid=queryProvincial.value(0).toString();
        QString Bank_Cityid=queryCity.value(0).toString();
        QString currentTimer=QDateTime::currentDateTime().toString("yyyy-MM-dd");

        QString sqlInsertNewBankCard="insert into BankCard values('"+Card_cid+"','"+card_pwd+"','"+User_sid+"','"+Bank_Id+"',"+Card_balance+",'"+currentTimer+"','"+Card_state+"','"+Bank_Provincialid+"','"+Bank_Cityid+"');";
        QSqlQuery queryInsertNewBankCard;
        if(queryInsertNewBankCard.exec(sqlInsertNewBankCard))
        {
            qDebug()<<"成功";
            return true;
        }
        return false;

    }
    //注销银行卡
    static bool deleteBankCard(QString BankCard)
    {
        QString sql="delete from BankCard where Card_cid='"+BankCard+"';";
        QSqlQuery query;
        if(query.exec(sql))
        {
            return true;
        }
        return false;
    }
    //查询银行卡是否存在
    static bool isBankCard(QString BankCard)
    {
        QString sql="select Card_cid from BankCard where Card_cid='"+BankCard+"';";
        QSqlQuery query;
        if(query.exec(sql))
        {
            return false;
        }
        return true;
    }
    //添加ATM设备
    static bool AddATMEquit(QString ATMEquiID,QString ATMEquitName,QString ATMEquiBalance)
    {

        QString sql="insert into ATMEquipment values('"+ATMEquiID+"','"+ATMEquitName+"',"+ATMEquiBalance+",'正常',' ');";
        QSqlQuery query;
        if(query.exec(sql))
        {
            return true;
        }
        return false;
    }
    //删除设备
    static bool DeleteATMEquit(QString ATMEquiID)
    {
        QString sql="delete from ATMEquipment where Equipment_id='"+ATMEquiID+"';";
        QSqlQuery query;
        if(query.exec(sql))
        {
            return true;
        }
        return false;
    }
    //更新设备
    static bool UpdateATMEquit(QString ATMEquiID,QString Equipment_state,QString Equipment_Balance)
    {
        QString sql="update ATMEquipment set Equipment_state='"+Equipment_state+"',Equipment_balance='"+Equipment_Balance+"' where Equipment_id='"+ATMEquiID+"';";
        QSqlQuery query;
        if(query.exec(sql))
        {
            return true;
        }
        return false;
    }
    //查看该设备是否存在
    static bool isATMEquit(QString ATMEquiID)
    {
        QString sql="select Equipment_id from ATMEquipment where Equipment_id='"+ATMEquiID+"';";
        QSqlQuery query;

        query.exec(sql);
        query.next();
        QString ok=query.value(0).toString();
        qDebug()<<ok;
        if(ok=="")
        {
            return true;
        }
        return false;
    }
};
#endif // SQLSERVER_H
