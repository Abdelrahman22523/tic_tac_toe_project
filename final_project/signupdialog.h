#ifndef SIGNUPDIALOG_H
#define SIGNUPDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QSqlDatabase>
#include <QSqlQuery>

class SignUpDialog : public QDialog {
    Q_OBJECT

public:
    explicit SignUpDialog(QWidget *parent = nullptr);
    ~SignUpDialog();

signals:
    void registered(const QString &username);

private slots:
    void signup();
    void goBack(); // Slot for handling back button click

private:
    void setupUI();
    bool createConnection();
    bool registerNewUser(const QString &username, const QString &password);

    QLineEdit *usernameEdit;
    QLineEdit *passwordEdit;
    QSqlDatabase db;
    QPushButton *backButton; // Declare back button
};

#endif // SIGNUPDIALOG_H
