#ifndef READER_H
#define READER_H

#include <QWidget>
#include "add_reader.h"
#include "database.h"

namespace Ui {
class Reader;
}

class Reader : public QWidget
{
    Q_OBJECT

public:
    explicit Reader(QWidget *parent = nullptr);
    ~Reader();
    void add(QString login, QString password, QString name, QString adress, QString number);

signals:
    //void addUser();
private slots:
    void on_pushButton_clicked();
    void addUSER();
    void on_pushButton_3_clicked();

private:
    Ui::Reader *ui;
    Add_reader ui_add_reader;

    DataBase    *db;

    QString u_login;
    QString u_password;
    QString u_name;
    QString u_adress;
    QString u_number;
};

#endif // READER_H
