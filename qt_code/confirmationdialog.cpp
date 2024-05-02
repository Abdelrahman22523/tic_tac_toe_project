#include "confirmationdialog.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

ConfirmationDialog::ConfirmationDialog(QWidget *parent) : QDialog(parent) {
    // Set window title
    setWindowTitle("Start Game");

    // Set window size
    setFixedSize(600, 600);

    // Set up layout
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Add title label
    QLabel *titleLabel = new QLabel("Select mode", this);
    QFont titleFont("Arial", 30, QFont::Bold); // Set font and size for the title
    titleLabel->setFont(titleFont);
    titleLabel->setStyleSheet("color: orange;"); // Set text color to white
    titleLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter); // Align text to the top-left corner
    layout->addWidget(titleLabel);

    // Add 1 vs AI button
    button1vs1 = new QPushButton("1 VS AI", this);
    button1vs1->setStyleSheet("QPushButton { background-color: #FFA500; color: black; font-size: 14px; padding: 6px; }"); // Orange button style
    button1vs1->setMaximumWidth(200);
    connect(button1vs1, &QPushButton::clicked, this, &ConfirmationDialog::on_button1vs1_clicked);
    layout->addWidget(button1vs1);

    // Add 1 vs 1 button
    button1vsAI = new QPushButton("1 VS 1", this);
    button1vsAI->setStyleSheet("QPushButton { background-color: #FFA500; color: black; font-size: 14px; padding: 6px; }"); // Orange button style
    button1vsAI->setMaximumWidth(200);
    connect(button1vsAI, &QPushButton::clicked, this, &ConfirmationDialog::on_button1vsAI_clicked);
    layout->addWidget(button1vsAI);

    // Set layout
    setLayout(layout);

    // Set background image
    QPixmap bkgnd("E:\\2nd year 2nd term assignments\\tic_tac_toe_project\\qt_code\\tic-tac-toe-background1.jpg");
    if (!bkgnd.isNull()) {
        bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
        QPalette palette;
        palette.setBrush(QPalette::Window, bkgnd);
        this->setPalette(palette);
    }
}

void ConfirmationDialog::on_button1vs1_clicked() {
    emit gameModeSelected(0); // 1 vs 1 mode selected
}

void ConfirmationDialog::on_button1vsAI_clicked() {
    emit gameModeSelected(1); // 1 vs AI mode selected
}
