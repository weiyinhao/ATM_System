#include "helpdlg.h"
#include "ui_helpdlg.h"
#include <QMessageBox>
HelpDlg::HelpDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HelpDlg)
{
    ui->setupUi(this);

}

HelpDlg::~HelpDlg()
{
    delete ui;
}
