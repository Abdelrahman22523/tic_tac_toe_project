#include "tictactoe2.h"
#include <QMessageBox>

TicTacToe2::TicTacToe2(QWidget *parent) : TicTacToe(parent) {
    resetGame();
}

void TicTacToe2::cellClicked(int row, int col) {
    if (gameOver || board[row][col] != ' ') return;

    board[row][col] = currentPlayer;
    buttons[row][col]->setText(QString(currentPlayer));

    if (checkWin(currentPlayer)) {
        QMessageBox::information(this, "Winner", QString("%1 wins!").arg(currentPlayer));
        gameOver = true;
        outcome = (currentPlayer == 'X') ? 1 : 2; // Set outcome based on current player
        emit gameEnded(outcome);
        resetGame();
        close();
    } else if (checkDraw()) {
        QMessageBox::information(this, "Draw", "It's a draw!");
        gameOver = true;
        outcome = 3; // Draw
        emit gameEnded(outcome);
        resetGame();
        close();
    } else {
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }
}

bool TicTacToe2::checkWin(char player) {
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

bool TicTacToe2::checkDraw() {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == ' ') {
                return false;
            }
        }
    }
    return true;
}

QString TicTacToe2::getWinner() const {
    if (gameOver) {
        if (outcome == 1) {
            return "Player 1";
        } else if (outcome == 2) {
            return "Player 2";
        } else {
            return "Draw";
        }
    }
    return "";
}



QString TicTacToe2::getBoardState() const {
    QString state;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            state.append(board[i][j]);
        }
        state.append('\n');  // Add a newline character at the end of each row

    }
    return state;
}

