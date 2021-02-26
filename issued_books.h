#ifndef ISSUED_BOOKS_H
#define ISSUED_BOOKS_H

#include <QWidget>
#include "database_user.h"
#include "database.h"

namespace Ui {
class issued_books;
}

class issued_books : public QWidget
{
    Q_OBJECT

public:
    explicit issued_books(QWidget *parent = nullptr);
    ~issued_books();
    void getTicket(QString m_ticket);

private slots:
    void on_pushButton_clicked();

private:
    Ui::issued_books *ui;
    DataBase        *db;
};

#endif // ISSUED_BOOKS_H
