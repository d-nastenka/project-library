#include "addbook.h"
#include "ui_addbook.h"
#include <QMessageBox>

AddBook::AddBook(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::addBook)
{
    ui->setupUi(this);
}

AddBook::~AddBook()
{
    delete ui;
}

void AddBook::on_pushButton_clicked() //Добавить
{

    if(ui->lineEdit->text().size()!=0 && ui->lineEdit_2->text().size()!=0 && ui->lineEdit_3->text().size()!=0 && ui->lineEdit_4->text().size()!=0)
        emit addpushButton_clicked();
    else{
        QMessageBox::warning(this, QString("Attantion!"), QString("Fill in the empty fields."), QMessageBox::Ok);
    }
}

void AddBook::on_pushButton_2_clicked() //Отменить
{
    AddBook::close();
}

void AddBook::on_lineEdit_textEdited(const QString &arg1)
{
    AddBook::m_name = arg1;
}

void AddBook::on_lineEdit_2_textEdited(const QString &arg1)
{
    AddBook::m_author = arg1;
}

void AddBook::on_lineEdit_3_textEdited(const QString &arg1)
{
    AddBook::m_numbers = arg1;
}

void AddBook::on_lineEdit_4_textEdited(const QString &arg1)
{
    AddBook::m_cost = arg1;
}
QString AddBook::getName()
{
    return AddBook::m_name;
}
QString AddBook::getAuthor()
{
    return AddBook::m_author;
}
QString AddBook::getNumbers()
{
    return AddBook::m_numbers;
}
QString AddBook::getCost()
{
    return AddBook::m_cost;
}


