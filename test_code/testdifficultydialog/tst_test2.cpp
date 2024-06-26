#include <QtTest>
#include <QCoreApplication>

#include "../difficultydialog.h"

class TestDifficultyDialog : public QObject
{
    Q_OBJECT

private slots:
    void testDifficultySelection();
    void testBackButton();
};

void TestDifficultyDialog::testDifficultySelection()
{
    DifficultyDialog dialog;

    QSignalSpy spy(&dialog, SIGNAL(difficultySelected(int)));

    // Simulate clicking on the Easy button
    QPushButton *easyButton = dialog.findChild<QPushButton*>("easyButton");
    QVERIFY(easyButton != nullptr);
    QTest::mouseClick(easyButton, Qt::LeftButton);

    // Check if the signal was emitted with the correct argument
    QCOMPARE(spy.count(), 1);
    QCOMPARE(spy.first().first().toInt(), 1); // Assuming easy is mapped to difficulty level 1
}

void TestDifficultyDialog::testBackButton()
{
    DifficultyDialog dialog;

    QSignalSpy backSpy(&dialog, SIGNAL(back()));

    // Simulate clicking on the Back button
    QPushButton *backButton = dialog.findChild<QPushButton*>("buttonback");
    QVERIFY(backButton != nullptr);
    QTest::mouseClick(backButton, Qt::LeftButton);

    // Check if the back signal was emitted
    QCOMPARE(backSpy.count(), 1);
}

QTEST_MAIN(TestDifficultyDialog)

#include "tst_test2.moc"
