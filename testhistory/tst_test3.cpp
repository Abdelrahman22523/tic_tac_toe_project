#include <QApplication>
#include <QtTest/QtTest>
#include "../history.h"
#include <QLabel>

class TestHistory : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();
    void testInitialization();
    void testDatabaseOperations();
    void testUIElements();

private:
    History *history;
    QString testDbName;
};

void TestHistory::initTestCase()
{
    testDbName = "test_user";
    history = new History(testDbName);
}

void TestHistory::cleanupTestCase()
{
    delete history;
    QFile::remove(testDbName + "_games_history.db");
}

void TestHistory::testInitialization()
{
    QVERIFY(history->windowTitle() == "User History");
    QVERIFY(history->size() == QSize(600, 600));
    QVERIFY(history->styleSheet() == "background-color: #222; color: white;");
}

void TestHistory::testDatabaseOperations()
{
    history->addGame("Player1", "Player2", "Player1", "XOXOXOXOX");

    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "test_connection");
        db.setDatabaseName(testDbName + "_games_history.db");
        QVERIFY(db.open());

        QSqlQuery query(db);
        query.exec("SELECT * FROM games");
        QVERIFY(query.next());

        QCOMPARE(query.value("player1").toString(), QString("Player1"));
        QCOMPARE(query.value("player2").toString(), QString("Player2"));
        QCOMPARE(query.value("winner").toString(), QString("Player1"));
        QCOMPARE(query.value("board_state").toString(), QString("XOXOXOXOX"));

        db.close();
    }
    QSqlDatabase::removeDatabase("test_connection");
}

void TestHistory::testUIElements()
{
    QLabel *titleLabel = history->findChild<QLabel *>();
    QVERIFY(titleLabel != nullptr);
    QVERIFY(titleLabel->text() == "User History");

    QPushButton *backButton = history->findChild<QPushButton *>("buttonback"); // Use the object name
    QVERIFY(backButton != nullptr);
    QVERIFY(backButton->text() == "Back");

    QTableView *view = history->findChild<QTableView *>();
    QVERIFY(view != nullptr);
    QVERIFY(view->model() != nullptr);
    QVERIFY(view->model()->rowCount() == 1);
}

QTEST_MAIN(TestHistory)


#include "tst_test3.moc"
