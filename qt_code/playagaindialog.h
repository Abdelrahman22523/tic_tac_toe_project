#ifndef playagaindialog.h
#define playagaindialog.h

#include <QDialog>
#include <QLabel>
class QPushButton;
class QVBoxLayout;
class QLabel;


class PlayAgainDialog : public QDialog {
    Q_OBJECT

public:
    PlayAgainDialog(QWidget *parent = nullptr);

    void setMessage(const QString &message);

signals:
    void Yes();
    void No();

private slots:
    void yesClicked();
    void noClicked();

private:
    QLabel *messageLabel;
    QPushButton *yes;
    QPushButton *no;
    QVBoxLayout *layout;


};

#endif // PLAYAGAINDIALOG_H
