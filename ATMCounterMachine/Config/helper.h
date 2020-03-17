#ifndef HELPER_H
#define HELPER_H

#include <QObject>
#include <QMessageBox>
class Helper : public QObject
{
    Q_OBJECT
public:
    explicit Helper(QObject *parent = nullptr);

    static void ShowMessageBoxInfo(QString info);//显示信息框
    static void ShowMessageBoxError(QString info);//显示错误框
    static int ShowMessageBoxQuesion(QString info);//显示询问框

    static bool Luhn(QString text);//银行卡校验Luhn算法
    static int GetCommissionCharge(QString MoneyNum);
//记录缓存信息
public:
    static QString CurrentBank;
    static QString CurrentBankNum;
    static QString CurrentBankPwd;
    static QString TransferState;
    static QString DFBankNum;
    static QString ZKMoney;
signals:

public slots:

};

#endif // HELPER_H
