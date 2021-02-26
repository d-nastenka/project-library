#include "database_user.h"
#include "QDebug"

UserDataBase::UserDataBase(QObject *parent) : QObject(parent)
{

}

UserDataBase::~UserDataBase()
{

}

/* Методы для подключения к базе данных
 * */
void UserDataBase::connectToUserDataBase()
{
    /* Перед подключением к базе данных производим проверку на её существование.
     * В зависимости от результата производим открытие базы данных или её восстановление
     * */

    if(!QFile("C:/example/" DATABASE_NAME).exists()){
        this->restoreUserDataBase();
    } else {
        this->openUserDataBase();
    }
}

/* Методы восстановления базы данных
 * */
bool UserDataBase::restoreUserDataBase()
{
    if(this->openUserDataBase()){
        if(!this->createUserTable()){
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
bool UserDataBase::openUserDataBase()
{
    /* База данных открывается по заданному пути
     * и имени базы данных, если она существует
     * */
    udb = QSqlDatabase::addDatabase("QSQLITE");
    udb.setHostName(DATABASE_HOSTNAME);
    udb.setDatabaseName("C:/example/" DATABASE_NAME);
    if(udb.open()){
        return true;
    } else {
        return false;
    }
}

/* Методы закрытия базы данных
 * */
void UserDataBase::closeUserDataBase()
{
    udb.close();
}

/* Метод для создания таблицы устройств в базе данных
 * */
bool UserDataBase::createUserTable()
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

/* Метод для вставки записи в таблицу устройств
 * */
bool UserDataBase::inserIntoUserTable(const QVariantList &data)
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
