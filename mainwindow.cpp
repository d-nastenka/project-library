#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "authorization.h"
#include "addbook.h"
#include <QtDebug>
#include <QtWidgets>
#include <QDate>
#include <QMessageBox>
//#include "database_user.h"
//#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    connect(&ui_Auth, SIGNAL(pushButton_clicked()),
            this, SLOT(authorizeUser()));
    connect(&ui_Add, SIGNAL(addpushButton_clicked()),
            this, SLOT(insertBook()));
    db = new DataBase();
    db->connectToDataBase();

    ui_Auth.show();
    this->hide();
}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::authorizeUser()
{
/*
    db->inserIntoLibrarianTable(QVariantList() << "Anastasia"
                                           << "1234"
                                           << "Анастасия Юрьевна"
                                           << "librarian");

    db->inserIntoDeviceTable(QVariantList() << QString::number(0)
                                                        << "чтиво"
                                                        << "Толстой А В"
                                                        << "10"
                                                        << "25"
                                                        << NULL
                                                        << NULL);
*/
    m_username = ui_Auth.getLogin();
    m_userpass = ui_Auth.getPass();

    m_loginSuccesfull = false;
    if (!m_username.size() || !m_userpass.size()){
        QMessageBox::warning(this, QString("Attantion!"), QString("Title is empty."), QMessageBox::Ok);
    }

    QSqlQuery query("SELECT "
                    USERS ".id, "
                    USERS "." USER_LOGIN ", "
                    USERS "." USER_PASSWORD", "
                    USERS "." USER_NAME ", "
                    USERS "." USER_ROLE ", "
                    USERS "." USER_TICKET ", "
                    USERS "." USER_ADRESS
                    " FROM " USERS);

    QSqlQuery query1("SELECT "
                    LIBRARIANS ".id, "
                    LIBRARIANS "." LIBRARIAN_LOGIN ", "
                    LIBRARIANS "." LIBRARIAN_PASSWORD", "
                    LIBRARIANS "." LIBRARIAN_NAME ", "
                    LIBRARIANS "." LIBRARIAN_ROLE
                    " FROM " LIBRARIANS);

    while(query.next() || query1.next()){
        if(m_username == "Admin" && m_userpass == "0000"){
            m_loginSuccesfull = true;
            m_role = "admin";
            m_ticket = "";
            break;
        }
        if (query.value(1) == m_username && query.value(2) == m_userpass){
            m_loginSuccesfull = true;
            m_role = query.value(4).toString();
            m_ticket = query.value(5).toString();
            break;
        }
        if (query1.value(1) == m_username && query1.value(2) == m_userpass){
            m_loginSuccesfull = true;
            m_role = query1.value(4).toString();
            m_ticket = "";
            break;
        }
    }

    if(!query.exec()){
        qDebug() << "error check " << "UserTable";
        qDebug() << query.lastError().text();
    } else {
        qDebug()<<"true";
    }

    if(!m_loginSuccesfull)
    {
        m_loginSuccesfull = false;
    }
    else
    {
        m_loginSuccesfull = true;
        ui_Auth.close();

        ui->setupUi(this);

        if(m_role == "reader"){
            ui->pushButton->setEnabled(false);
            ui->pushButton->setVisible(false);
            ui->pushButton_2->setEnabled(false);
            ui->pushButton_2->setVisible(false);
            ui->pushButton_4->setVisible(false);
            ui->pushButton_4->setEnabled(false);
            ui->lineEdit->setVisible(false);
            ui->pushButton_3->setVisible(false);
            ui->label_3->setVisible(false);
            ui->action_2->setVisible(false);
            ui->action_3->setVisible(false);
            ui->action_4->setVisible(false);
            //ui->action_5->setVisible(false);
            //ui->menu->setVisible(false);
        }
        if(m_role == "librarian"){
            ui->action_5->setVisible(false);
            ui->action_3->setVisible(false);
        }
        if(m_role == "admin"){
            ui->pushButton->setEnabled(false);
            ui->pushButton->setVisible(false);
            ui->pushButton_2->setEnabled(false);
            ui->pushButton_2->setVisible(false);
            ui->pushButton_4->setVisible(false);
            ui->pushButton_4->setEnabled(false);
            ui->lineEdit->setVisible(false);
            ui->pushButton_3->setVisible(false);
            ui->label_3->setVisible(false);
            ui->action_5->setVisible(false);
            ui->action_2->setVisible(false);
            ui->action_4->setVisible(false);
        }

        this->setWindowTitle("Books list");
        this->createUI();
    }
}
void MainWindow::createUI()
{
    //логин и роль
    ui->label_2->setText(m_username);
    ui->label->setText(m_role);

    ui->tableWidget->setColumnCount(8);
    ui->tableWidget->setShowGrid(true);

    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);

    ui->tableWidget->hideColumn(0);

    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << trUtf8("id")
                                               << trUtf8("Доступность")
                                               << trUtf8("Название")
                                               << trUtf8("Автор")
                                               << trUtf8("Количество страниц")
                                               << trUtf8("Цена")
                                               << trUtf8("Номер читательского билета")
                                               << trUtf8("Дата выдачи"));


    QSqlQuery query("SELECT "
                    DEVICE ".id, "
                    DEVICE "." DEVICE_CHECK_STATE ", "
                    DEVICE "." DEVICE_NAME ", "
                    DEVICE "." DEVICE_AUTHOR ", "
                    DEVICE "." DEVICE_NUMBER ", "
                    DEVICE "." DEVICE_COST ", "
                    DEVICE "." DEVICE_TICKET ", "
                    DEVICE "." DEVICE_DATE
                    " FROM " DEVICE);
    //query.exec();

    for(int i = 0; query.next(); i++){
        //qDebug()<<i<<query.value(0).toString()<<query.value(1).toString()<<query.value(2).toString();
        if(query.value(2) == NULL)
            continue;
        ui->tableWidget->insertRow(i);

        QTableWidgetItem *item1 = new QTableWidgetItem(query.value(0).toString());
        item1->setFlags(item1->flags() ^ Qt::ItemIsEditable);
        ui->tableWidget->setItem(i,0, item1);

        QTableWidgetItem *item = new QTableWidgetItem(query.value(1).toString());
        item->setFlags(item->flags() ^ Qt::ItemIsEditable);
        ui->tableWidget->setItem(i,1, item);
        QTableWidgetItem *item2 = new QTableWidgetItem(query.value(2).toString());
        item2->setFlags(item2->flags() ^ Qt::ItemIsEditable);
        ui->tableWidget->setItem(i,2, item2);
        QTableWidgetItem *item3 = new QTableWidgetItem(query.value(3).toString());
        item3->setFlags(item3->flags() ^ Qt::ItemIsEditable);
        ui->tableWidget->setItem(i,3, item3);
        QTableWidgetItem *item4 = new QTableWidgetItem(query.value(4).toString());
        item4->setFlags(item4->flags() ^ Qt::ItemIsEditable);
        ui->tableWidget->setItem(i,4, item4);
        QTableWidgetItem *item5 = new QTableWidgetItem(query.value(5).toString());
        item4->setFlags(item5->flags() ^ Qt::ItemIsEditable);
        ui->tableWidget->setItem(i,5, item5);
        QTableWidgetItem *item6 = new QTableWidgetItem(query.value(6).toString());
        item4->setFlags(item6->flags() ^ Qt::ItemIsEditable);
        ui->tableWidget->setItem(i,6, item6);
        QTableWidgetItem *item7 = new QTableWidgetItem(query.value(7).toString());
        item4->setFlags(item7->flags() ^ Qt::ItemIsEditable);
        ui->tableWidget->setItem(i,7, item7);
    }

    ui->tableWidget->resizeColumnsToContents();
}


void MainWindow::on_pushButton_clicked() //удаление
{
    int i = ui->tableWidget->currentRow();
    if (i==-1){
        qDebug()<<"Ошибка: Книга не выбрана";
        return;
    }
    QSqlQuery query;
    query.prepare("DELETE FROM BooksTable WHERE id =" + ui->tableWidget->item(i,0)->text());
    if(!query.exec()){
        qDebug() << "error update " << DEVICE;
        qDebug() << query.lastError().text();
    } else {
        qDebug()<<"true";
    }

    ui->tableWidget->removeRow(i);
    updateTable();



}

void MainWindow::updateTable(){

    ui->tableWidget->clear();

    ui->tableWidget->setColumnCount(8); // Указываем число колонок
    ui->tableWidget->setShowGrid(true); // Включаем сетку
    // Разрешаем выделение только одного элемента
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    // Разрешаем выделение построчно
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    // Устанавливаем заголовки колонок
    //ui->tableWidget->setHorizontalHeaderLabels(headers);
    // Растягиваем последнюю колонку на всё доступное пространство
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    // Скрываем колонку под номером 0
    ui->tableWidget->hideColumn(0);

    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << trUtf8("id")
                                               << trUtf8("Доступность")
                                               << trUtf8("Название")
                                               << trUtf8("Автор")
                                               << trUtf8("Количество страниц")
                                               << trUtf8("Цена")
                                               << trUtf8("Номер читательского билета")
                                               << trUtf8("Дата выдачи"));


    QSqlQuery query("SELECT "
                    DEVICE ".id, "
                    DEVICE "." DEVICE_CHECK_STATE ", "
                    DEVICE "." DEVICE_NAME ", "
                    DEVICE "." DEVICE_AUTHOR ", "
                    DEVICE "." DEVICE_NUMBER ", "
                    DEVICE "." DEVICE_COST ", "
                    DEVICE "." DEVICE_TICKET ", "
                    DEVICE "." DEVICE_DATE
                    " FROM " DEVICE);
    //query.exec();


    for(int i = 0; query.next(); i++){
        //qDebug()<<i<<query.value(0).toString()<<query.value(1).toString()<<query.value(2).toString();
        if(query.value(2) == NULL)
            continue;


        QTableWidgetItem *item1 = new QTableWidgetItem(query.value(0).toString());
        item1->setFlags(item1->flags() ^ Qt::ItemIsEditable);
        ui->tableWidget->setItem(i,0, item1);

        QTableWidgetItem *item = new QTableWidgetItem(query.value(1).toString());
        item->setFlags(item->flags() ^ Qt::ItemIsEditable);
        ui->tableWidget->setItem(i,1, item);
        QTableWidgetItem *item2 = new QTableWidgetItem(query.value(2).toString());
        item2->setFlags(item2->flags() ^ Qt::ItemIsEditable);
        ui->tableWidget->setItem(i,2, item2);
        QTableWidgetItem *item3 = new QTableWidgetItem(query.value(3).toString());
        item3->setFlags(item3->flags() ^ Qt::ItemIsEditable);
        ui->tableWidget->setItem(i,3, item3);
        QTableWidgetItem *item4 = new QTableWidgetItem(query.value(4).toString());
        item4->setFlags(item4->flags() ^ Qt::ItemIsEditable);
        ui->tableWidget->setItem(i,4, item4);
        QTableWidgetItem *item5 = new QTableWidgetItem(query.value(5).toString());
        item4->setFlags(item5->flags() ^ Qt::ItemIsEditable);
        ui->tableWidget->setItem(i,5, item5);
        QTableWidgetItem *item6 = new QTableWidgetItem(query.value(6).toString());
        item4->setFlags(item6->flags() ^ Qt::ItemIsEditable);
        ui->tableWidget->setItem(i,6, item6);
        QTableWidgetItem *item7 = new QTableWidgetItem(query.value(7).toString());
        item4->setFlags(item7->flags() ^ Qt::ItemIsEditable);
        ui->tableWidget->setItem(i,7, item7);
    }

    // Ресайзим колонки по содержимому
    ui->tableWidget->resizeColumnsToContents();

}

void MainWindow::insertBook(){ //добавление книги
    m_name = ui_Add.getName();
    m_author = ui_Add.getAuthor();
    m_numbers = ui_Add.getNumbers();
    m_cost = ui_Add.getCost();

    db->inserIntoDeviceTable(QVariantList() << QString::number(0)
                                                        << m_name
                                                        << m_author
                                                        << m_numbers
                                                        << m_cost
                                                        << NULL
                                                        << NULL);
    ui->tableWidget->insertRow(0);
    updateTable();
    ui_Add.close();

}

void MainWindow::on_pushButton_2_clicked() //добавить книгу
{
    ui_Add.show();

}

void MainWindow::on_action_2_triggered() //список читателей
{
    ui_reader.show();
}

void MainWindow::on_pushButton_3_clicked() //выдать книгу
{
    QSqlQuery query1("SELECT "
                    USERS "." USER_TICKET
                    " FROM " USERS);
    bool scf = 0;
    while(query1.next()){
        if (query1.value(0).toString() == ui->lineEdit->text()){
            scf = 1;
            break;
        }
    }

    if(!query1.exec()){
        qDebug() << "error check " << "UserTable";
        qDebug() << query1.lastError().text();
    }

    int i = ui->tableWidget->currentRow();
    if (i==-1){
        qDebug()<<"Ошибка: Книга не выбрана";
        return;
    }

    QSqlQuery query2("SELECT "
                     DEVICE ".id, "
                     DEVICE "." DEVICE_TICKET
                    " FROM " DEVICE);

    if(!query2.exec()){
        //return;
        qDebug() << "error update " << DEVICE;
        qDebug() << query2.lastError().text();
    }
    bool scf2 = 0;
    while(query2.next()){
         if (query2.value(0).toString() == ui->tableWidget->item(i,0)->text() && query2.value(1).toString()=='0'){
             scf2 = 1;
             break;
         }
     }
    if(scf == 0 ){
        QMessageBox::warning(this, QString("Attantion!"), QString("Reader not found."), QMessageBox::Ok);
        return;
    }

    if (scf2 == 0){

        QMessageBox::warning(this, QString("Attantion!"), QString("This book has already been issued."), QMessageBox::Ok);
        return;
    }

    QSqlQuery query;
    query.prepare("UPDATE BooksTable Set Availible = 1 WHERE id=" + ui->tableWidget->item(i,0)->text());
    if(!query.exec()){
        qDebug() << "error update " << DEVICE;
        qDebug() << query.lastError().text();
    } else {
        //qDebug()<<"true1";
    }
    query.prepare("UPDATE BooksTable Set Ticket = '" + ui->lineEdit->text() + "' WHERE id=" + ui->tableWidget->item(i,0)->text());
    if(!query.exec()){
        qDebug() << "error update " << DEVICE;
        qDebug() << query.lastError().text();
    } else {
        //qDebug()<<"true2";
    }
    QDate cd = QDate::currentDate();

    QString cd1 = cd.toString("dd:MM:yyyy");

    query.prepare("UPDATE BooksTable Set Date ='" + cd1 + "' WHERE id=" + ui->tableWidget->item(i,0)->text());
    if(!query.exec()){
        qDebug() << "error update " << DEVICE;
        qDebug() << query.lastError().text();
    } else {
        //qDebug()<<"true3";
    }

    //ui->tableWidget->removeRow(i);

    updateTable();

}

void MainWindow::on_action_3_triggered() // библиотекари
{
    ui_librarian.show();
}

void MainWindow::on_action_5_triggered()
{
    ui_ib.show();
    ui_ib.getTicket(m_ticket);
}

void MainWindow::on_pushButton_4_clicked() // вернуть книгу
{
    int i = ui->tableWidget->currentRow();
    if (i==-1){
        qDebug()<<"Ошибка: Книга не выбрана";
        return;
    }

    QSqlQuery query;
    query.prepare("UPDATE BooksTable Set Availible = 0 WHERE id=" + ui->tableWidget->item(i,0)->text());
    if(!query.exec()){
        qDebug() << "error update " << DEVICE;
        qDebug() << query.lastError().text();
    } else {
        //qDebug()<<"true1";
    }
    query.prepare("UPDATE BooksTable Set Ticket = '0' WHERE id=" + ui->tableWidget->item(i,0)->text());
    if(!query.exec()){
        qDebug() << "error update " << DEVICE;
        qDebug() << query.lastError().text();
    } else {
        //qDebug()<<"true2";
    }

    query.prepare("UPDATE BooksTable Set Date ='0' WHERE id=" + ui->tableWidget->item(i,0)->text());
    if(!query.exec()){
        qDebug() << "error update " << DEVICE;
        qDebug() << query.lastError().text();
    } else {
        //qDebug()<<"true3";
    }

    //ui->tableWidget->removeRow(i);

    updateTable();

}

void MainWindow::on_action_4_triggered()
{
    ui_debt.show();
}
