#ifndef DEBT_H
#define DEBT_H

#include <QWidget>
#include <database.h>

namespace Ui {
class Debt;
}

class Debt : public QWidget
{
    Q_OBJECT

public:
    explicit Debt(QWidget *parent = nullptr);
    ~Debt();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Debt *ui;

    DataBase    *db;
};

#endif // DEBT_H
