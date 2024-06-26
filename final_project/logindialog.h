#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>

class LoginDialog : public QDialog {
    Q_OBJECT

public:
    LoginDialog(QWidget *parent = nullptr);
    QString getUsername() const;

signals:
    void loggedIn(const QString &username);
    void registered(const QString &username);
    void loginCancelled();

private slots:
    void login();
    void openSignUpDialog();
    void handleRegistration(const QString &username);
    void handleDialogClosed(int result);

private:
    QLineEdit *usernameEdit;
    QLineEdit *passwordEdit;
    QSqlDatabase db;

    bool createConnection();
    bool verifyCredentials(const QString &username, const QString &password);
};

#endif // LOGINDIALOG_H
