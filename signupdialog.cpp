#include "signupdialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QDebug>
#include <QSqlError>////>
#include <QSqlQuery>>
SignUpDialog::SignUpDialog(QWidget *parent) : QDialog(parent) {
    setupUI(); // Call setupUI function to initialize UI elements

    // Create SQLite connection and initialize database
    if (!createConnection()) {
        QMessageBox::critical(this, "Database Error", "Failed to connect to database.");
        return;
    }

    connect(backButton, &QPushButton::clicked, this, &SignUpDialog::goBack);
}

SignUpDialog::~SignUpDialog() {
    // Clean up resources if needed
}

void SignUpDialog::setupUI() {
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

    // Set window title
    setWindowTitle("Sign Up");

    // Set window size
    setFixedSize(600, 600);

    // Set up layout
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Add spacer for top alignment
    layout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));

    // Add username label and line edit
    QHBoxLayout *usernameLayout = new QHBoxLayout;
    QLabel *usernameLabel = new QLabel("Username:", this);
    usernameLabel->setStyleSheet("color: white;");
    usernameEdit = new QLineEdit(this);
    usernameEdit->setStyleSheet("background-color: #383838; color: white; border: 1px solid #555; font-size: 14px; padding: 4px;");
    usernameEdit->setMaximumWidth(200);
    usernameLayout->addWidget(usernameLabel);
    usernameLayout->addWidget(usernameEdit);
    layout->addLayout(usernameLayout);

    // Add password label and line edit
    QHBoxLayout *passwordLayout = new QHBoxLayout;
    QLabel *passwordLabel = new QLabel("Password:", this);
    passwordLabel->setStyleSheet("color: white;");
    passwordEdit = new QLineEdit(this);
    passwordEdit->setEchoMode(QLineEdit::Password);
    passwordEdit->setStyleSheet("background-color: #383838; color: white; border: 1px solid #555; font-size: 14px; padding: 4px;");
    passwordEdit->setMaximumWidth(200);
    passwordLayout->addWidget(passwordLabel);
    passwordLayout->addWidget(passwordEdit);
    layout->addLayout(passwordLayout);

    // Add sign up button
    QPushButton *signupButton = new QPushButton("Sign Up", this);
    signupButton->setStyleSheet("QPushButton { background-color: #FFA500; color: black; font-size: 14px; padding: 6px; }");
    signupButton->setMaximumWidth(150);
    connect(signupButton, &QPushButton::clicked, this, &SignUpDialog::signup);
    layout->addWidget(signupButton, 0, Qt::AlignHCenter);

    // Add back button
    backButton = new QPushButton("Back", this);
    backButton->setStyleSheet(" QPushButton { background-color: #FFA500; color: black; font-size: 14px; padding: 6px; }");
    backButton->setMaximumWidth(150);
    connect(backButton, &QPushButton::clicked, this, &SignUpDialog::goBack);
    layout->addWidget(backButton, 0, Qt::AlignHCenter);

    // Add spacer for bottom alignment
    layout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));

    // Set layout
    setLayout(layout);
}

bool SignUpDialog::createConnection() {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("users.db");

    if (!db.open()) {
        qDebug() << "Error: Failed to connect database:" << db.lastError().text();
        return false;
    }

    QSqlQuery query;
    QString createTableQuery = "CREATE TABLE IF NOT EXISTS users ("
                               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                               "username TEXT UNIQUE NOT NULL, "
                               "password TEXT NOT NULL)";
    if (!query.exec(createTableQuery)) {
        qDebug() << "Error: Failed to create table:" << query.lastError().text();
        return false;
    }

    return true;
}

void SignUpDialog::signup() {
    QString username = usernameEdit->text().trimmed();
    QString password = passwordEdit->text();

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Registration Failed", "Please enter both username and password.");
        return;
    }

    bool success = registerNewUser(username, password);
    if (success) {
        emit registered(username);
        accept();
    } else {
        QMessageBox::warning(this, "Registration Failed", "Username already exists or an error occurred.");
    }
}

bool SignUpDialog::registerNewUser(const QString &username, const QString &password) {
    QSqlQuery query;
    query.prepare("INSERT INTO users (username, password) VALUES (:username, :password)");
    query.bindValue(":username", username);
    query.bindValue(":password", password);

    if (!query.exec()) {
        if (query.lastError().nativeErrorCode() == "23505") {
            return false; // Username already exists
        }
        qDebug() << "Error executing query:" << query.lastError().text();
        return false;
    }

    return true;
}

void SignUpDialog::goBack() {
    reject(); // Close the dialog without accepting
}

void SignUpDialog::setCredentials(const QString &username, const QString &password) {
    // Set username and password internally (no direct access to private members)
    usernameEdit->setText(username);
    passwordEdit->setText(password);
}
