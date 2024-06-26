#ifndef DIFFICULTYDIALOG_H
#define DIFFICULTYDIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QRadioButton>
#include <QPushButton>

class DifficultyDialog : public QDialog {
    Q_OBJECT

public:
    explicit DifficultyDialog(QWidget *parent = nullptr);

signals:
    void difficultySelected(int difficulty);
    void back();

private slots:
    void selectEasy();
    void selectMedium();
    void selectHard();
    void back_clicked();

private:
    QVBoxLayout *layout;
    QPushButton *easyButton;
    QPushButton *mediumButton;
    QPushButton *hardButton;
    QPushButton *buttonback;
};

#endif // DIFFICULTYDIALOG_H
