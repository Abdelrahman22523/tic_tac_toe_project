#include "confirmationdialoge.h"
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

    DifficultyDialog::DifficultyDialog(QWidget *parent) : QDialog(parent) {
        setWindowTitle("Choose AI Difficulty");
        setFixedSize(600, 600);
        layout = new QVBoxLayout(this);

        QLabel *titleLabel = new QLabel("Select AI Difficulty", this);
        QFont titleFont("Arial", 30, QFont::Bold); // Set font and size for the title
        titleLabel->setFont(titleFont);
        titleLabel->setStyleSheet("color: orange;"); // Set text color to white
        layout->addWidget(titleLabel);

        QPushButton *easyButton = new QPushButton("Easy", this);
        easyButton->setStyleSheet("QPushButton { background-color: #FFA500; color: black; font-size: 14px; padding: 6px; }"); // Set button color to orange, text color to black, and adjust font size and padding
        easyButton->setMaximumWidth(200); // Set maximum width
        connect(easyButton, &QPushButton::clicked, this, &DifficultyDialog::selectEasy);
        layout->addWidget(easyButton);



        QPushButton *mediumButton = new QPushButton("Medium", this);
        mediumButton->setStyleSheet("QPushButton { background-color: #FFA500; color: black; font-size: 14px; padding: 6px; }"); // Set button color to orange, text color to black, and adjust font size and padding
        mediumButton->setMaximumWidth(200); // Set maximum width
        connect(mediumButton, &QPushButton::clicked, this, &DifficultyDialog::selectMedium);
        layout->addWidget(mediumButton);

        QPushButton *hardButton = new QPushButton("Hard", this);
        hardButton->setStyleSheet("QPushButton { background-color: #FFA500; color: black; font-size: 14px; padding: 6px; }"); // Set button color to orange, text color to black, and adjust font size and padding
        hardButton->setMaximumWidth(200); // Set maximum width
        connect(hardButton, &QPushButton::clicked, this, &DifficultyDialog::selectHard);
        layout->addWidget(hardButton);







        setLayout(layout);
    }

