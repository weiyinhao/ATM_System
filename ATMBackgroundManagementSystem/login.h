#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QMessageBox>
namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();

private slots:
    void on_Btn_close_clicked();

    void on_Btn_Login_clicked();

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
