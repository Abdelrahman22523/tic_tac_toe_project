#include "menu.h"
#include <QLabel>
#include <QMessageBox>
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QDebug>
#include <QDialog>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QFont>



Menu::Menu(QWidget *parent) : QDialog(parent) {
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

    layout = new QVBoxLayout(this);
    QLabel *titleLabel = new QLabel("Menu", this);
    QFont titleFont("Arial", 30, QFont::Bold); // Set font and size for the title
    titleLabel->setFont(titleFont);
    titleLabel->setStyleSheet("color: orange;"); // Set text color to white
    layout->addWidget(titleLabel);

    QPushButton *buttonplay = new QPushButton("Play", this);
    buttonplay->setStyleSheet("QPushButton { background-color: #FFA500; color: black; font-size: 14px; padding: 6px; }"); // Set button color to orange, text color to black, and adjust font size and padding
    buttonplay->setMaximumWidth(200); // Set maximum width
    connect(buttonplay, &QPushButton::clicked, this, &Menu::on_buttonplay_clicked);
    layout->addWidget(buttonplay);

    QPushButton *buttonhistory = new QPushButton("History", this);
    buttonhistory->setStyleSheet("QPushButton { background-color: #FFA500; color: black; font-size: 14px; padding: 6px; }"); // Set button color to orange, text color to black, and adjust font size and padding
    buttonhistory->setMaximumWidth(200); // Set maximum width //
    connect(buttonhistory, &QPushButton::clicked, this, &Menu::on_buttonhistory_clicked);
    layout->addWidget(buttonhistory);

    setLayout(layout);
}

void Menu::on_buttonplay_clicked() {
    emit gameModeSelected(0); //
}

void Menu::on_buttonhistory_clicked() {
    emit gameModeSelected(1);
}
