#include <QApplication>
#include "confirmationdialog.h"
#include "tictactoe1.h"
#include "tictactoe2.h"
#include "logindialog.h"
#include "menu.h" // Include the menu header file

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Create and show the login dialog
    LoginDialog loginDialog;
    if (loginDialog.exec() != QDialog::Accepted) {
        return 0; // If login is not accepted, exit the application
    }

    // If login is successful, proceed to menu selection
    Menu menu;
    ConfirmationDialog confirmDialog;
    TicTacToe1 game1;
    TicTacToe2 game2;

    QObject::connect(&menu, &Menu::gameModeSelected, [&](int mode){
        // After selecting a mode in the menu, show the confirmation dialog
        confirmDialog.show();
        QObject::connect(&confirmDialog, &ConfirmationDialog::gameModeSelected, [&](int mode){
            if(mode == 0) {
                game1.setWindowTitle("Tic Tac Toe (1 vs AI)");
                game1.resize(600, 600);
                game1.show();
            } else if (mode == 1) {
                game2.setWindowTitle("Tic Tac Toe (1 vs 1)");
                game2.resize(600, 600);
                game2.show();
            }
        });
    });

    menu.show();

    return app.exec();
}
