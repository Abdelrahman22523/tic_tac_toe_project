#include "confirmationdialog.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QPalette>

ConfirmationDialog::ConfirmationDialog(QWidget *parent)
    : QDialog(parent)
{

    // Set window title
    setWindowTitle("Start Game");

    // Set window size
    setFixedSize(600, 600);

    // Set up layout
    layout = new QVBoxLayout(this);

    // Add title label
    QLabel *titleLabel = new QLabel("Select mode", this);
    QFont titleFont("Arial", 30, QFont::Bold);
    titleLabel->setFont(titleFont);
    titleLabel->setStyleSheet("color: orange;");
    titleLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    layout->addWidget(titleLabel);

    // Add 1 vs AI button
    button1vsAI = new QPushButton("1 VS 1", this);
    button1vsAI->setObjectName("button1vsAI"); // Object name assignment
    button1vsAI->setStyleSheet("QPushButton { background-color: #FFA500; color: black; font-size: 14px; padding: 6px; }");
    button1vsAI->setMaximumWidth(200);
    connect(button1vsAI, &QPushButton::clicked, this, &ConfirmationDialog::on_button1vsAI_clicked);
    layout->addWidget(button1vsAI);

    // Add 1 vs 1 button
    button1vs1 = new QPushButton("1 VS AI", this);
    button1vs1->setObjectName("button1vs1"); // Object name assignment
    button1vs1->setStyleSheet("QPushButton { background-color: #FFA500; color: black; font-size: 14px; padding: 6px; }");
    button1vs1->setMaximumWidth(200);
    connect(button1vs1, &QPushButton::clicked, this, &ConfirmationDialog::on_button1vs1_clicked);
    layout->addWidget(button1vs1);

    // Add back button
    buttonBack = new QPushButton("Back", this);
    buttonBack->setObjectName("buttonBack"); // Object name assignment
    buttonBack->setStyleSheet("QPushButton { background-color: #FFA500; color: black; font-size: 14px; padding: 6px; }");
    buttonBack->setMaximumWidth(200);
    connect(buttonBack, &QPushButton::clicked, this, &ConfirmationDialog::on_buttonBack_clicked);
    layout->addWidget(buttonBack);

    // Set layout
    setLayout(layout);

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
}

void ConfirmationDialog::on_button1vs1_clicked()
{
    emit gameModeSelected(0); // 1 vs 1 mode selected
    close();
}

void ConfirmationDialog::on_button1vsAI_clicked()
{
    emit gameModeSelected(1); // 1 vs AI mode selected
    close();
}

void ConfirmationDialog::on_buttonBack_clicked()
{
    emit gameModeSelected(2); // Back mode selected
    close();
}
