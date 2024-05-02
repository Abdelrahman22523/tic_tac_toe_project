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
    void gameModeSelected(int mode); // Signal to indicate the selected game mode: 0 for 1 vs 1, 1 for 1 vs AI

private slots:
    void on_buttonplay_clicked();
    void on_buttonhistory_clicked();

private:
    QPushButton *buttonplay;
    QPushButton *buttonhistory;
    QVBoxLayout *layout;
};

#endif // MENU_H
