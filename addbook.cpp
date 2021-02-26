#include "addbook.h"
#include "ui_addbook.h"
#include <QMessageBox>

addBook::addBook(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::addBook)
{
    ui->setupUi(this);
}

addBook::~addBook()
{
    delete ui;
}

void addBook::on_pushButton_clicked() //Добавить
{

    if(ui->lineEdit->text().size()!=0 && ui->lineEdit_2->text().size()!=0 && ui->lineEdit_3->text().size()!=0 && ui->lineEdit_4->text().size()!=0)
        emit addpushButton_clicked();
    else{
        QMessageBox::warning(this, QString("Attantion!"), QString("Fill in the empty fields."), QMessageBox::Ok);
    }
}

void addBook::on_pushButton_2_clicked() //Отменить
{
    addBook::close();
}

void addBook::on_lineEdit_textEdited(const QString &arg1)
{
    addBook::m_name = arg1;
}

void addBook::on_lineEdit_2_textEdited(const QString &arg1)
{
    addBook::m_author = arg1;
}

void addBook::on_lineEdit_3_textEdited(const QString &arg1)
{
    addBook::m_numbers = arg1;
}

void addBook::on_lineEdit_4_textEdited(const QString &arg1)
{
    addBook::m_cost = arg1;
}
QString addBook::getName()
{
    return addBook::m_name;
}
QString addBook::getAuthor()
{
    return addBook::m_author;
}
QString addBook::getNumbers()
{
    return addBook::m_numbers;
}
QString addBook::getCost()
{
    return addBook::m_cost;
}


