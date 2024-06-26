#include <QtTest/QtTest>
#include "../PlayAgainDialog.h"
#include <QPushButton>

class TestPlayAgainDialog : public QObject
{
    Q_OBJECT

private slots:
    void testYesClicked()
    {
        // Mock the PlayAgainDialog without relying on specific image loading
        PlayAgainDialog dialog;

        // Simulate clicking 'Yes' button
        QSignalSpy spy(&dialog, &PlayAgainDialog::Yes);
        QPushButton *yesButton = dialog.findChild<QPushButton*>("yesButton");
        QVERIFY(yesButton != nullptr); // Check if button is found
        QTest::mouseClick(yesButton, Qt::LeftButton);

        // Verify signal emission
        QCOMPARE(spy.count(), 1);  // Ensure the signal was emitted exactly once
    }

    void testNoClicked()
    {
        // Mock the PlayAgainDialog without relying on specific image loading
        PlayAgainDialog dialog;

        // Simulate clicking 'No' button
        QSignalSpy spy(&dialog, &PlayAgainDialog::No);
        QPushButton *noButton = dialog.findChild<QPushButton*>("noButton");
        QVERIFY(noButton != nullptr); // Check if button is found
        QTest::mouseClick(noButton, Qt::LeftButton);

        // Verify signal emission
        QCOMPARE(spy.count(), 1);  // Ensure the signal was emitted exactly once
    }
};

QTEST_MAIN(TestPlayAgainDialog)
#include "tst_test6.moc"
