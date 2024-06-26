#include "menu.h"
#include <QLabel>
#include <QDebug>
#include <QPalette>

Menu::Menu(QWidget *parent) : QDialog(parent),
    buttonplay(new QPushButton("Play", this)),
    buttonhistory(new QPushButton("History", this)),
    buttonback(new QPushButton("Log out", this)),
    layout(new QVBoxLayout(this))
{
    setupUI(); // Initialize UI components
}

void Menu::setupUI() {
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

    setWindowTitle("Start Game");
    setFixedSize(600, 600); // Set a fixed size for the window

    QLabel *titleLabel = new QLabel("Menu", this);
    QFont titleFont("Arial", 30, QFont::Bold); // Set font and size for the title
    titleLabel->setFont(titleFont);
    titleLabel->setStyleSheet("color: orange;"); // Set text color to orange
    layout->addWidget(titleLabel);

    buttonplay->setStyleSheet("QPushButton { background-color: #FFA500; color: black; font-size: 14px; padding: 6px; }"); // Set button style
    buttonplay->setMaximumWidth(200); // Set maximum width
    connect(buttonplay, &QPushButton::clicked, this, &Menu::on_buttonplay_clicked);
    layout->addWidget(buttonplay);

    buttonhistory->setStyleSheet("QPushButton { background-color: #FFA500; color: black; font-size: 14px; padding: 6px; }"); // Set button style
    buttonhistory->setMaximumWidth(200); // Set maximum width
    connect(buttonhistory, &QPushButton::clicked, this, &Menu::on_buttonhistory_clicked);
    layout->addWidget(buttonhistory);

    buttonback->setStyleSheet("QPushButton { background-color: #FFA500; color: black; font-size: 14px; padding: 6px; }"); // Set button style
    buttonback->setMaximumWidth(200); // Set maximum width
    connect(buttonback, &QPushButton::clicked, this, &Menu::on_buttonback_clicked);
    layout->addWidget(buttonback);

    setLayout(layout);
}

void Menu::on_buttonplay_clicked() {
    emit gameModeSelected(0);
    close();
}

void Menu::on_buttonhistory_clicked() {
    emit gameModeSelected(1);
    close();
}

void Menu::on_buttonback_clicked() {
    emit gameModeSelected(2);
    close();
}

void Menu::simulatePlayClick() {
    on_buttonplay_clicked();
}

void Menu::simulateHistoryClick() {
    on_buttonhistory_clicked();
}

void Menu::simulateBackClick() {
    on_buttonback_clicked();
}
