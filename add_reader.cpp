#include "add_reader.h"
#include "ui_add_reader.h"
#include <QMessageBox>

Add_reader::Add_reader(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::add_reader)
{
    ui->setupUi(this);
}

Add_reader::~Add_reader()
{
    delete ui;
}

void Add_reader::on_pushButton_clicked()  //Добавить пользователя
{
    if(ui->lineEdit->text().size()!=0 && ui->lineEdit_2->text().size()!=0 && ui->lineEdit_3->text().size()!=0 && ui->lineEdit_4->text().size()!=0 && ui->lineEdit_5->text().size()!=0)
        emit addReader();
    else{
        QMessageBox::warning(this, QString("Attantion!"), QString("Fill in the empty fields."), QMessageBox::Ok);
    }
}

void Add_reader::on_pushButton_2_clicked() //Отменить
{
    Add_reader::close();
}

void Add_reader::on_lineEdit_textEdited(const QString &arg1) //Логин
{
    Add_reader::m_login = arg1;
}

void Add_reader::on_lineEdit_2_textEdited(const QString &arg1) //Пароль
{
    Add_reader::m_password = arg1;
}

void Add_reader::on_lineEdit_3_textEdited(const QString &arg1) //ФИО
{
    Add_reader::m_name = arg1;
}

void Add_reader::on_lineEdit_4_textEdited(const QString &arg1) //Адрес
{
    Add_reader::m_adress = arg1;
}

void Add_reader::on_lineEdit_5_textEdited(const QString &arg1) //Номер билета
{
    Add_reader::m_ticket = arg1;
}

QString Add_reader::getLogin()
{
    return Add_reader::m_login;
}
QString Add_reader::getPassword()
{
    return Add_reader::m_password;
}
QString Add_reader::getName()
{
    return Add_reader::m_name;
}
QString Add_reader::getAdress()
{
    return Add_reader::m_adress;
}
QString Add_reader::getTicket()
{
    return Add_reader::m_ticket;
}
