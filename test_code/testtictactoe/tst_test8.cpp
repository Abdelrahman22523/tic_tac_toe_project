#include <QCoreApplication>
#include <QtTest>
#include <QMessageBox>
#include <QPushButton>

#include "../tictactoe.h"

class TestableTicTacToe : public TicTacToe {
    Q_OBJECT

public:
    using TicTacToe::TicTacToe;

    void simulateCellClick(int row, int col) {
        cellClicked(row, col);
    }

protected:
    void cellClicked(int row, int col) override {
        if (!gameOver && board[row][col] == ' ') {
            board[row][col] = currentPlayer;
            buttons[row][col]->setText(QString(currentPlayer));

            if (checkWin(currentPlayer)) {
                gameOver = true;
                QMessageBox::information(this, "Game Over", QString("%1 wins!").arg(currentPlayer));
            } else if (checkDraw()) {
                gameOver = true;
                QMessageBox::information(this, "Game Over", "It's a draw!");
            } else {
                currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
            }
        }
    }

    bool checkWin(char player) override {
        // This is a stub implementation for testing purposes
        return false;
    }

    bool checkDraw() override {
        // This is a stub implementation for testing purposes
        return false;
    }
};

class TicTacToeTest : public QObject {
    Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();
    void testResetGame();
    void testSetGetBoardState();
    void testCellClick();

private:
    TestableTicTacToe *tictactoe;
};

void TicTacToeTest::initTestCase() {
    tictactoe = new TestableTicTacToe;
}

void TicTacToeTest::cleanupTestCase() {
    delete tictactoe;
}

void TicTacToeTest::testResetGame() {
    tictactoe->resetGame();
    QString emptyBoard = "   \n   \n   \n";
    QCOMPARE(tictactoe->getBoardState(), emptyBoard);
}

void TicTacToeTest::testSetGetBoardState() {
    QString boardState = "XOX\nOXO\nXOX\n";
    tictactoe->setBoardState(boardState);
    QCOMPARE(tictactoe->getBoardState(), boardState);
}

void TicTacToeTest::testCellClick() {
    tictactoe->resetGame();
    tictactoe->simulateCellClick(0, 0);
    QCOMPARE(tictactoe->buttons[0][0]->text(), QString('X'));
    QCOMPARE(tictactoe->board[0][0], 'X');
}

QTEST_MAIN(TicTacToeTest)


#include "tst_test8.moc"
