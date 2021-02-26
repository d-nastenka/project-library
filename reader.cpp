#include "reader.h"
#include "ui_reader.h"
#include "QDebug"

reader::reader(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::reader)
{
    ui->setupUi(this);
    connect(&ui_add_reader, SIGNAL(addReader()),
            this, SLOT(addUSER()));

    ui->tableWidget->setColumnCount(4); // Указываем число колонок
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
                                               << trUtf8("ФИО")
                                               << trUtf8("Номер читательского билета")
                                               << trUtf8("Адрес"));

    db = new DataBase();
    db->connectToDataBase();

    QSqlQuery query("SELECT "
                    USERS ".id, "
                    USERS "." USER_NAME ", "
                    USERS "." USER_TICKET ", "
                    USERS "." USER_ADRESS ", "
                    USERS "." USER_ROLE
                    " FROM " USERS);
    for(int i = 0; query.next(); i++){
        //qDebug()<<i<<query.value(0).toString()<<query.value(1).toString()<<query.value(2).toString();
        //qDebug()<<query.value(4).toString();
        if(query.value(4).toString() == "reader"){

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
        }
        else i--;
    }
    // Ресайзим колонки по содержимому
    ui->tableWidget->resizeColumnsToContents();
}

reader::~reader()
{
    delete ui;
}

void reader::on_pushButton_clicked() //Добавить
{
    ui_add_reader.show();
}

void reader::on_pushButton_3_clicked() //Закрыть
{
    reader::close();
}

void reader::add(QString login, QString password, QString name, QString adress, QString number){
    qDebug()<<db->inserIntoUserTable(QVariantList()     << login
                                                        << password
                                                        << name
                                                        << "reader"
                                                        << number
                                                        << adress);
}

void reader::addUSER(){

    u_login = ui_add_reader.getLogin();
    u_password = ui_add_reader.getPassword();
    u_name = ui_add_reader.getName();
    u_adress = ui_add_reader.getAdress();
    u_number = ui_add_reader.getTicket();

    add(u_login, u_password, u_name, u_adress, u_number);

    ui->tableWidget->insertRow(0);
    //update
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << trUtf8("id")
                                               << trUtf8("ФИО")
                                               << trUtf8("Номер читательского билета")
                                               << trUtf8("Адрес"));

    QSqlQuery query("SELECT "
                    USERS ".id, "
                    USERS "." USER_NAME ", "
                    USERS "." USER_TICKET ", "
                    USERS "." USER_ADRESS ", "
                    USERS "." USER_ROLE
                    " FROM " USERS);
    for(int i = 0; query.next(); i++){
        if(query.value(4).toString() == "reader"){
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
        }
        else i--;
    }
    ui->tableWidget->resizeColumnsToContents();

    ui_add_reader.close();
}
