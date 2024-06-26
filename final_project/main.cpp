#include <QApplication>
#include "playagaindialog.h"
#include "confirmationdialog.h"
#include "tictactoe1.h"
#include "tictactoe2.h"
#include "logindialog.h"
#include "menu.h"
#include "history.h"
#include "difficultydialog.h"
#include "performanceoptimizer.h"
#include "gameengine.h" // Assuming you have a GameEngine class

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Initialize performance optimizer
    PerformanceOptimizer optimizer;
    optimizer.optimize(); // Example: Perform optimizations

    bool loggedOut = false;

    do {
        LoginDialog loginDialog;
        if (loginDialog.exec() != QDialog::Accepted) {
            return 0; // Exit the application if the login is not accepted
        }

        QString username = loginDialog.getUsername(); // Assuming LoginDialog has getUsername() method

        Menu menu;
        ConfirmationDialog confirmDialog;
        TicTacToe1 game1;
        TicTacToe2 game2;
        History history(username); // Pass username to History constructor
        DifficultyDialog difficultyDialog;
        GameEngine gameEngine; // Initialize GameEngine

        auto handleGameEnd = [&](QWidget *gameWidget, const QString &winner) {
            PlayAgainDialog playAgainDialog;
            playAgainDialog.show();

            QObject::connect(&playAgainDialog, &PlayAgainDialog::Yes, [&]() {
                confirmDialog.show();
            });

            QObject::connect(&playAgainDialog, &PlayAgainDialog::No, [&]() {
                menu.show();
            });

            playAgainDialog.exec();

            QString player2 = "Player 2";
            QString boardState;

            if (gameWidget == &game1) {
                player2 = "AI";
                boardState = game1.getBoardState();
            } else if (gameWidget == &game2) {
                boardState = game2.getBoardState();
            }

            history.addGame(username, player2, winner, boardState); // Update History with board state
        };

        QObject::connect(&game1, &TicTacToe1::gameEnded, [&]() {
            QString winner = game1.getWinner();
            if (winner == "Player 1") {
                winner = username;
            }
            handleGameEnd(&game1, winner);
        });

        QObject::connect(&game2, &TicTacToe2::gameEnded, [&]() {
            QString winner = game2.getWinner();
            if (winner == "Player 1") {
                winner = username;
            }
            handleGameEnd(&game2, winner);
        });

        QObject::connect(&menu, &Menu::gameModeSelected, [&](int mode) {
            if (mode == 0) {
                confirmDialog.show();
            } else if (mode == 1) {
                history.show();
                QObject::connect(&history, &History::back, [&]() {
                    menu.show();
                });
            } else if (mode == 2) { // Log out
                loggedOut = true;
                menu.close(); // Close the menu
            }
        });

        QObject::connect(&confirmDialog, &ConfirmationDialog::gameModeSelected, [&](int mode) {
            if (mode == 0) {
                difficultyDialog.show();
            } else if (mode == 1) {
                game2.setWindowTitle("Tic Tac Toe (1 vs 1)");
                game2.resize(600, 600);
                game2.show();
            } else if (mode == 2) {
                menu.show();
            }
        });

        QObject::connect(&difficultyDialog, &DifficultyDialog::difficultySelected, [&](int difficulty) {
            game1.setDifficulty(difficulty);
            game1.startGame();
        });

        QObject::connect(&difficultyDialog, &DifficultyDialog::back, [&]() {
            confirmDialog.show();
        });

        menu.show();

        // Enter the event loop for the menu
        app.exec();

    } while (loggedOut);

    return 0;
}
