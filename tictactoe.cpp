#include "tictactoe.h"
#include <QMessageBox>
#include <QDebug>

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

QString TicTacToe::getBoardState() const {
    QString state;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            state.append(board[i][j]);
        }
        state.append('\n');  // Add a newline character at the end of each row
    }
    return state;
}

void TicTacToe::setBoardState(const QString &boardState) {
    int index = 0;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            board[i][j] = boardState[index].toLatin1();
            buttons[i][j]->setText(board[i][j] == ' ' ? "" : QString(board[i][j]));
            index++;
        }
        index++;  // Skip the newline character
    }
}

