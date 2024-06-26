// history.h
#ifndef HISTORY_H
#define HISTORY_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlTableModel>
#include <QTableView>
#include <QVBoxLayout>
#include <QPushButton>

class History : public QWidget {
    Q_OBJECT

public:
    explicit History(const QString &username, QWidget *parent = nullptr);
    ~History();
    void addGame(const QString &player1, const QString &player2, const QString &winner, const QString &boardState);

signals:
    void back();

private slots:
    void back_clicked();

private:
    void setupModelAndView();

    QString currentUser;
    QSqlDatabase db;
    QSqlTableModel *model;
    QTableView *view;
    QPushButton *buttonback;
    QVBoxLayout *layout;
};

#endif // HISTORY_H
