#include "tictactoe1.h"
#include <limits>
#include <QMessageBox>
#include <QDebug>

TicTacToe1::TicTacToe1(QWidget *parent) : TicTacToe(parent) {
    resetGame();
}

void TicTacToe1::startGame() {
    askDifficulty();
}

void TicTacToe1::cellClicked(int row, int col) {
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
        if (currentPlayer == 'O') {
            qDebug() << "AI's turn to play.";
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

void TicTacToe1::askDifficulty() {
    startRealGame();
}

void TicTacToe1::setDifficulty(int difficulty) {
    selectedDifficulty = difficulty;
    qDebug() << "Difficulty selected:" << difficulty;
}

void TicTacToe1::startRealGame() {
    currentPlayer = 'X';
    gameOver = false;
    resize(600, 600);
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            board[i][j] = ' ';
            buttons[i][j]->setText("");
        }
    }
    show();
}

void TicTacToe1::makeAIMove() {
    qDebug() << "Making AI move.";
    int bestScore = -std::numeric_limits<int>::max();
    int bestRow = -1;
    int bestCol = -1;

    int depth;
    switch (selectedDifficulty) {
    case 1:
        depth = 1;
        break;
    case 2:
        depth = 3;
        break;
    case 3:
        depth = 6;
        break;
    }

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == ' ') {
                board[i][j] = 'O';
                int score = minimax(0, depth, false, -std::numeric_limits<int>::max(), std::numeric_limits<int>::max());
                board[i][j] = ' ';
                qDebug() << "AI considering move at (" << i << "," << j << ") with score" << score;

                if (score > bestScore) {
                    bestScore = score;
                    bestRow = i;
                    bestCol = j;
                }
            }
        }
    }

    if (bestRow != -1 && bestCol != -1) {
        qDebug() << "AI selects move at (" << bestRow << "," << bestCol << ") with score" << bestScore;
        board[bestRow][bestCol] = 'O';
        buttons[bestRow][bestCol]->setText("O");

        if (checkWin('O')) {
            QMessageBox::information(this, "Winner", "O wins!");
            gameOver = true;
            outcome = 2; // AI wins
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
            currentPlayer = 'X';
        }
    } else {
        qDebug() << "AI failed to find a valid move!";
    }
}

int TicTacToe1::minimax(int depth, int maxDepth, bool maximizingPlayer, int alpha, int beta) {
    if (checkWin('X')) {
        return -10 + depth;
    } else if (checkWin('O')) {
        return 10 - depth;
    } else if (checkDraw() || depth >= maxDepth) {
        return 0;
    }

    if (maximizingPlayer) {
        int bestScore = -std::numeric_limits<int>::max();
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'O';
                    int score = minimax(depth + 1, maxDepth, false, alpha, beta);
                    board[i][j] = ' ';
                    bestScore = std::max(bestScore, score);
                    alpha = std::max(alpha, score);
                    if (beta <= alpha) {
                        break;
                    }
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
                    int score = minimax(depth + 1, maxDepth, true, alpha, beta);
                    board[i][j] = ' ';
                    bestScore = std::min(bestScore, score);
                    beta = std::min(beta, score);
                    if (beta <= alpha) {
                        break;
                    }
                }
            }
        }
        return bestScore;
    }
}

QString TicTacToe1::getWinner() const {
    if (gameOver) {
        if (outcome == 1) {
            return "Player 1";
        } else if (outcome == 2) {
            return "AI";
        } else {
            return "Draw";
        }
    }
    return "";
}

QString TicTacToe1::getBoardState() const {
    QString state;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            state.append(board[i][j]);
        }
        state.append('\n');  // Add a newline character at the end of each row

    }
    return state;
}

QString TicTacToe1::boardStateToString() const {
    QString state;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            state.append(board[i][j]);
        }
        state.append('\n');  // Add a newline character at the end of each row

    }
    return state;
}
