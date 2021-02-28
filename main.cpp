#include "mainwindow.h"
#include <QApplication>
#include <QTest>
#include <test.h>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    freopen("testing.log", "w", stdout);
    QTest::qExec(new Test, argc, argv);

    w.show();

    return a.exec();
}
