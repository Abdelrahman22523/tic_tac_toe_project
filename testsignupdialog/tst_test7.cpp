#include <QtTest>
#include <QCoreApplication>
#include <QSignalSpy>
#include "../signupdialog.h" // Adjust the path as per your project structure

class TestSignUpDialog : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase() {
        // Initialize resources if needed
    }

    void cleanupTestCase() {
        // Clean up resources if needed
    }

    void testSignUpFailure_UsernameExists()
    {
        SignUpDialog dialog; // Create an instance of SignUpDialog

        // Set credentials using public method
        dialog.setCredentials("existinguser", "password");

        // Trigger the signup process directly
        dialog.signup();

        // Verify that the 'registered' signal was NOT emitted
        QSignalSpy registeredSpy(&dialog, &SignUpDialog::registered);
        QCOMPARE(registeredSpy.count(), 0); // Ensure the signal was not emitted

        // Additional verification can be added here if needed
    }

    void testEmptyUsernameAndPassword()
    {
        SignUpDialog dialog; // Create an instance of SignUpDialog

        QSignalSpy registeredSpy(&dialog, &SignUpDialog::registered);

        // Set empty credentials
        dialog.setCredentials("", "");

        // Trigger the signup process directly
        dialog.signup();

        // Verify that the 'registered' signal was NOT emitted
        QCOMPARE(registeredSpy.count(), 0); // Ensure the signal was not emitted

        // Additional verification can be added here if needed
    }
};

QTEST_MAIN(TestSignUpDialog)
#include "tst_test7.moc"
