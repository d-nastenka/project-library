#include "issued_books.h"
#include "ui_issued_books.h"

issued_books::issued_books(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::issued_books)
{
    ui->setupUi(this);

}

void issued_books::getTicket(QString u_ticket){
    db = new DataBase();
    db->connectToDataBase();

    ui->tableWidget->setColumnCount(6); // Указываем число колонок
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
                                               << trUtf8("Количество страниц")
                                               << trUtf8("Цена")
                                               << trUtf8("Дата выдачи"));


    QSqlQuery query("SELECT "
                    DEVICE ".id, "
                    DEVICE "." DEVICE_NAME ", "
                    DEVICE "." DEVICE_AUTHOR ", "
                    DEVICE "." DEVICE_NUMBER ", "
                    DEVICE "." DEVICE_TICKET ", "
                    DEVICE "." DEVICE_COST ", "
                    DEVICE "." DEVICE_DATE
                    " FROM " DEVICE);
    //query.exec();

    for(int i = 0; query.next(); i++){
        //qDebug()<<u_ticket<<i<<query.value(0).toString()<<query.value(1).toString()<<query.value(2).toString()<<query.value(3).toString()<<query.value(4).toString()<<query.value(5).toString()<<(query.value(4) != u_ticket);
        if(query.value(4) != u_ticket){
            i--;
            continue;
        }
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
        //QTableWidgetItem *item4 = new QTableWidgetItem(query.value(4).toString());
        //item4->setFlags(item4->flags() ^ Qt::ItemIsEditable);
        //ui->tableWidget->setItem(i,4, item4);
        QTableWidgetItem *item4 = new QTableWidgetItem(query.value(5).toString());
        item4->setFlags(item4->flags() ^ Qt::ItemIsEditable);
        ui->tableWidget->setItem(i,4, item4);
        QTableWidgetItem *item5 = new QTableWidgetItem(query.value(6).toString());
        item5->setFlags(item5->flags() ^ Qt::ItemIsEditable);
        ui->tableWidget->setItem(i,5, item5);
    }

    // Ресайзим колонки по содержимому
    ui->tableWidget->resizeColumnsToContents();
}

issued_books::~issued_books()
{
    delete ui;
}

void issued_books::on_pushButton_clicked()
{
    issued_books::close();
}
