#ifndef ADD_LIBRARIAN_H
#define ADD_LIBRARIAN_H

#include <QWidget>

namespace Ui {
class add_librarian;
}

class add_librarian : public QWidget
{
    Q_OBJECT

public:
    explicit add_librarian(QWidget *parent = nullptr);
    ~add_librarian();

    QString getLogin();
    QString getPassword();
    QString getName();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_lineEdit_textEdited(const QString &arg1);

    void on_lineEdit_2_textEdited(const QString &arg1);

    void on_lineEdit_3_textEdited(const QString &arg1);

signals:
    void addLibrerian();

private:
    Ui::add_librarian *ui;
    QString m_login;
    QString m_password;
    QString m_name;
};

#endif // ADD_LIBRARIAN_H
