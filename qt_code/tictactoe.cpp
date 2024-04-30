#include "tictactoe.h"
#include <QMessageBox>

TicTacToe::TicTacToe(QWidget *parent) : QWidget(parent), currentPlayer('X'), gameOver(false) {
    QGridLayout *layout = new QGridLayout(this);

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            buttons[i][j] = new QPushButton("", this);
            buttons[i][j]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            buttons[i][j]->setFont(QFont("Arial", 24));
            layout->addWidget(buttons[i][j], i, j);

            connect(buttons[i][j], &QPushButton::clicked, [this, i, j]() {
                cellClicked(i, j);
            });
        }
    }

    setLayout(layout);
    resetGame();
}

void TicTacToe::resetGame() {
    currentPlayer = 'X';
    gameOver = false;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            buttons[i][j]->setText("");
            board[i][j] = ' ';
        }
    }
}
