#include "authorization.h"
#include "ui_authorization.h"

Authorization::Authorization(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Authorization)
{
    ui->setupUi(this);
}

Authorization::~Authorization()
{
    delete ui;
}

void Authorization::on_pushButton_clicked()
{
    emit pushButton_clicked();
}

void Authorization::on_lineEdit_textEdited(const QString &arg1)
{
    Authorization::m_username = arg1;
}

void Authorization::on_lineEdit_2_textEdited(const QString &arg1)
{
    Authorization::m_userpass = arg1;
}
QString Authorization::getLogin()
{
    return Authorization::m_username;
}

QString Authorization::getPass()
{
    return Authorization::m_userpass;
}
