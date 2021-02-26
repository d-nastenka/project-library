#ifndef USERDATABASE_H
#define USERDATABASE_H

#include <QObject>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QFile>
#include <QDate>
#include <QDebug>

/* Директивы имен таблицы, полей таблицы и базы данных */
#define DATABASE_HOSTNAME   "ExampleUSERDataBase"
#define DATABASE_NAME       "USERDataBase.db"

#define USERS                     "UserTable"
#define USER_LOGIN                "Login"
#define USER_PASSWORD             "Password"
#define USER_NAME                 "Name"
#define USER_ROLE                 "Role"
#define USER_TICKET               "Ticket"
#define USER_ADRESS               "Adress"

class UserDataBase : public QObject
{
    Q_OBJECT
public:
    explicit UserDataBase(QObject *parent = 0);
    ~UserDataBase();
    /* Методы для непосредственной работы с классом
     * Подключение к базе данных и вставка записей в таблицу
     * */
    void connectToUserDataBase();
    bool inserIntoUserTable(const QVariantList &data);
    void closeUserDataBase();

private:
    // Сам объект базы данных, с которым будет производиться работа
    QSqlDatabase    udb;

private:
    /* Внутренние методы для работы с базой данных
     * */
    bool openUserDataBase();
    bool restoreUserDataBase();
    bool createUserTable();
};

#endif // USERDATABASE_H
