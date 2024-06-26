#include "logindialog.h"
#include "signupdialog.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QDebug>
#include <QSqlError>

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
    // Initialize UI components
    setWindowTitle("Tic Tac Toe Login");
    setFixedSize(600, 600);

    QVBoxLayout *layout = new QVBoxLayout(this);

    QLabel *titleLabel = new QLabel("Tic Tac Toe", this);
    titleLabel->setObjectName("titleLabel");  // Set object name
    QFont titleFont("Arial", 30, QFont::Bold);
    titleLabel->setFont(titleFont);
    titleLabel->setStyleSheet("color: orange;");
    layout->addWidget(titleLabel);

    QHBoxLayout *usernameLayout = new QHBoxLayout;
    QLabel *usernameLabel = new QLabel("Username:", this);
    usernameLabel->setObjectName("usernameLabel");  // Set object name
    usernameLabel->setStyleSheet("color: white;");
    usernameEdit = new QLineEdit(this);
    usernameEdit->setObjectName("usernameEdit");  // Set object name
    usernameEdit->setStyleSheet("background-color: #383838; color: white; border: 1px solid #555; font-size: 14px; padding: 4px;");
    usernameEdit->setMaximumWidth(200);
    usernameLayout->addWidget(usernameLabel);
    usernameLayout->addWidget(usernameEdit);
    layout->addLayout(usernameLayout);

    QHBoxLayout *passwordLayout = new QHBoxLayout;
    QLabel *passwordLabel = new QLabel("Password:", this);
    passwordLabel->setObjectName("passwordLabel");  // Set object name
    passwordLabel->setStyleSheet("color: white;");
    passwordEdit = new QLineEdit(this);
    passwordEdit->setObjectName("passwordEdit");  // Set object name
    passwordEdit->setEchoMode(QLineEdit::Password);
    passwordEdit->setStyleSheet("background-color: #383838; color: white; border: 1px solid #555; font-size: 14px; padding: 4px;");
    passwordEdit->setMaximumWidth(200);
    passwordLayout->addWidget(passwordLabel);
    passwordLayout->addWidget(passwordEdit);
    layout->addLayout(passwordLayout);

    QPushButton *loginButton = new QPushButton("Login", this);
    loginButton->setObjectName("loginButton");  // Set object name
    loginButton->setStyleSheet("QPushButton { background-color: #FFA500; color: black; font-size: 14px; padding: 6px; }");
    loginButton->setMaximumWidth(200);
    connect(loginButton, &QPushButton::clicked, this, &LoginDialog::login);
    layout->addWidget(loginButton);

    QPushButton *registerButton = new QPushButton("Register", this);
    registerButton->setObjectName("registerButton");  // Set object name
    registerButton->setStyleSheet("QPushButton { background-color: #FFA500; color: black; font-size: 14px; padding: 6px; }");
    registerButton->setMaximumWidth(200);
    connect(registerButton, &QPushButton::clicked, this, &LoginDialog::openSignUpDialog);
    layout->addWidget(registerButton);

    setLayout(layout);

    // Create SQLite connection and initialize database
    if (!createConnection()) {
        QMessageBox::critical(this, "Database Error", "Failed to connect to database.");
        return;
    }

    connect(this, &QDialog::finished, this, &LoginDialog::handleDialogClosed);
}

bool LoginDialog::createConnection() {
    // Set up the SQLite database
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("users.db");

    // Open database
    if (!db.open()) {
        qDebug() << "Error: Failed to connect database:" << db.lastError().text();
        return false;
    }

    // Create table if it doesn't exist
    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY AUTOINCREMENT, username TEXT UNIQUE, password TEXT)");

    return true;
}

void LoginDialog::login() {
    QString username = usernameEdit->text().trimmed();
    QString password = passwordEdit->text();

    qDebug() << "Attempting login with username:" << username << "and password:" << password;

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Login Failed", "Please enter both username and password.");
        return;
    }

    bool success = verifyCredentials(username, password);
    if (success) {
        qDebug() << "Login successful for user:" << username;
        QMessageBox::information(this, "Login Successful", "Welcome, " + username + "!");
        emit loggedIn(username);
        accept();
    } else {
        qDebug() << "Login failed for user:" << username;
        QMessageBox::warning(this, "Login Failed", "Invalid username or password.");
    }
}

bool LoginDialog::verifyCredentials(const QString &username, const QString &password) {
    QSqlQuery query;
    query.prepare("SELECT username FROM users WHERE username = :username AND password = :password");
    query.bindValue(":username", username);
    query.bindValue(":password", password);

    if (!query.exec()) {
        qDebug() << "Error executing query:" << query.lastError().text();
        return false;
    }

    bool result = query.next();
    qDebug() << "Query result for user" << username << ":" << result;
    return result; // Returns true if a record exists (username and password match)
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

QString LoginDialog::getUsername() const {
    return usernameEdit->text().trimmed();
}
// LOGINDIALOG_H
