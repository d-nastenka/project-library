#ifndef ISSUED_BOOKS_H
#define ISSUED_BOOKS_H

#include <QWidget>
#include "database_user.h"
#include "database.h"

namespace Ui {
class Issued_books;
}

class Issued_books : public QWidget
{
    Q_OBJECT

public:
    explicit Issued_books(QWidget *parent = nullptr);
    ~Issued_books();
    void getTicket(QString m_ticket);

private slots:
    void on_pushButton_clicked();

private:
    Ui::Issued_books *ui;
    DataBase        *db;
};

#endif // ISSUED_BOOKS_H
