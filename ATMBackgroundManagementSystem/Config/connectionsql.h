#ifndef CONNECTIONSQL_H
#define CONNECTIONSQL_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include "Config/helper.h"
//创建数据并连接数据库
static bool createConnection()
{
    QSqlDatabase db=QSqlDatabase::addDatabase("QODBC");//数据库驱动类型为SQL Server
    QString dsn=QString::fromLocal8Bit("ATM");//数据源名称
    db.setHostName("localhost");//主机名
    db.setDatabaseName(dsn);//设置数据源
    db.setUserName("st");//登陆用户
    db.setPassword("123456");//密码
    if(!db.open())//数据库连接失败
    {
        //Helper::ShowMessageBoxError("连接数据库失败！");
        return false;
    }
    return true;
}
//关闭数据库连接
static bool closeConnection()
{
    QSqlDatabase::database().close();
    return true;
}

#endif // CONNECTIONSQL_H
