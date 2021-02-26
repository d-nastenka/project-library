#include "add_librarian.h"
#include "ui_add_librarian.h"
#include <QMessageBox>

Add_librarian::Add_librarian(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::add_librarian)
{
    ui->setupUi(this);
}

Add_librarian::~Add_librarian()
{
    delete ui;
}

void Add_librarian::on_pushButton_clicked() //Добавить
{
    if(ui->lineEdit->text().size()!=0 && ui->lineEdit_2->text().size()!=0 && ui->lineEdit_3->text().size()!=0)
        emit addLibrerian();
    else{
        QMessageBox::warning(this, QString("Attantion!"), QString("Fill in the empty fields."), QMessageBox::Ok);
    }
}

void Add_librarian::on_pushButton_2_clicked() //Удалить
{
    Add_librarian::close();
}

void Add_librarian::on_lineEdit_textEdited(const QString &arg1) //Логин
{
    Add_librarian::m_login = arg1;
}

void Add_librarian::on_lineEdit_2_textEdited(const QString &arg1) //Пароль
{
    Add_librarian::m_password = arg1;
}

void Add_librarian::on_lineEdit_3_textEdited(const QString &arg1) //ФИО
{
    Add_librarian::m_name = arg1;
}

QString Add_librarian::getLogin()
{
    return Add_librarian::m_login;
}
QString Add_librarian::getPassword()
{
    return Add_librarian::m_password;
}
QString Add_librarian::getName()
{
    return Add_librarian::m_name;
}
