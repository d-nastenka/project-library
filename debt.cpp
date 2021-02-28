#include "debt.h"
#include "ui_debt.h"

#include <iostream>
#include <sstream>

Debt::Debt(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Debt)
{
    ui->setupUi(this);

    db = new DataBase();
    db->connectToDataBase();

    ui->tableWidget->setColumnCount(5); // Указываем число колонок
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
                                               << trUtf8("Название")
                                               << trUtf8("Автор")
                                               << trUtf8("Номер читательского билета")
                                               << trUtf8("Дата выдачи"));


    QSqlQuery query("SELECT "
                    DEVICE ".id, "
                    DEVICE "." DEVICE_NAME ", "
                    DEVICE "." DEVICE_AUTHOR ", "
                    DEVICE "." DEVICE_TICKET ", "
                    DEVICE "." DEVICE_DATE
                    " FROM " DEVICE);
    //query.exec();

    for(int i = 0; query.next(); i++){

        QString u_date = query.value(4).toString();
        QDate dt1 = QDate::fromString(u_date,"dd:MM:yyyy"); //дата когда взяли книгу
        QDate cd = QDate::currentDate();

        if(dt1.daysTo(cd)>=30 && query.value(3).toInt() != 0){

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
        }
        else i--;

    }

    ui->tableWidget->resizeColumnsToContents();
}

Debt::~Debt()
{
    delete ui;
}

void Debt::on_pushButton_clicked()
{
    Debt::close();
}
