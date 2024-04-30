#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>

class TicTacToe : public QWidget {
    Q_OBJECT

public:
    TicTacToe(QWidget *parent = nullptr);
    virtual ~TicTacToe() = default;

protected:
    QPushButton *buttons[3][3];
    char board[3][3];
    char currentPlayer;
    bool gameOver;

    virtual void cellClicked(int row, int col) = 0;
    virtual bool checkWin(char player) = 0;
    virtual bool checkDraw() = 0;
    void resetGame();
};

#endif // TICTACTOE_H
