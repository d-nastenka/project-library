#ifndef DEBT_H
#define DEBT_H

#include <QWidget>
#include <database.h>

namespace Ui {
class debt;
}

class debt : public QWidget
{
    Q_OBJECT

public:
    explicit debt(QWidget *parent = nullptr);
    ~debt();

private slots:
    void on_pushButton_clicked();

private:
    Ui::debt *ui;

    DataBase    *db;
};

#endif // DEBT_H
