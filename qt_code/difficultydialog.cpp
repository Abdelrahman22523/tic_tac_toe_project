#include "difficultydialog.h"
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QDebug>
#include <QPixmap>
#include <QPalette>

DifficultyDialog::DifficultyDialog(QWidget *parent) : QDialog(parent) {
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

    setWindowTitle("Choose AI Difficulty");
    setFixedSize(600, 600);
    layout = new QVBoxLayout(this);

    QLabel *titleLabel = new QLabel("Select AI Difficulty", this);
    QFont titleFont("Arial", 30, QFont::Bold);
    titleLabel->setFont(titleFont);
    titleLabel->setStyleSheet("color: orange;");
    layout->addWidget(titleLabel);

    QPushButton *easyButton = new QPushButton("Easy", this);
    easyButton->setStyleSheet("QPushButton { background-color: #FFA500; color: black; font-size: 14px; padding: 6px; }");
    easyButton->setMaximumWidth(200);
    connect(easyButton, &QPushButton::clicked, this, &DifficultyDialog::selectEasy);
    layout->addWidget(easyButton);

    QPushButton *mediumButton = new QPushButton("Medium", this);
    mediumButton->setStyleSheet("QPushButton { background-color: #FFA500; color: black; font-size: 14px; padding: 6px; }");
    mediumButton->setMaximumWidth(200);
    connect(mediumButton, &QPushButton::clicked, this, &DifficultyDialog::selectMedium);
    layout->addWidget(mediumButton);

    QPushButton *hardButton = new QPushButton("Hard", this);
    hardButton->setStyleSheet("QPushButton { background-color: #FFA500; color: black; font-size: 14px; padding: 6px; }");
    hardButton->setMaximumWidth(200);
    connect(hardButton, &QPushButton::clicked, this, &DifficultyDialog::selectHard);
    layout->addWidget(hardButton);

    buttonback = new QPushButton("Back", this);
    buttonback->setStyleSheet("QPushButton { background-color: #FFA500; color: black; font-size: 14px; padding: 6px; }");
    buttonback->setMaximumWidth(200);
    connect(buttonback, &QPushButton::clicked, this, &DifficultyDialog::back_clicked);
    layout->addWidget(buttonback);

    // Set background color and text color for night mode
    setStyleSheet("background-color: #222; color: white;");

    setLayout(layout);
}

void DifficultyDialog::selectEasy() {
    emit difficultySelected(1);
    close();
}

void DifficultyDialog::selectMedium() {
    emit difficultySelected(2);
    close();
}

void DifficultyDialog::selectHard() {
    emit difficultySelected(3);
    close();
}

void DifficultyDialog::back_clicked() {
    emit back();
    close();
}
