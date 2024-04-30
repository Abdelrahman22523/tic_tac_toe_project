#include "signupdialog.h"
#include <QLabel>
#include <QMessageBox>
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QDebug>
#include <QMessageBox>
#include <QDialog>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <limits>

SignUpDialog::SignUpDialog(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Sign Up");

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

    QPushButton *signupButton = new QPushButton("Sign Up", this);
    connect(signupButton, &QPushButton::clicked, this, &SignUpDialog::signup);
    layout->addWidget(signupButton);

    setLayout(layout);
}

void SignUpDialog::signup() {
    QString username = usernameEdit->text();
    QString password = passwordEdit->text();

    bool success = registerNewUser(username, password);
    if (success) {
        QMessageBox::information(this, "Sign-up Successful", "Account created for " + username + ".");
        emit registered(username);
        accept();
    } else {
        QMessageBox::warning(this, "Registration Failed", "Username already exists.");
    }
}

bool SignUpDialog::registerNewUser(const QString &username, const QString &password) {
    // Dummy registration: Allow registration if username is not empty
    // (simulating that username should be unique in a real application)
    if (username.isEmpty()) return false;
    // Perform registration logic here
    // For demonstration purposes, just returning true
    return true;
}
