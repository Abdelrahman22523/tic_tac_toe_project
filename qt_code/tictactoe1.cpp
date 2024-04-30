#include "tictactoe1.h"
#include <limits>
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QDebug>
#include <QMessageBox>
#include <QDialog>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <limits>
TicTacToe1::TicTacToe1(QWidget *parent) : TicTacToe(parent) {
    resetGame();
}

void TicTacToe1::cellClicked(int row, int col) {
    if (gameOver || board[row][col] != ' ') return;

    board[row][col] = currentPlayer;
    buttons[row][col]->setText(QString(currentPlayer));

    if (checkWin(currentPlayer)) {
        QMessageBox::information(this, "Winner", QString("%1 wins!").arg(currentPlayer));
        gameOver = true;
    } else if (checkDraw()) {
        QMessageBox::information(this, "Draw", "It's a draw!");
        gameOver = true;
    } else {
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        if (currentPlayer == 'O') {
            makeAIMove();
        }
    }
}

bool TicTacToe1::checkWin(char player) {
    for (int i = 0; i < 3; ++i) {
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
            (board[0][i] == player && board[1][i] == player && board[2][i] == player)) {
            return true;
        }
    }
    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[0][2] == player && board[1][1] == player && board[2][0] == player)) {
        return true;
    }
    return false;
}

bool TicTacToe1::checkDraw() {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == ' ') {
                return false;
            }
        }
    }
    return true;
}

void TicTacToe1::makeAIMove() {
    int bestScore = -std::numeric_limits<int>::max();
    int bestRow = -1;
    int bestCol = -1;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == ' ') {
                board[i][j] = 'O';
                int score = minimax(0, false);
                board[i][j] = ' ';

                if (score > bestScore) {
                    bestScore = score;
                    bestRow = i;
                    bestCol = j;
                }
            }
        }
    }

    if (bestRow != -1 && bestCol != -1) {
        cellClicked(bestRow, bestCol);
    }
}

int TicTacToe1::minimax(int depth, bool maximizingPlayer) {
    if (checkWin('X')) {
        return -10 + depth; // Human wins
    } else if (checkWin('O')) {
        return 10 - depth; // AI wins
    } else if (checkDraw()) {
        return 0; // Draw
    }

    if (maximizingPlayer) {
        int bestScore = -std::numeric_limits<int>::max();
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'O';
                    int score = minimax(depth + 1, false);
                    board[i][j] = ' ';
                    bestScore = std::max(bestScore, score);
                }
            }
        }
        return bestScore;
    } else {
        int bestScore = std::numeric_limits<int>::max();
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'X';
                    int score = minimax(depth + 1, true);
                    board[i][j] = ' ';
                    bestScore = std::min(bestScore, score);
                }
            }
        }
        return bestScore;
    }
}
