QT += core gui quick sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    confirmationdialog.cpp \
    difficultydialog.cpp \
    history.cpp \
    logindialog.cpp \
    main.cpp \
    menu.cpp \
    playagaindialog.cpp \
    signupdialog.cpp \
    tictactoe.cpp \
    tictactoe1.cpp \
    tictactoe2.cpp \
    performanceoptimizer.cpp \  # Add your new source files here
    gameengine.cpp

HEADERS += \
    confirmationdialog.h \
    difficultydialog.h \
    history.h \
    logindialog.h \
    menu.h \
    playagaindialog.h \
    signupdialog.h \
    tictactoe.h \
    tictactoe1.h \
    tictactoe2.h \
    performanceoptimizer.h \  # Add your new header files here
    gameengine.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
