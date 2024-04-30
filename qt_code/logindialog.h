#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>

class LoginDialog : public QDialog {
    Q_OBJECT

public:
    LoginDialog(QWidget *parent = nullptr);

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
};

#endif // LOGINDIALOG_H
