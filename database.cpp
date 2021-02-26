#include "database.h"
#include "QDebug"

DataBase::DataBase(QObject *parent) : QObject(parent)
{

}

DataBase::~DataBase()
{

}

/* Методы для подключения к базе данных
 * */
void DataBase::connectToDataBase()
{
    /* Перед подключением к базе данных производим проверку на её существование.
     * В зависимости от результата производим открытие базы данных или её восстановление
     * */
    if(!QFile("C:/example/" DATABASE_NAME).exists()){
        this->restoreDataBase();
    } else {
        this->openDataBase();
    }
}

/* Методы восстановления базы данных
 * */
bool DataBase::restoreDataBase()
{
    if(this->openDataBase()){
        if(!this->createDeviceTable() || !this->createUserTable() || !this->createLibrarianTable()){
            return false;
        } else {
            return true;
        }
    } else {
        qDebug() << "Не удалось восстановить базу данных";
        return false;
    }
    return false;
}

/* Метод для открытия базы данных
 * */
bool DataBase::openDataBase()
{
    /* База данных открывается по заданному пути
     * и имени базы данных, если она существует
     * */
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName(DATABASE_HOSTNAME);
    db.setDatabaseName("C:/example/" DATABASE_NAME);
    if(db.open()){
        return true;
    } else {
        return false;
    }
}

/* Методы закрытия базы данных
 * */
void DataBase::closeDataBase()
{
    db.close();
}

/* Метод для создания таблицы устройств в базе данных
 * */
bool DataBase::createDeviceTable()
{
    /* В данном случае используется формирование сырого SQL-запроса
     * с последующим его выполнением.
     * */
    QSqlQuery query;
    if(!query.exec( "CREATE TABLE " DEVICE " ("
                            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                            DEVICE_CHECK_STATE " INTEGER     NOT NULL,"
                            DEVICE_NAME " VARCHAR(255)       NOT NULL,"
                            DEVICE_AUTHOR " VARCHAR(255)     NOT NULL,"
                            DEVICE_NUMBER " VARCHAR(18)      NOT NULL,"
                            DEVICE_COST " VARCHAR(18)             NOT NULL,"
                            DEVICE_TICKET " INTEGER               NOT NULL,"
                            DEVICE_DATE " DATE            NOT NULL"
                            " )"
                    )){
        qDebug() << "DataBase: error of create " << DEVICE;
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
    return false;
}

/* Метод для вставки записи в таблицу устройств
 * */
bool DataBase::inserIntoDeviceTable(const QVariantList &data)
{
    /* Запрос SQL формируется из QVariantList,
     * в который передаются данные для вставки в таблицу.
     * */
    QSqlQuery query;
    /* В начале SQL запрос формируется с ключами,
     * которые потом связываются методом bindValue
     * для подстановки данных из QVariantList
     * */

    //qDebug()<<(data[0].toInt())<<(data[1].toString())<<(data[2].toString())<<(data[3].toString())<<(data[4].toString())<<(data[5].toInt())<<(data[6].toString());
    query.prepare("INSERT INTO " DEVICE " ( " DEVICE_CHECK_STATE ", "
                                              DEVICE_NAME ", "
                                              DEVICE_AUTHOR ", "
                                              DEVICE_NUMBER ", "
                                              DEVICE_COST ", "
                                              DEVICE_TICKET ", "
                                              DEVICE_DATE " ) "
                  "VALUES (:state, :name, :author, :number, :cost, :ticket, :date )");
    query.bindValue(":state",  data[0].toInt());
    query.bindValue(":name",    data[1].toString());
    query.bindValue(":author",          data[2].toString());
    query.bindValue(":number",         data[3].toString());
    query.bindValue(":cost",           data[4].toString());
    query.bindValue(":ticket",         data[5].toInt());
    query.bindValue(":date",           data[6].toString());
    // После чего выполняется запросом методом exec()
    if(!query.exec()){
        qDebug() << "error insert into " << DEVICE;
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
    return false;
}

bool DataBase::createUserTable()
{
    /* В данном случае используется формирование сырого SQL-запроса
     * с последующим его выполнением.
     * */

    QSqlQuery query;
    if(!query.exec( "CREATE TABLE " USERS " ("
                            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                            USER_LOGIN " VARCHAR(255)             NOT NULL,"
                            USER_PASSWORD " VARCHAR(255)          NOT NULL,"
                            USER_NAME " VARCHAR(255)              NOT NULL,"
                            USER_ROLE " VARCHAR(255)              NOT NULL,"
                            USER_TICKET " VARCHAR(255)            NOT NULL,"
                            USER_ADRESS " VARCHAR(255)            NOT NULL"
                            " )"
                    )){
        qDebug() << "DataBase: error of create " << USERS;
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
    return false;
}

bool DataBase::inserIntoUserTable(const QVariantList &data)
{
    /* Запрос SQL формируется из QVariantList,
     * в который передаются данные для вставки в таблицу.
     * */
    QSqlQuery query;
    query.prepare("INSERT INTO " USERS " ( " USER_LOGIN ", "
                                              USER_PASSWORD ", "
                                              USER_NAME ", "
                                              USER_ROLE ", "
                                              USER_TICKET ", "
                                              USER_ADRESS " ) "
                  "VALUES (:login, :PASSWORD, :NAME, :ROLE, :TICKET, :USER_ADRESS )");
    query.bindValue(":login",               data[0].toString());
    query.bindValue(":PASSWORD",            data[1].toString());
    query.bindValue(":NAME",                data[2].toString());
    query.bindValue(":ROLE",                data[3].toString());
    query.bindValue(":TICKET",              data[4].toString());
    query.bindValue(":USER_ADRESS",         data[5].toString());
    // После чего выполняется запросом методом exec()
    if(!query.exec()){
        qDebug() << "error insert into " << USERS;
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
    return false;
}
bool DataBase::createLibrarianTable()
{
    /* В данном случае используется формирование сырого SQL-запроса
     * с последующим его выполнением.
     * */

    QSqlQuery query;
    if(!query.exec( "CREATE TABLE " LIBRARIANS " ("
                            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                            LIBRARIAN_LOGIN " VARCHAR(255)             NOT NULL,"
                            LIBRARIAN_PASSWORD " VARCHAR(255)          NOT NULL,"
                            LIBRARIAN_NAME " VARCHAR(255)              NOT NULL,"
                            LIBRARIAN_ROLE " VARCHAR(255)              NOT NULL"
                            " )"
                    )){
        qDebug() << "DataBase: error of create " << LIBRARIANS;
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
    return false;
}
bool DataBase::inserIntoLibrarianTable(const QVariantList &data)
{
    /* Запрос SQL формируется из QVariantList,
     * в который передаются данные для вставки в таблицу.
     * */
    QSqlQuery query;
    /* В начале SQL запрос формируется с ключами,
     * которые потом связываются методом bindValue
     * для подстановки данных из QVariantList
     * */

    //qDebug()<<(data[0].toInt())<<(data[1].toString())<<(data[2].toString())<<(data[3].toString());
    query.prepare("INSERT INTO " LIBRARIANS " ( " LIBRARIAN_LOGIN ", "
                                              LIBRARIAN_PASSWORD ", "
                                              LIBRARIAN_NAME ", "
                                              LIBRARIAN_ROLE " ) "
                  "VALUES (:login, :PASSWORD, :NAME, :ROLE )");
    query.bindValue(":login",               data[0].toString());
    query.bindValue(":PASSWORD",            data[1].toString());
    query.bindValue(":NAME",                data[2].toString());
    query.bindValue(":ROLE",                data[3].toString());
    // После чего выполняется запросом методом exec()
    if(!query.exec()){
        qDebug() << "error insert into " << LIBRARIANS;
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
    return false;
}
