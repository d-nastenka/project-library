#include "authorization.h"
#include "ui_authorization.h"

authorization::authorization(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::authorization)
{
    ui->setupUi(this);
}

authorization::~authorization()
{
    delete ui;
}

void authorization::on_pushButton_clicked()
{
    emit pushButton_clicked();
}

void authorization::on_lineEdit_textEdited(const QString &arg1)
{
    authorization::m_username = arg1;
}

void authorization::on_lineEdit_2_textEdited(const QString &arg1)
{
    authorization::m_userpass = arg1;
}
QString authorization::getLogin()
{
    return authorization::m_username;
}

QString authorization::getPass()
{
    return authorization::m_userpass;
}
