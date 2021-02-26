#include "add_librarian.h"
#include "ui_add_librarian.h"
#include <QMessageBox>

add_librarian::add_librarian(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::add_librarian)
{
    ui->setupUi(this);
}

add_librarian::~add_librarian()
{
    delete ui;
}

void add_librarian::on_pushButton_clicked() //Добавить
{
    if(ui->lineEdit->text().size()!=0 && ui->lineEdit_2->text().size()!=0 && ui->lineEdit_3->text().size()!=0)
        emit addLibrerian();
    else{
        QMessageBox::warning(this, QString("Attantion!"), QString("Fill in the empty fields."), QMessageBox::Ok);
    }
}

void add_librarian::on_pushButton_2_clicked() //Удалить
{
    add_librarian::close();
}

void add_librarian::on_lineEdit_textEdited(const QString &arg1) //Логин
{
    add_librarian::m_login = arg1;
}

void add_librarian::on_lineEdit_2_textEdited(const QString &arg1) //Пароль
{
    add_librarian::m_password = arg1;
}

void add_librarian::on_lineEdit_3_textEdited(const QString &arg1) //ФИО
{
    add_librarian::m_name = arg1;
}

QString add_librarian::getLogin()
{
    return add_librarian::m_login;
}
QString add_librarian::getPassword()
{
    return add_librarian::m_password;
}
QString add_librarian::getName()
{
    return add_librarian::m_name;
}
