#include "test.h"
#include <QTest>
#include "reader.h"
#include "librarian.h"

Test::Test(QObject *parent) :
    QObject(parent)
{
    db = new DataBase();
    db->connectToDataBase();
}

void Test::addUser()
{
    reader a;
    //добавляем пользователя
    a.add("DGorban", "1234", "Горбань Даниил Юрьевич", "Мира д.11 кв. 21", "555533");
    //ищем пользователя
    QSqlQuery query("SELECT "
                    USERS ".id, "
                    USERS "." USER_NAME ", "
                    USERS "." USER_TICKET ", "
                    USERS "." USER_ADRESS ", "
                    USERS "." USER_ROLE
                    " FROM " USERS " WHERE Name = 'Горбань Даниил Юрьевич'");
    query.next();
    QCOMPARE("Горбань Даниил Юрьевич", query.value(1).toString());

    QSqlQuery query1;
    query1.prepare("DELETE FROM UserTable WHERE Name = 'Горбань Даниил Юрьевич'");
    query1.exec();

    a.add("AKozlova", "111111", "Козлова Алина Евгеньевна", "ул. Щорса д. 35 кв. 15", "555533");
    QSqlQuery query2("SELECT "
    USERS ".id, "
    USERS "." USER_NAME ", "
    USERS "." USER_TICKET ", "
    USERS "." USER_ADRESS ", "
    USERS "." USER_ROLE
    " FROM " USERS " WHERE Name = 'Козлова Алина Евгеньевна'");
    query2.next();
    QCOMPARE("Козлова Алина Евгеньевна", query2.value(1).toString());

    QSqlQuery query3;
    query3.prepare("DELETE FROM UserTable WHERE Name = 'Козлова Алина Евгеньевна'");
    query3.exec();

    a.add("AVeretnov", "000000", "Веретнов Алексей Дмитриевич", "ул. Авиаторов д. 98 кв. 55", "111111");
    QSqlQuery query4("SELECT "
    USERS ".id, "
    USERS "." USER_NAME ", "
    USERS "." USER_TICKET ", "
    USERS "." USER_ADRESS ", "
    USERS "." USER_ROLE
    " FROM " USERS " WHERE Name = 'Веретнов Алексей Дмитриевич'");
    query4.next();
    QCOMPARE("Веретнов Алексей Дмитриевич", query4.value(1).toString());

    QSqlQuery query5;
    query5.prepare("DELETE FROM UserTable WHERE Name = 'Веретнов Алексей Дмитриевич'");
    query5.exec();

    a.add("AAlekseeva", "8765", "Алексеева Анна Андреевна", "ул. Пирогова д. 5 кв. 66", "543211");
    QSqlQuery query6("SELECT "
    USERS ".id, "
    USERS "." USER_NAME ", "
    USERS "." USER_TICKET ", "
    USERS "." USER_ADRESS ", "
    USERS "." USER_ROLE
    " FROM " USERS " WHERE Name = 'Алексеева Анна Андреевна'");
    query6.next();
    QCOMPARE("Алексеева Анна Андреевна", query6.value(1).toString());

    QSqlQuery query7;
    query7.prepare("DELETE FROM UserTable WHERE Name = 'Алексеева Анна Андреевна'");
    query7.exec();

    a.add("DKirillov", "232323", "Кириллов Дмитрий Егорович", "ул. Шахтеров д. 45 кв. 102", "112233");
    QSqlQuery query8("SELECT "
    USERS ".id, "
    USERS "." USER_NAME ", "
    USERS "." USER_TICKET ", "
    USERS "." USER_ADRESS ", "
    USERS "." USER_ROLE
    " FROM " USERS " WHERE Name = 'Кириллов Дмитрий Егорович'");
    query8.next();
    QCOMPARE("Кириллов Дмитрий Егорович", query8.value(1).toString());
    QSqlQuery query9;
    query9.prepare("DELETE FROM UserTable WHERE Name = 'Кириллов Дмитрий Егорович'");
    query9.exec();
}
void Test::addLibrarian()
{
    librarian a;

    a.add("LVlasova", "7767", "Власова Любовь Леонидовна");

    QSqlQuery query("SELECT "
    LIBRARIANS ".id, "
    LIBRARIANS "." LIBRARIAN_NAME ", "
    LIBRARIANS "." LIBRARIAN_ROLE
    " FROM " LIBRARIANS " WHERE Name = 'Власова Любовь Леонидовна'");
    query.next();
    QCOMPARE("Власова Любовь Леонидовна", query.value(1).toString());

    a.add("DLeontev", "12345", "Леонтьев Дмитрий Константинович");

    QSqlQuery query1("SELECT "
    LIBRARIANS ".id, "
    LIBRARIANS "." LIBRARIAN_NAME ", "
    LIBRARIANS "." LIBRARIAN_ROLE
    " FROM " LIBRARIANS " WHERE Name = 'Леонтьев Дмитрий Константинович'");
    query1.next();
    QCOMPARE("Леонтьев Дмитрий Константинович", query1.value(1).toString());

    a.add("KGrigorieva", "00000", "Григорьева Ксения Владимировна");

    QSqlQuery query2("SELECT "
    LIBRARIANS ".id, "
    LIBRARIANS "." LIBRARIAN_NAME ", "
    LIBRARIANS "." LIBRARIAN_ROLE
    " FROM " LIBRARIANS " WHERE Name = 'Григорьева Ксения Владимировна'");
    query2.next();
    QCOMPARE("Григорьева Ксения Владимировна", query2.value(1).toString());

    a.add("VTerehov", "454545", "Терехов Владислав Олегович");

    QSqlQuery query3("SELECT "
    LIBRARIANS ".id, "
    LIBRARIANS "." LIBRARIAN_NAME ", "
    LIBRARIANS "." LIBRARIAN_ROLE
    " FROM " LIBRARIANS " WHERE Name = 'Терехов Владислав Олегович'");
    query3.next();
    QCOMPARE("Терехов Владислав Олегович", query3.value(1).toString());

    a.add("OPopova", "33333", "Попова Ольга Витальевна");

    QSqlQuery query4("SELECT "
    LIBRARIANS ".id, "
    LIBRARIANS "." LIBRARIAN_NAME ", "
    LIBRARIANS "." LIBRARIAN_ROLE
    " FROM " LIBRARIANS " WHERE Name = 'Попова Ольга Витальевна'");
    query4.next();
    QCOMPARE("Попова Ольга Витальевна", query4.value(1).toString());
}

void Test::removeLibrarian(){
    librarian a;

    a.remove("Власова Любовь Леонидовна");
    QSqlQuery query("SELECT "
    LIBRARIANS ".id, "
    LIBRARIANS "." LIBRARIAN_NAME ", "
    LIBRARIANS "." LIBRARIAN_ROLE
    " FROM " LIBRARIANS " WHERE Name = 'Власова Любовь Леонидовна'");

    query.next();
    QCOMPARE("", query.value(1).toString());

    a.remove("Леонтьев Дмитрий Константинович");
    QSqlQuery query1("SELECT "
    LIBRARIANS ".id, "
    LIBRARIANS "." LIBRARIAN_NAME ", "
    LIBRARIANS "." LIBRARIAN_ROLE
    " FROM " LIBRARIANS " WHERE Name = 'Леонтьев Дмитрий Константинович'");

    query1.next();
    QCOMPARE("", query1.value(1).toString());

    a.remove("Григорьева Ксения Владимировна");
    QSqlQuery query2("SELECT "
    LIBRARIANS ".id, "
    LIBRARIANS "." LIBRARIAN_NAME ", "
    LIBRARIANS "." LIBRARIAN_ROLE
    " FROM " LIBRARIANS " WHERE Name = 'Григорьева Ксения Владимировна'");

    query2.next();
    QCOMPARE("", query2.value(1).toString());

    a.remove("Терехов Владислав Олегович");
    QSqlQuery query3("SELECT "
    LIBRARIANS ".id, "
    LIBRARIANS "." LIBRARIAN_NAME ", "
    LIBRARIANS "." LIBRARIAN_ROLE
    " FROM " LIBRARIANS " WHERE Name = 'Терехов Владислав Олегович'");

    query3.next();
    QCOMPARE("", query3.value(1).toString());

    a.remove("Попова Ольга Витальевна");
    QSqlQuery query4("SELECT "
    LIBRARIANS ".id, "
    LIBRARIANS "." LIBRARIAN_NAME ", "
    LIBRARIANS "." LIBRARIAN_ROLE
    " FROM " LIBRARIANS " WHERE Name = 'Попова Ольга Витальевна'");

    query4.next();
    QCOMPARE("", query4.value(1).toString());
}


