#include <QCoreApplication>
#include <QtTest>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include "../logindialog.h"

class TestLoginDialog : public QObject
{
    Q_OBJECT

public:
    TestLoginDialog();
    ~TestLoginDialog();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void testUIElements();
    void testLoginSuccess();
    void testLoginFailure();
    void testDatabaseConnection();

private:
    LoginDialog *loginDialog;
};

TestLoginDialog::TestLoginDialog() : loginDialog(nullptr) {}

TestLoginDialog::~TestLoginDialog() {}

void TestLoginDialog::initTestCase()
{
    loginDialog = new LoginDialog();

    // Set up the test database
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "test_connection");
    db.setDatabaseName(":memory:");  // Use in-memory database for testing

    if (!db.open()) {
        qDebug() << "Error: Failed to open test database:" << db.lastError().text();
        return;
    }

    QSqlQuery query(db);

    // Create a test user
    query.exec("CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY AUTOINCREMENT, username TEXT UNIQUE, password TEXT)");
    query.exec("INSERT INTO users (username, password) VALUES ('testuser', 'testpass')");
}

void TestLoginDialog::cleanupTestCase()
{
    delete loginDialog;

    // Close and remove the test database
    QSqlDatabase::removeDatabase("test_connection");
}

void TestLoginDialog::testUIElements()
{
    QVERIFY(loginDialog->findChild<QLabel *>("titleLabel") != nullptr);
    QVERIFY(loginDialog->findChild<QLineEdit *>("usernameEdit") != nullptr);
    QVERIFY(loginDialog->findChild<QLineEdit *>("passwordEdit") != nullptr);
    QVERIFY(loginDialog->findChild<QPushButton *>("loginButton") != nullptr);
    QVERIFY(loginDialog->findChild<QPushButton *>("registerButton") != nullptr);
}

void TestLoginDialog::testLoginSuccess()
{
    QLineEdit *usernameEdit = loginDialog->findChild<QLineEdit *>("usernameEdit");
    QLineEdit *passwordEdit = loginDialog->findChild<QLineEdit *>("passwordEdit");

    usernameEdit->setText("testuser");
    passwordEdit->setText("testpass");

    // Simulate button click
    QPushButton *loginButton = loginDialog->findChild<QPushButton *>("loginButton");
    QTest::mouseClick(loginButton, Qt::LeftButton);

    // Check if the login was successful
    QVERIFY(loginDialog->result() == QDialog::Accepted);
}

void TestLoginDialog::testLoginFailure()
{
    // Reset dialog state
    delete loginDialog;
    loginDialog = new LoginDialog();

    QLineEdit *usernameEdit = loginDialog->findChild<QLineEdit *>("usernameEdit");
    QLineEdit *passwordEdit = loginDialog->findChild<QLineEdit *>("passwordEdit");

    usernameEdit->setText("wronguser");
    passwordEdit->setText("wrongpass");

    // Simulate button click
    QPushButton *loginButton = loginDialog->findChild<QPushButton *>("loginButton");
    QTest::mouseClick(loginButton, Qt::LeftButton);

    // Check if the login failed
    QVERIFY(loginDialog->result() == QDialog::Rejected);
}

void TestLoginDialog::testDatabaseConnection()
{
    QSqlDatabase db = QSqlDatabase::database("test_connection");

    // Check if the database connection is open
    QVERIFY(db.isOpen());
}

QTEST_MAIN(TestLoginDialog)



#include "tst_test4.moc"
