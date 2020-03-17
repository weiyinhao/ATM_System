#include "helper.h"
#include "mesaagedialog.h"
#include <QDebug>
QString Helper::CurrentBank="";
QString Helper::CurrentBankNum="";
QString Helper::CurrentBankPwd="";
QString Helper::TransferState="行内转账";
QString Helper::ZKMoney="";
QString Helper::DFBankNum="";
Helper::Helper(QObject *parent) : QObject(parent)
{

}
//银行卡校验算法
bool Helper::Luhn(QString text)
{
   int sum = 0;
   int length = text.length();
   for (int i = 0; i < length; i++) {
       int digit = text.mid(length - i - 1,1).toInt();
       if (i % 2 == 1) {
           digit *= 2;
       }
       sum += digit > 9 ? digit - 9 : digit;
   }
   qDebug()<<sum % 10;
   return sum % 10 == 0;
}
//行外手续费
int Helper::GetCommissionCharge(QString MoneyNum)
{
    if(MoneyNum.toInt()<=100)
    {
        return 2;
    }else if(MoneyNum.toInt()<=500)
    {
        return 4;
    }else if(MoneyNum.toInt()<=1000)
    {
        return 6;
    }else if(MoneyNum.toInt()<=2000)
    {
        return 8;
    }
}
//显示消息框
void Helper::ShowMessageBoxInfo(QString info)
{

    MesaageDiaLog *msg=new MesaageDiaLog;
    msg->SetMessage(info,0);
    msg->exec();
}
//显示错误框
void Helper::ShowMessageBoxError(QString info)
{
    MesaageDiaLog *msg=new MesaageDiaLog;
    msg->SetMessage(info,2);
    msg->exec();
}
//显示询问框
int Helper::ShowMessageBoxQuesion(QString info)
{
    MesaageDiaLog *msg=new MesaageDiaLog;
    msg->SetMessage(info,1);
    msg->exec();
}
