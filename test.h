#ifndef TEST_H
#define TEST_H

#include <QObject>
#include <database.h>

class Test: public QObject
{
    Q_OBJECT
public:
    explicit Test(QObject *parent = 0);
private slots:
    void addUser();
    void addLibrarian();
    void removeLibrarian();
private:
    DataBase    *db;


};

#endif // TEST_H
