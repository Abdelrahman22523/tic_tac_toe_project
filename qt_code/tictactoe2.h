#ifndef TICTACTOE2_H
#define TICTACTOE2_H

#include "tictactoe.h"

class TicTacToe2 : public TicTacToe {
    Q_OBJECT

public:
    TicTacToe2(QWidget *parent = nullptr);

protected:
    void cellClicked(int row, int col) override;
    bool checkWin(char player) override;
    bool checkDraw() override;
};

#endif // TICTACTOE2_H
