#include "add_reader.h"
#include "ui_add_reader.h"
#include <QMessageBox>

add_reader::add_reader(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::add_reader)
{
    ui->setupUi(this);
}

add_reader::~add_reader()
{
    delete ui;
}

void add_reader::on_pushButton_clicked()  //Добавить пользователя
{
    if(ui->lineEdit->text().size()!=0 && ui->lineEdit_2->text().size()!=0 && ui->lineEdit_3->text().size()!=0 && ui->lineEdit_4->text().size()!=0 && ui->lineEdit_5->text().size()!=0)
        emit addReader();
    else{
        QMessageBox::warning(this, QString("Attantion!"), QString("Fill in the empty fields."), QMessageBox::Ok);
    }
}

void add_reader::on_pushButton_2_clicked() //Отменить
{
    add_reader::close();
}

void add_reader::on_lineEdit_textEdited(const QString &arg1) //Логин
{
    add_reader::m_login = arg1;
}

void add_reader::on_lineEdit_2_textEdited(const QString &arg1) //Пароль
{
    add_reader::m_password = arg1;
}

void add_reader::on_lineEdit_3_textEdited(const QString &arg1) //ФИО
{
    add_reader::m_name = arg1;
}

void add_reader::on_lineEdit_4_textEdited(const QString &arg1) //Адрес
{
    add_reader::m_adress = arg1;
}

void add_reader::on_lineEdit_5_textEdited(const QString &arg1) //Номер билета
{
    add_reader::m_ticket = arg1;
}

QString add_reader::getLogin()
{
    return add_reader::m_login;
}
QString add_reader::getPassword()
{
    return add_reader::m_password;
}
QString add_reader::getName()
{
    return add_reader::m_name;
}
QString add_reader::getAdress()
{
    return add_reader::m_adress;
}
QString add_reader::getTicket()
{
    return add_reader::m_ticket;
}
