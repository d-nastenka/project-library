#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QFile>
#include <QDate>
#include <QDebug>

/* Директивы имен таблицы, полей таблицы и базы данных */
#define DATABASE_HOSTNAME   "ExampleDataBase"
#define DATABASE_NAME       "DataBase.db"

#define DEVICE                  "BooksTable"
#define DEVICE_CHECK_STATE      "Availible"
#define DEVICE_NAME             "Name"
#define DEVICE_AUTHOR           "Author"
#define DEVICE_NUMBER           "Number"
#define DEVICE_COST             "Cost"
#define DEVICE_TICKET           "Ticket"
#define DEVICE_DATE             "Date"

#define USERS                     "UserTable"
#define USER_LOGIN                "Login"
#define USER_PASSWORD             "Password"
#define USER_NAME                 "Name"
#define USER_ROLE                 "Role"
#define USER_TICKET               "Ticket"
#define USER_ADRESS               "Adress"

#define LIBRARIANS                "LibrarianTable"
#define LIBRARIAN_LOGIN           "Login"
#define LIBRARIAN_PASSWORD        "Password"
#define LIBRARIAN_NAME            "Name"
#define LIBRARIAN_ROLE            "Role"

class DataBase : public QObject
{
    Q_OBJECT
public:
    explicit DataBase(QObject *parent = 0);
    ~DataBase();
    /* Методы для непосредственной работы с классом
     * Подключение к базе данных и вставка записей в таблицу
     * */
    void connectToDataBase();
    bool inserIntoDeviceTable(const QVariantList &data);
    bool inserIntoUserTable(const QVariantList &data);
    bool inserIntoLibrarianTable(const QVariantList &data);
    void closeDataBase();

private:
    // Сам объект базы данных, с которым будет производиться работа
    QSqlDatabase    db;    

private:
    /* Внутренние методы для работы с базой данных
     * */
    bool openDataBase();
    bool restoreDataBase();
    bool createDeviceTable();
    bool createUserTable();
    bool createLibrarianTable();
};

#endif // DATABASE_H
