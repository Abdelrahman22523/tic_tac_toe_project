// confirmationdialog.cpp
#include "confirmationdialog.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

ConfirmationDialog::ConfirmationDialog(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Start Game");

    layout = new QVBoxLayout(this);

    QLabel *label = new QLabel("Select The Mode", this);
    layout->addWidget(label);

    button1vs1 = new QPushButton("1 VS AI", this);
    connect(button1vs1, &QPushButton::clicked, this, &ConfirmationDialog::on_button1vs1_clicked);
    layout->addWidget(button1vs1);

    button1vsAI = new QPushButton("1 VS 1", this);
    connect(button1vsAI, &QPushButton::clicked, this, &ConfirmationDialog::on_button1vsAI_clicked);
    layout->addWidget(button1vsAI);

    setLayout(layout);
}

void ConfirmationDialog::on_button1vs1_clicked() {
    emit gameModeSelected(0); // 1 vs 1 mode selected
}

void ConfirmationDialog::on_button1vsAI_clicked() {
    emit gameModeSelected(1); // 1 vs AI mode selected
}
