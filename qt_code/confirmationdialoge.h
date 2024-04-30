#ifndef CONFIRMATIONDIALOG_H
#define CONFIRMATIONDIALOG_H

#include <QDialog>

class ConfirmationDialog : public QDialog {
    Q_OBJECT

public:
    ConfirmationDialog(QWidget *parent = nullptr);

signals:
    void gameSelected(bool vsAI);

private slots:
    void oneVsAI();
    void oneVsOne();

private:
};

#endif // CONFIRMATIONDIALOG_H
