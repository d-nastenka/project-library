QT       += core gui
QT       += sql
QT       += testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    add_librarian.cpp \
    add_reader.cpp \
    addbook.cpp \
    authorization.cpp \
    database.cpp \
    debt.cpp \
    issued_books.cpp \
    librarian.cpp \
    main.cpp \
    mainwindow.cpp \
    reader.cpp \
    test.cpp

HEADERS += \
    add_librarian.h \
    add_reader.h \
    addbook.h \
    authorization.h \
    database.h \
    debt.h \
    issued_books.h \
    librarian.h \
    mainwindow.h \
    reader.h \
    test.h

FORMS += \
    add_librarian.ui \
    add_reader.ui \
    addbook.ui \
    authorization.ui \
    debt.ui \
    issued_books.ui \
    librarian.ui \
    mainwindow.ui \
    reader.ui

TRANSLATIONS += \
    projL_ru_RU.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
