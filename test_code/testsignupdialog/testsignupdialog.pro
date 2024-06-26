QT += testlib
QT += core gui widgets
QT += core gui quick sql
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

SOURCES +=  tst_test7.cpp \
   ../confirmationdialog.cpp \
   ../difficultydialog.cpp \
   ../history.cpp \
   ../logindialog.cpp \
   ../mainwindow.cpp \
   ../menu.cpp \
   ../playagaindialog.cpp \
   ../signupdialog.cpp \
   ../tictactoe.cpp \
   ../tictactoe1.cpp \
   ../tictactoe2.cpp
   FORMS += \
       ../mainwindow.ui
       HEADERS += \
           ../confirmationdialog.h \
           ../difficultydialog.h \
           ../history.h \
           ../logindialog.h \
           ../mainwindow.h \
           ../menu.h \
           ../playagaindialog.h \
           ../signupdialog.h \
           ../tictactoe.h \
           ../tictactoe1.h \
           ../tictactoe2.h
    TARGET = Mytestsignupdialog
