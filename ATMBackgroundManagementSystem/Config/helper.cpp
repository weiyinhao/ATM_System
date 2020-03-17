#include "helper.h"

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
   return sum % 10 == 0;
}
