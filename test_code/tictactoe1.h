#ifndef TICTACTOE1_H
#define TICTACTOE1_H

#include "tictactoe.h"
#include "difficultydialog.h"
#include <QMessageBox>
#include <QDebug>

class TicTacToe1 : public TicTacToe {
    Q_OBJECT

public:
    enum Difficulty { Easy, Medium, Hard };
    explicit TicTacToe1(QWidget *parent = nullptr);
    void setDifficulty(int difficulty);
    void startGame();
    QString getWinner() const;
    QString getBoardState() const;
    int selectedDifficulty;
    void startRealGame();
    bool checkWin(char player) override;
    int outcome; // This member variable will store the game outcome
    bool checkDraw() override;





protected:
    void cellClicked(int row, int col) override;

private slots:
    void askDifficulty();
    void makeAIMove();
    int minimax(int depth, int maxDepth, bool maximizingPlayer, int alpha, int beta);

signals:
    void gameEnded(int m);

private:
    DifficultyDialog *difficultyDialog;

    QString boardStateToString() const;
};

#endif // TICTACTOE1_H
