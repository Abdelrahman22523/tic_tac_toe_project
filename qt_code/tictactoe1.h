#ifndef TICTACTOE1_H
#define TICTACTOE1_H

#include "tictactoe.h"

class TicTacToe1 : public TicTacToe {
    Q_OBJECT

public:
    TicTacToe1(QWidget *parent = nullptr);

protected:
    void cellClicked(int row, int col) override;
    bool checkWin(char player) override;
    bool checkDraw() override;

private:
    void makeAIMove();
    int minimax(int depth, bool maximizingPlayer);
};

#endif // TICTACTOE1_H
