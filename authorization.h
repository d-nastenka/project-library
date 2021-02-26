#ifndef AUTHORIZATION_H
#define AUTHORIZATION_H

#include <QWidget>

namespace Ui {
class Authorization;
}

class Authorization : public QWidget
{
    Q_OBJECT

public:
    explicit Authorization(QWidget *parent = nullptr);
    ~Authorization();
    QString getLogin();
    QString getPass();

signals:
    void pushButton_clicked();

private slots:
    void on_pushButton_clicked();

    void on_lineEdit_textEdited(const QString &arg1);

    void on_lineEdit_2_textEdited(const QString &arg1);

private:
    Ui::Authorization *ui;
    QString m_username;
    QString m_userpass;
};

#endif // AUTHORIZATION_H
