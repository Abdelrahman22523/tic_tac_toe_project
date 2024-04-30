#include <QApplication>
#include "confirmationdialog.h"
#include "tictactoe1.h"
#include "tictactoe2.h"
#include "logindialog.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Create and show the login dialog
    LoginDialog loginDialog;
    if (loginDialog.exec() != QDialog::Accepted) {
        return 0; // If login is not accepted, exit the application
    }

    // If login is successful, proceed to game mode selection
    ConfirmationDialog confirmDialog;
    TicTacToe1 game1;
    TicTacToe2 game2;

    QObject::connect(&confirmDialog, &ConfirmationDialog::gameModeSelected, [&](int mode){
        if(mode == 0) {
            game1.setWindowTitle("Tic Tac Toe (1 vs AI)");
            game1.resize(300, 300);
            game1.show();
        } else if (mode == 1) {
            game2.setWindowTitle("Tic Tac Toe (1 vs 1)");
            game2.resize(300, 300);
            game2.show();
        }
    });

    confirmDialog.show();

    return app.exec();
}
