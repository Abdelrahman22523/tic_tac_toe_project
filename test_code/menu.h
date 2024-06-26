#ifndef MENU_H
#define MENU_H

#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>

class Menu : public QDialog
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = nullptr);
    // Public methods to simulate button clicks
    void simulatePlayClick();
    void simulateHistoryClick();
    void simulateBackClick();

signals:
    void gameModeSelected(int mode);

private slots:
    // Private slots for actual button clicks
    void on_buttonplay_clicked();
    void on_buttonhistory_clicked();
    void on_buttonback_clicked();

private:
    QPushButton *buttonplay;
    QPushButton *buttonhistory;
    QPushButton *buttonback;
    QVBoxLayout *layout;

    void setupUI(); // Helper function to initialize UI components
};

#endif // MENU_H
