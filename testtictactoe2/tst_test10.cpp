#include <QCoreApplication>
#include <QtTest>
#include "../tictactoe2.h"

// تعريف وحدة اختبارية فرعية لـ TicTacToe2 لاختبار الوظائف المحمية
class TestableTicTacToe2 : public TicTacToe2 {
    Q_OBJECT

public:
    using TicTacToe2::TicTacToe2;

    void simulateCellClick(int row, int col) {
        cellClicked(row, col);
    }

protected:
    void cellClicked(int row, int col) override {
        TicTacToe2::cellClicked(row, col);
    }
};

class TicTacToe2Test : public QObject {
    Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();
    void testStartGame();
    void testCellClick();
    void testGetWinner();
    void testCheckDraw();

private:
    TestableTicTacToe2 *tictactoe2;
};

void TicTacToe2Test::initTestCase() {
    tictactoe2 = new TestableTicTacToe2;
}

void TicTacToe2Test::cleanupTestCase() {
    delete tictactoe2;
}

void TicTacToe2Test::testStartGame() {
    tictactoe2->resetGame();
    QCOMPARE(tictactoe2->getBoardState(), "   \n   \n   \n");
}

void TicTacToe2Test::testCellClick() {
    tictactoe2->resetGame();
    tictactoe2->simulateCellClick(0, 0);
    QCOMPARE(tictactoe2->buttons[0][0]->text(), QString('X'));
    QCOMPARE(tictactoe2->board[0][0], 'X');
}

void TicTacToe2Test::testGetWinner() {
    tictactoe2->resetGame();
    tictactoe2->board[0][0] = 'X';
    tictactoe2->board[0][1] = 'X';
    tictactoe2->board[0][2] = 'X';
    tictactoe2->gameOver = true;
    tictactoe2->outcome = 1;
    QCOMPARE(tictactoe2->getWinner(), QString("Player 1"));

    tictactoe2->resetGame();
    tictactoe2->board[0][0] = 'O';
    tictactoe2->board[0][1] = 'O';
    tictactoe2->board[0][2] = 'O';
    tictactoe2->gameOver = true;
    tictactoe2->outcome = 2;
    QCOMPARE(tictactoe2->getWinner(), QString("Player 2"));

    tictactoe2->resetGame();
    tictactoe2->board[0][0] = 'X';
    tictactoe2->board[0][1] = 'O';
    tictactoe2->board[0][2] = 'X';
    tictactoe2->board[1][0] = 'O';
    tictactoe2->board[1][1] = 'O';
    tictactoe2->board[1][2] = 'X';
    tictactoe2->board[2][0] = 'X';
    tictactoe2->board[2][1] = 'X';
    tictactoe2->board[2][2] = 'O';
    tictactoe2->gameOver = true;
    tictactoe2->outcome = 3;
    QCOMPARE(tictactoe2->getWinner(), QString("Draw"));
}

void TicTacToe2Test::testCheckDraw() {
    tictactoe2->resetGame();
    tictactoe2->board[0][0] = 'X';
    tictactoe2->board[0][1] = 'O';
    tictactoe2->board[0][2] = 'X';
    tictactoe2->board[1][0] = 'O';
    tictactoe2->board[1][1] = 'X';
    tictactoe2->board[1][2] = 'O';
    tictactoe2->board[2][0] = 'O';
    tictactoe2->board[2][1] = 'X';
    tictactoe2->board[2][2] = 'O';
    QVERIFY(tictactoe2->checkDraw());
}

QTEST_MAIN(TicTacToe2Test)

#include "tst_test10.moc"
