#ifndef ADDBOOK_H
#define ADDBOOK_H

#include <QWidget>

namespace Ui {
class addBook;
}

class addBook : public QWidget
{
    Q_OBJECT

public:
    explicit addBook(QWidget *parent = nullptr);
    ~addBook();
    QString getName();
    QString getAuthor();
    QString getNumbers();
    QString getCost();

signals:
    void addpushButton_clicked();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_lineEdit_textEdited(const QString &arg1);

    void on_lineEdit_2_textEdited(const QString &arg1);

    void on_lineEdit_3_textEdited(const QString &arg1);

    void on_lineEdit_4_textEdited(const QString &arg1);

private:
    Ui::addBook *ui;
    QString m_name;
    QString m_author;
    QString m_numbers;
    QString m_cost;
};

#endif // ADDBOOK_H
