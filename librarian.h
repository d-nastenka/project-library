#ifndef LIBRARIAN_H
#define LIBRARIAN_H

#include <QWidget>
#include "database.h"
#include "add_librarian.h"

namespace Ui {
class librarian;
}

class librarian : public QWidget
{
    Q_OBJECT

public:
    explicit librarian(QWidget *parent = nullptr);
    ~librarian();
    void add(QString login, QString password, QString name);
    void remove(QString name);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();//Удалить


    void on_pushButton_3_clicked();

    void addLIBRERIAN();

private:
    Ui::librarian *ui;

    add_librarian ui_add_librarian;

    DataBase    *db;

    QString u_login;
    QString u_password;
    QString u_name;
};

#endif // LIBRARIAN_H
