// menu.h
#ifndef MENU_H
#define MENU_H

#include <QDialog>

class QPushButton;
class QVBoxLayout;
class QLabel;

class Menu : public QDialog {
    Q_OBJECT

public:
    Menu(QWidget *parent = nullptr);

signals:
    void gameModeSelected(int mode);    // Signal to indicate the selected game mode: 0 for Play, 1 for History
    void backToLogin(); // Signal to indicate the back button was clicked

private slots:
    void on_buttonplay_clicked();
    void on_buttonhistory_clicked();
    void on_buttonback_clicked(); // Slot for handling back button click

private:
    QPushButton *buttonplay;
    QPushButton *buttonhistory;
    QPushButton *buttonback; // Back button
    QVBoxLayout *layout;
};

#endif // MENU_H
