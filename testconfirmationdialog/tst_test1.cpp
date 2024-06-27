#include <QtTest>
#include <QPushButton>
#include <QtTest>
#include <QPushButton>
#include <QSignalSpy>
#include "..\confirmationdialog.h"

class ConfirmationDialogTest : public QObject
{
    Q_OBJECT

private slots:
    void testButton1vs1Click();
    void testButton1vsAIClick();
    void testBackButtonClick();

private:
    ConfirmationDialog *dialog;

private slots:
    void initTestCase();
    void cleanupTestCase();
};

void ConfirmationDialogTest::initTestCase()
{
    dialog = new ConfirmationDialog();
    // dialog->show(); // Optional: Show the dialog for visual inspection
}

void ConfirmationDialogTest::cleanupTestCase()
{
    delete dialog;
}

void ConfirmationDialogTest::testButton1vs1Click()
{
    QSignalSpy spy(dialog, &ConfirmationDialog::gameModeSelected);

    // Simulate a click on the "1 VS 1" button
    QPushButton button1vs1 = dialog->findChild<QPushButton>("button1vs1");
    QVERIFY2(button1vs1 != nullptr, "Button '1 VS 1' not found.");
    QTest::mouseClick(button1vs1, Qt::LeftButton);

    // Check that the signal was emitted with the correct argument
    QCOMPARE(spy.count(), 1);
    QCOMPARE(spy.takeFirst().at(0).toInt(), 0); // Expected game mode value for 1 vs 1
}

void ConfirmationDialogTest::testButton1vsAIClick()
{
    QSignalSpy spy(dialog, &ConfirmationDialog::gameModeSelected);

    // Simulate a click on the "1 VS AI" button
    QPushButton button1vsAI = dialog->findChild<QPushButton>("button1vsAI");
    QVERIFY2(button1vsAI != nullptr, "Button '1 VS AI' not found.");
    QTest::mouseClick(button1vsAI, Qt::LeftButton);

    // Check that the signal was emitted with the correct argument
    QCOMPARE(spy.count(), 1);
    QCOMPARE(spy.takeFirst().at(0).toInt(), 1); // Expected game mode value for 1 vs AI
}

void ConfirmationDialogTest::testBackButtonClick()
{
    QSignalSpy spy(dialog, &ConfirmationDialog::gameModeSelected);

    // Simulate a click on the "Back" button
    QPushButton buttonBack = dialog->findChild<QPushButton>("buttonBack");
    QVERIFY2(buttonBack != nullptr, "Button 'Back' not found.");
    QTest::mouseClick(buttonBack, Qt::LeftButton);

    // Check that the signal was emitted with the correct argument
    QCOMPARE(spy.count(), 1);
    QCOMPARE(spy.takeFirst().at(0).toInt(), 2); // Expected game mode value for back button
}

QTEST_MAIN(ConfirmationDialogTest)

#include "tst_test1.moc"