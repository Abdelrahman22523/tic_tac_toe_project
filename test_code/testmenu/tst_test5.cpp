#include <QtTest>
#include "../menu.h"

class TestMenu : public QObject
{
    Q_OBJECT

private slots:
    // Test case for button clicks
    void testButtonClicked_data();
    void testButtonClicked();

private:
    Menu *menu; // Instance of the Menu class for testing

public:
    TestMenu() : menu(nullptr) {}
    ~TestMenu() {}

private slots:
    void initTestCase() {
        menu = new Menu();
        QVERIFY(menu); // Verify menu is valid
    }

    void cleanupTestCase() {
        delete menu;
        menu = nullptr;
    }
};

void TestMenu::testButtonClicked_data() {
    QTest::addColumn<int>("buttonIndex");
    QTest::newRow("PlayButton") << 0;
    QTest::newRow("HistoryButton") << 1;
    QTest::newRow("BackButton") << 2;
}

void TestMenu::testButtonClicked() {
    QFETCH(int, buttonIndex);

    // Create a QSignalSpy to monitor the emitted signal
    QSignalSpy spy(menu, &Menu::gameModeSelected);

    // Simulate button click based on buttonIndex using public methods
    switch (buttonIndex) {
    case 0:
        menu->simulatePlayClick();
        break;
    case 1:
        menu->simulateHistoryClick();
        break;
    case 2:
        menu->simulateBackClick();
        break;
    default:
        QFAIL("Unknown button index");
    }

    // Check if the correct signal was emitted
    QCOMPARE(spy.count(), 1);
    QCOMPARE(spy.at(0).at(0).toInt(), buttonIndex);
}

QTEST_MAIN(TestMenu)



#include "tst_test5.moc"
