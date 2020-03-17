#include "mesaagedialog.h"
#include "ui_mesaagedialog.h"
#include <QPainter>
MesaageDiaLog::MesaageDiaLog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MesaageDiaLog)
{
    ui->setupUi(this);

    //设置窗体标题栏隐藏
    //this->setWindowFlags(Qt::FramelessWindowHint);
    //设置窗体关闭时自动释放内存
    //this->setAttribute(Qt::WA_DeleteOnClose);
}

MesaageDiaLog::~MesaageDiaLog()
{
    delete ui;
}
void MesaageDiaLog::paintEvent(QPaintEvent *event)
{
    //定义画家
    QPainter painter(this);
    painter.drawPixmap(0,0,this->width(),this->height(),QPixmap(":/images/img/blue5.jpg"));
}
void MesaageDiaLog::SetMessage(const QString &msg, int type)
{
    //提示消息框
    if(type==0)
    {
        ui->labIcoMain->setStyleSheet("border-image: url(:/images/img/update.png);");
        //ui->lab_Title->setText("提示");
        this->setWindowTitle("提示");
    }
    //询问消息框
    else if(type==1)
    {
        ui->labIcoMain->setStyleSheet("border-image: url(:/images/img/info.png);");
        //ui->lab_Title->setText("询问");
        this->setWindowTitle("询问");
    }
    //错误提示框
    else if(type==2)
    {
        ui->labIcoMain->setStyleSheet("border-image: url(:/images/img/error.png);");
        //ui->lab_Title->setText("错误");
        this->setWindowTitle("错误");
    }
    ui->labInfo->setText(msg);
}
//关闭
void MesaageDiaLog::on_btnOk_clicked()
{
    this->close();
}
