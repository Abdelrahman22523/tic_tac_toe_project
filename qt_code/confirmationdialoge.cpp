#include "confirmationdialoge.h"
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

ConfirmationDialog::ConfirmationDialog(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Start Game");

    // Create layout for confirmation dialog
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Label
    QLabel *label = new QLabel("Select The Mode", this);
    layout->addWidget(label);

    // "1 VS AI" button
    QPushButton *vsAIButton = new QPushButton("1 VS AI", this);
    connect(vsAIButton, &QPushButton::clicked, this, &ConfirmationDialog::oneVsAI);
    layout->addWidget(vsAIButton);

    // "1 VS 1" button
    QPushButton *vsOneButton = new QPushButton("1 VS 1", this);
    connect(vsOneButton, &QPushButton::clicked, this, &ConfirmationDialog::oneVsOne);
    layout->addWidget(vsOneButton);

    setLayout(layout);
}

void ConfirmationDialog::oneVsAI() {
    emit gameSelected(true); // Signal that 1 VS AI game is selected
    accept(); // Close the dialog
}

void ConfirmationDialog::oneVsOne() {
    emit gameSelected(false); // Signal that 1 VS 1 game is selected
    accept(); // Close the dialog
}
