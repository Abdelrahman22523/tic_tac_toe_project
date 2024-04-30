#ifndef SIGNUPDIALOG_H
#define SIGNUPDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>

class SignUpDialog : public QDialog {
    Q_OBJECT

public:
    SignUpDialog(QWidget *parent = nullptr);

signals:
    void registered(const QString &username);

private slots:
    void signup();

private:
    QLineEdit *usernameEdit;
    QLineEdit *passwordEdit;
    bool registerNewUser(const QString &username, const QString &password);
};

#endif // SIGNUPDIALOG_H
