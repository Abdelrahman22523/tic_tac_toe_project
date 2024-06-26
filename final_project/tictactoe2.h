#ifndef TICTACTOE2_H
#define TICTACTOE2_H

#include "tictactoe.h"
#include "history.h" // Include the header for History
#include <QMessageBox>

class TicTacToe2 : public TicTacToe {
    Q_OBJECT

public:
    TicTacToe2(QWidget *parent = nullptr);
    QString getWinner() const;
    QString getBoardState() const;

signals:
    void gameEnded(int m);

protected:
    void cellClicked(int row, int col) override;
    bool checkWin(char player) override;
    bool checkDraw() override;

private:
    void saveCurrentBoardState();
    History *history; // Pointer to History instance
    int outcome; // This member variable will store the game outcome
};

#endif // TICTACTOE2_H
