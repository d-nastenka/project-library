#ifndef LIBRARIAN_H
#define LIBRARIAN_H

#include <QWidget>
#include "database.h"
#include "add_librarian.h"

namespace Ui {
class Librarian;
}

class Librarian : public QWidget
{
    Q_OBJECT

public:
    explicit Librarian(QWidget *parent = nullptr);
    ~Librarian();
    void add(QString login, QString password, QString name);
    void remove(QString name);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();//Удалить


    void on_pushButton_3_clicked();

    void addLIBRERIAN();

private:
    Ui::Librarian *ui;

    Add_librarian ui_add_librarian;

    DataBase    *db;

    QString u_login;
    QString u_password;
    QString u_name;
};

#endif // LIBRARIAN_H
