#include <QCoreApplication>
#include <QtTest>
#include "../tictactoe1.h"


// تعريف وحدة اختبارية فرعية لـ TicTacToe1 لاختبار الوظائف المحمية
class TestableTicTacToe1 : public TicTacToe1 {
    Q_OBJECT

public:
    using TicTacToe1::TicTacToe1;

    void simulateCellClick(int row, int col) {
        cellClicked(row, col);
    }

protected:
    void cellClicked(int row, int col) override {
        TicTacToe1::cellClicked(row, col);
    }
};

class TicTacToe1Test : public QObject {
    Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();
    void testStartGame();
    void testSetDifficulty();
    void testCellClick();
    void testAIMove();
    void testGetWinner();

private:
    TestableTicTacToe1 *tictactoe1;
};

void TicTacToe1Test::initTestCase() {
    tictactoe1 = new TestableTicTacToe1;
}

void TicTacToe1Test::cleanupTestCase() {
    delete tictactoe1;
}

void TicTacToe1Test::testStartGame() {
    tictactoe1->startGame();
    QCOMPARE(tictactoe1->getBoardState(), "   \n   \n   \n");
}

void TicTacToe1Test::testSetDifficulty() {
    tictactoe1->setDifficulty(TicTacToe1::Easy);
    QCOMPARE(tictactoe1->selectedDifficulty, TicTacToe1::Easy);

    tictactoe1->setDifficulty(TicTacToe1::Medium);
    QCOMPARE(tictactoe1->selectedDifficulty, TicTacToe1::Medium);

    tictactoe1->setDifficulty(TicTacToe1::Hard);
    QCOMPARE(tictactoe1->selectedDifficulty, TicTacToe1::Hard);
}

void TicTacToe1Test::testCellClick() {
    tictactoe1->startRealGame();
    tictactoe1->simulateCellClick(0, 0);
    QCOMPARE(tictactoe1->buttons[0][0]->text(), QString('X'));
    QCOMPARE(tictactoe1->board[0][0], 'X');
}

void TicTacToe1Test::testAIMove() {
    tictactoe1->setDifficulty(TicTacToe1::Easy);
    tictactoe1->startRealGame();
    tictactoe1->simulateCellClick(0, 0);  // Player X's move

    // Check if AI (O) made a move
    bool aiMoved = false;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (tictactoe1->board[i][j] == 'O') {
                aiMoved = true;
                break;
            }
        }
    }
    QVERIFY(aiMoved);
}

void TicTacToe1Test::testGetWinner() {
    tictactoe1->startRealGame();

    tictactoe1->board[0][0] = 'X';
    tictactoe1->board[0][1] = 'X';
    tictactoe1->board[0][2] = 'X';
    tictactoe1->gameOver = true;
    tictactoe1->outcome = 1;
    QCOMPARE(tictactoe1->getWinner(), QString("Player 1"));

    tictactoe1->resetGame();
    tictactoe1->board[0][0] = 'O';
    tictactoe1->board[0][1] = 'O';
    tictactoe1->board[0][2] = 'O';
    tictactoe1->gameOver = true;
    tictactoe1->outcome = 2;
    QCOMPARE(tictactoe1->getWinner(), QString("AI"));

    tictactoe1->resetGame();
    tictactoe1->board[0][0] = 'X';
    tictactoe1->board[0][1] = 'O';
    tictactoe1->board[0][2] = 'X';
    tictactoe1->board[1][0] = 'O';
    tictactoe1->board[1][1] = 'O';
    tictactoe1->board[1][2] = 'X';
    tictactoe1->board[2][0] = 'X';
    tictactoe1->board[2][1] = 'X';
    tictactoe1->board[2][2] = 'O';
    tictactoe1->gameOver = true;
    tictactoe1->outcome = 3;
    QCOMPARE(tictactoe1->getWinner(), QString("Draw"));
}

QTEST_MAIN(TicTacToe1Test)


#include "tst_test9.moc"
