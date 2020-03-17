#ifndef HELPER_H
#define HELPER_H

#include <QObject>

class Helper : public QObject
{
    Q_OBJECT
public:
    explicit Helper(QObject *parent = nullptr);


    static bool Luhn(QString text);//银行卡校验Luhn算法
signals:

public slots:
};

#endif // HELPER_H
