#include "Playagaindialog.h"
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QDebug>
#include <QPixmap>
#include <QPalette>

PlayAgainDialog::PlayAgainDialog(QWidget *parent) : QDialog(parent) {
    // Load background image
    QPixmap bkgnd("E:\\2nd year 2nd term assignments\\tic_tac_toe_project\\qt_code\\tic-tac-toe-background1.jpg");
    if (bkgnd.isNull()) {
        qDebug() << "Failed to load background image.";
    } else {
        qDebug() << "Background image loaded successfully. Size:" << bkgnd.size();
        bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
        QPalette palette;
        palette.setBrush(QPalette::Window, bkgnd);
        this->setPalette(palette);
    }

    setWindowTitle("Game Over");
    setFixedSize(600, 600);

    layout = new QVBoxLayout(this);

    QLabel *titleLabel = new QLabel("Play Again?", this);
    QFont titleFont("Arial", 30, QFont::Bold);
    titleLabel->setFont(titleFont);
    titleLabel->setStyleSheet("color: orange;");
    layout->addWidget(titleLabel);

    QPushButton *yesButton = new QPushButton("Yes", this);
    yesButton->setObjectName("yesButton"); // Set object name for testability
    yesButton->setStyleSheet("QPushButton { background-color: #FFA500; color: black; font-size: 14px; padding: 6px; }");
    yesButton->setMaximumWidth(200);
    connect(yesButton, &QPushButton::clicked, this, &PlayAgainDialog::yesClicked);
    layout->addWidget(yesButton);

    QPushButton *noButton = new QPushButton("No", this);
    noButton->setObjectName("noButton"); // Set object name for testability
    noButton->setStyleSheet("QPushButton { background-color: #FFA500; color: black; font-size: 14px; padding: 6px; }");
    noButton->setMaximumWidth(200);
    connect(noButton, &QPushButton::clicked, this, &PlayAgainDialog::noClicked);
    layout->addWidget(noButton);

    // Set background color and text color for night mode
    setStyleSheet("background-color: #222; color: white;");

    setLayout(layout);
}

void PlayAgainDialog::yesClicked() {
    emit Yes();
    close();
}

void PlayAgainDialog::noClicked() {
    emit No();
    close();
}

