#ifndef MESAAGEDIALOG_H
#define MESAAGEDIALOG_H

#include <QDialog>

namespace Ui {
class MesaageDiaLog;
}

class MesaageDiaLog : public QDialog
{
    Q_OBJECT

public:
    explicit MesaageDiaLog(QWidget *parent = 0);

    void SetMessage(const QString &msg, int type);//设置信息框

    ~MesaageDiaLog();
protected:
    void paintEvent(QPaintEvent *event);
private slots:
    void on_btnOk_clicked();

private:
    Ui::MesaageDiaLog *ui;

};

#endif // MESAAGEDIALOG_H
