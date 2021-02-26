#ifndef MAINWINDOW_H
#include <QMainWindow>
#include <QString>
#include <QtSql/QtSql>
#include "authorization.h"
#include "addbook.h"
#include "reader.h"
#include "add_reader.h"
#include "librarian.h"
#include "issued_books.h"
#include "debt.h"
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>

#include <QMainWindow>
#include <QSqlQuery>

#include <database.h>
#include <database_user.h>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

namespace Ui {
    class MainWindow;
}

struct Book{
    QString name;
    QString author;
    int numbers;
    int cost;
    int ticket;
    QDate date;
};
//Q_DECLARE_METATYPE(Book*)

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void display();

private:
    Ui::MainWindow *ui;
    Authorization ui_Auth; // экземпляры окна авторизации и окна регистрации
    AddBook ui_Add;
    Reader ui_reader;
    Librarian ui_librarian;
    Issued_books ui_ib;
    Debt ui_debt;
    //add_reader ui_add_reader;

    QString m_username; // строки для обработки
    QString m_userpass; // пользовательского ввода
    QString m_role;
    QString m_name;
    QString m_author;
    QString m_numbers;
    QString m_cost;
    QString m_ticket;

    bool m_loginSuccesfull;
    void createUI();
    void updateTable();

    //Ui::MainWindow  *ui;
    DataBase        *db;
    //UserDataBase    *udb;

private slots:
    void authorizeUser(); // пользовательские слоты
    void insertBook();
    //void addUSER();
    //void addREADER();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_action_2_triggered();
    void on_pushButton_3_clicked();
    void on_action_3_triggered();
    void on_action_5_triggered();
    void on_pushButton_4_clicked();
    void on_action_4_triggered();
};
#endif // MAINWINDOW_H
