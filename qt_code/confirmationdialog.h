#ifndef CONFIRMATIONDIALOG_H
#define CONFIRMATIONDIALOG_H

#include <QDialog>

class QPushButton;
class QVBoxLayout;
class QLabel;

class ConfirmationDialog : public QDialog {
    Q_OBJECT

public:
    ConfirmationDialog(QWidget *parent = nullptr);

signals:
    void gameModeSelected(int mode); // Signal to indicate the selected game mode: 0 for 1 vs 1, 1 for 1 vs AI, 2 for back

private slots:
    void on_button1vs1_clicked();
    void on_button1vsAI_clicked();
    void on_buttonBack_clicked();

private:
    QPushButton *button1vs1;
    QPushButton *button1vsAI;
    QPushButton *buttonBack;
    QVBoxLayout *layout;
};

#endif // CONFIRMATIONDIALOG_H
