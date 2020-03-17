#include "widget.h"
#include <QApplication>
#include "login.h"
#include "Config/connectionsql.h"
#include "Config/connectionpool.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Login w;
    w.show();

    //从数据库连接池里取得连接
    ConnectionPool::openConnection();

    /*if(!createConnection())
    {
        qDebug()<<"数据库连接失败";
        return 1;
    }*/
    return a.exec();
}
