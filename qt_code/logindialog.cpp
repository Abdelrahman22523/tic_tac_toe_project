#include "signupdialog.h"
#include "logindialog.h"
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
#include <QFont>

LoginDialog::LoginDialog(QWidget *parent) : QDialog(parent) {
    // Load background image
    QPixmap bkgnd("E:\\2nd year 2nd term assignments\\tic_tac_toe_project\\qt_code\\tic-tac-toe-background1.jpg");
    if (bkgnd.isNull()) {
        qDebug() << "Failed to load background image.";
    } else {
        qDebug() << "Background image loaded successfully. Size:" << bkgnd.size();
        bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
        QPalette palette;
        palette.setBrush(QPalette::Window, bkgnd);
        this->setPalette(palette);
    }

    setWindowTitle("Tic Tac Toe Login");
    setFixedSize(600, 600); // Set a fixed size for the window

    QVBoxLayout *layout = new QVBoxLayout(this);

    QLabel *titleLabel = new QLabel("Tic Tac Toe", this);
    QFont titleFont("Arial", 30, QFont::Bold); // Set font and size for the title
    titleLabel->setFont(titleFont);
    titleLabel->setStyleSheet("color: orange;"); // Set text color to white
    layout->addWidget(titleLabel);

    QHBoxLayout *usernameLayout = new QHBoxLayout;
    QLabel *usernameLabel = new QLabel("Username:", this);
    usernameLabel->setStyleSheet("color: white;"); // Set text color to white
    usernameEdit = new QLineEdit(this);
    usernameEdit->setStyleSheet("background-color: #383838; color: white; border: 1px solid #555; font-size: 14px; padding: 4px;"); // Set background color to dark gray, text color to white, and adjust font size and padding
    usernameEdit->setMaximumWidth(200);
    usernameLayout->addWidget(usernameLabel);
    usernameLayout->addWidget(usernameEdit);
    layout->addLayout(usernameLayout);

    QHBoxLayout *passwordLayout = new QHBoxLayout;
    QLabel *passwordLabel = new QLabel("Password:", this);
    passwordLabel->setStyleSheet("color: white;"); // Set text color to white
    passwordEdit = new QLineEdit(this);
    passwordEdit->setEchoMode(QLineEdit::Password);
    passwordEdit->setStyleSheet("background-color: #383838; color: white; border: 1px solid #555; font-size: 14px; padding: 4px;"); // Set background color to dark gray, text color to white, and adjust font size and padding
    passwordEdit->setMaximumWidth(200);
    passwordLayout->addWidget(passwordLabel);
    passwordLayout->addWidget(passwordEdit);
    layout->addLayout(passwordLayout);

    QPushButton *loginButton = new QPushButton("Login", this);
    loginButton->setStyleSheet("QPushButton { background-color: #FFA500; color: black; font-size: 14px; padding: 6px; }"); // Set button color to orange, text color to black, and adjust font size and padding
    loginButton->setMaximumWidth(200); // Set maximum width
    connect(loginButton, &QPushButton::clicked, this, &LoginDialog::login);
    layout->addWidget(loginButton);

    QPushButton *registerButton = new QPushButton("Register", this);
    registerButton->setStyleSheet("QPushButton { background-color: #FFA500; color: black; font-size: 14px; padding: 6px; }"); // Set button color to orange, text color to black, and adjust font size and padding
    registerButton->setMaximumWidth(200); // Set maximum width
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
