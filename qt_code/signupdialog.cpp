#include "signupdialog.h"
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QSpacerItem>

SignUpDialog::SignUpDialog(QWidget *parent) : QDialog(parent) {
    // Set window title
    setWindowTitle("Sign Up");

    // Set window size
    setFixedSize(600, 600);

    // Set up layout
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Add spacer for top alignment
    layout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));

    // Add username label and line edit
    // QLabel *usernameLabel = new QLabel("Username:", this);
    // layout->addWidget(usernameLabel, 0, Qt::AlignHCenter); // Align label to the center horizontally
    // usernameEdit = new QLineEdit(this);
    // passwordEdit->setMaximumWidth(200);
    // usernameEdit->setStyleSheet("background-color: #383838; color: white; border: 1px solid #555; font-size: 14px; padding: 4px;"); // Dark mode style
    // layout->addWidget(usernameEdit);

    // // Add password label and line edit
    // QLabel *passwordLabel = new QLabel("Password:", this);
    // layout->addWidget(passwordLabel, 0, Qt::AlignHCenter); // Align label to the center horizontally
    // passwordEdit = new QLineEdit(this);
    // passwordEdit->setMaximumWidth(200);
    // passwordEdit->setEchoMode(QLineEdit::Password);
    // passwordEdit->setStyleSheet("background-color: #383838; color: white; border: 1px solid #555; font-size: 14px; padding: 4px;"); // Dark mode style
    // layout->addWidget(passwordEdit);
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

    // Add sign up button
    QPushButton *signupButton = new QPushButton("Sign Up", this);
    signupButton->setStyleSheet("QPushButton { background-color: #FFA500; color: black; font-size: 14px; padding: 6px; }"); // Orange button in dark mode
    signupButton->setMaximumWidth(150); // Set maximum width
    connect(signupButton, &QPushButton::clicked, this, &SignUpDialog::signup);
    layout->addWidget(signupButton, 0, Qt::AlignHCenter); // Align button to the center horizontally

    // Add spacer for bottom alignment
    layout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));

    // Set layout
    setLayout(layout);

    // Set background image
    QPixmap bkgnd("E:\\2nd year 2nd term assignments\\tic_tac_toe_project\\qt_code\\tic-tac-toe-background1.jpg");
    if (!bkgnd.isNull()) {
        bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
        QPalette palette;
        palette.setBrush(QPalette::Window, bkgnd);
        this->setPalette(palette);
    }
}

void SignUpDialog::signup() {
    QString username = usernameEdit->text();
    QString password = passwordEdit->text();

    bool success = registerNewUser(username, password);
    if (success) {
        // QMessageBox::information(this, "Sign-up Successful", "Account created for " + username + ".");
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
