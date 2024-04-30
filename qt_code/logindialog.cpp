#include "logindialog.h"
#include "signupdialog.h"
#include <QLabel>
#include <QMessageBox>
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QDebug>
#include <QDialog>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <limits>

LoginDialog::LoginDialog(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Login");

    QVBoxLayout *layout = new QVBoxLayout(this);

    QLabel *usernameLabel = new QLabel("Username:", this);
    usernameEdit = new QLineEdit(this);
    layout->addWidget(usernameLabel);
    layout->addWidget(usernameEdit);

    QLabel *passwordLabel = new QLabel("Password:", this);
    passwordEdit = new QLineEdit(this);
    passwordEdit->setEchoMode(QLineEdit::Password);
    layout->addWidget(passwordLabel);
    layout->addWidget(passwordEdit);

    QPushButton *loginButton = new QPushButton("Login", this);
    connect(loginButton, &QPushButton::clicked, this, &LoginDialog::login);
    layout->addWidget(loginButton);

    QPushButton *registerButton = new QPushButton("Register", this);
    connect(registerButton, &QPushButton::clicked, this, &LoginDialog::openSignUpDialog);
    layout->addWidget(registerButton);

    setLayout(layout);

    connect(this, &QDialog::finished, this, &LoginDialog::handleDialogClosed);
}

void LoginDialog::login() {
    QString username = usernameEdit->text();
    QString password = passwordEdit->text();

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Login Failed", "Please enter both username and password.");
    } else {
        QMessageBox::information(this, "Login Successful", "Welcome, " + username + "!");
        emit loggedIn(username);
        accept();
    }
}

void LoginDialog::openSignUpDialog() {
    SignUpDialog signUpDialog;
    connect(&signUpDialog, &SignUpDialog::registered, this, &LoginDialog::handleRegistration);
    signUpDialog.exec();
}

void LoginDialog::handleRegistration(const QString &username) {
    QMessageBox::information(this, "Sign-up Successful", "Account created for " + username + ".");
    emit registered(username);
}

void LoginDialog::handleDialogClosed(int result) {
    if (result == QDialog::Rejected) {
        emit loginCancelled();
    }
}
