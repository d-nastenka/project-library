#include "librarian.h"
#include "ui_librarian.h"

Librarian::Librarian(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Librarian)
{
    ui->setupUi(this);

    connect(&ui_add_librarian, SIGNAL(addLibrerian()),
                this, SLOT(addLIBRERIAN()));

        ui->tableWidget->setColumnCount(2); // Указываем число колонок
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
                                                   << trUtf8("ФИО"));

        db = new DataBase();
        db->connectToDataBase();

        QSqlQuery query("SELECT "
                        LIBRARIANS ".id, "
                        LIBRARIANS "." LIBRARIAN_NAME ", "
                        LIBRARIANS "." LIBRARIAN_ROLE
                        " FROM " LIBRARIANS);
        for(int i = 0; query.next(); i++){
            //qDebug()<<i<<query.value(0).toString()<<query.value(1).toString()<<query.value(2).toString();
            //qDebug()<<query.value(4).toString();
            //qDebug()<<query.value(2).toString()<<(query.value(2).toString() == "librarian");
            if (query.value(2).toString() == "librarian"){
                ui->tableWidget->insertRow(i);

                QTableWidgetItem *item1 = new QTableWidgetItem(query.value(0).toString());
                item1->setFlags(item1->flags() ^ Qt::ItemIsEditable);
                ui->tableWidget->setItem(i,0, item1);

                QTableWidgetItem *item = new QTableWidgetItem(query.value(1).toString());
                item->setFlags(item->flags() ^ Qt::ItemIsEditable);
                ui->tableWidget->setItem(i,1, item);
            }
            else
                i--;
        }
        ui->tableWidget->resizeColumnsToContents();
}

Librarian::~Librarian()
{
    delete ui;
}

void Librarian::on_pushButton_clicked()
{
    ui_add_librarian.show();
}

void Librarian::remove(QString name){
    QSqlQuery query1;
    query1.prepare("DELETE FROM LibrarianTable WHERE Name = '" + name + "'");
    if(!query1.exec()){
        qDebug() << "error update " << LIBRARIANS;
        qDebug() << query1.lastError().text();
    }
}

void Librarian::on_pushButton_2_clicked() //Удалить
{
    int i = ui->tableWidget->currentRow();
    if (i==-1){
        qDebug()<<"Ошибка: Библиотекарь не выбран";
        return;
    }

    QSqlQuery query1;
    query1.prepare("DELETE FROM LibrarianTable WHERE id =" + ui->tableWidget->item(i,0)->text());
    if(!query1.exec()){
        qDebug() << "error update " << LIBRARIANS;
        qDebug() << query1.lastError().text();
    }
    ui->tableWidget->removeRow(i);
    ui->tableWidget->clear();

    //update
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << trUtf8("id")
                                               << trUtf8("ФИО"));

    QSqlQuery query("SELECT "
                    LIBRARIANS ".id, "
                    LIBRARIANS "." LIBRARIAN_NAME ", "
                    LIBRARIANS "." LIBRARIAN_ROLE
                    " FROM " LIBRARIANS);
    for(int i = 0; query.next(); i++){
        if (query.value(2).toString() == "librarian"){
            QTableWidgetItem *item1 = new QTableWidgetItem(query.value(0).toString());
            item1->setFlags(item1->flags() ^ Qt::ItemIsEditable);
            ui->tableWidget->setItem(i,0, item1);
            QTableWidgetItem *item = new QTableWidgetItem(query.value(1).toString());
            item->setFlags(item->flags() ^ Qt::ItemIsEditable);
            ui->tableWidget->setItem(i,1, item);
        }
        else
            i--;
    }
    // Ресайзим колонки по содержимому
    ui->tableWidget->resizeColumnsToContents();
}

void Librarian::on_pushButton_3_clicked()
{
    Librarian::close();
}

void Librarian::add(QString login, QString password, QString name){
    qDebug()<<db->inserIntoLibrarianTable(QVariantList()<< login
                                                        << password
                                                        << name
                                                        << "librarian");
}

void Librarian::addLIBRERIAN(){
    u_login = ui_add_librarian.getLogin();
    u_password = ui_add_librarian.getPassword();
    u_name = ui_add_librarian.getName();

    add(u_login, u_password, u_name);

    ui->tableWidget->clear();
    ui->tableWidget->insertRow(0);
    //update
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << trUtf8("id")
                                               << trUtf8("ФИО"));

    QSqlQuery query("SELECT "
                    LIBRARIANS ".id, "
                    LIBRARIANS "." LIBRARIAN_NAME ", "
                    LIBRARIANS "." LIBRARIAN_ROLE
                    " FROM " LIBRARIANS);
    for(int i = 0; query.next(); i++){
        if (query.value(2).toString() == "librarian"){
            QTableWidgetItem *item1 = new QTableWidgetItem(query.value(0).toString());
            item1->setFlags(item1->flags() ^ Qt::ItemIsEditable);
            ui->tableWidget->setItem(i,0, item1);
            QTableWidgetItem *item = new QTableWidgetItem(query.value(1).toString());
            item->setFlags(item->flags() ^ Qt::ItemIsEditable);
            ui->tableWidget->setItem(i,1, item);
        }
        else
            i--;
    }
    // Ресайзим колонки по содержимому
    ui->tableWidget->resizeColumnsToContents();

    ui_add_librarian.close();

    //udb->closeUserDataBase();


}
