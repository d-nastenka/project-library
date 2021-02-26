#ifndef ADD_READER_H
#define ADD_READER_H

#include <QWidget>

namespace Ui {
class add_reader;
}

class add_reader : public QWidget
{
    Q_OBJECT

public:
    explicit add_reader(QWidget *parent = nullptr);
    ~add_reader();

    QString getLogin();
    QString getPassword();
    QString getName();
    QString getAdress();
    QString getTicket();
signals:
    void addReader();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_lineEdit_textEdited(const QString &arg1);

    void on_lineEdit_2_textEdited(const QString &arg1);

    void on_lineEdit_3_textEdited(const QString &arg1);

    void on_lineEdit_4_textEdited(const QString &arg1);

    void on_lineEdit_5_textEdited(const QString &arg1);

private:
    Ui::add_reader *ui;
    QString m_login;
    QString m_password;
    QString m_name;
    QString m_adress;
    QString m_ticket;
};

#endif // ADD_READER_H
