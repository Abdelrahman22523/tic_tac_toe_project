#include "history.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QHeaderView> // Include the QHeaderView header file

History::History(const QString &username, QWidget *parent) : QWidget(parent),
    currentUser(username), model(nullptr)
{

    // Load background image
    QPixmap bkgnd("E:\\2nd year 2nd term assignments\\tic_tac_toe_project\\qt_code\\tic-tac-toe-background1.jpg");
    if (bkgnd.isNull()) {
        qDebug() << "Failed to load background image.";
    } else {
        qDebug() << "Background image loaded successfully. Size:" << bkgnd.size();
        bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
        QPalette palette;
        palette.setBrush(QPalette::Window, bkgnd);
        this->setPalette(palette);
    }
    setWindowTitle("User History");
    setFixedSize(600, 600);

    // Set background color and text color for night mode
    setStyleSheet("background-color: #222; color: white;");

    layout = new QVBoxLayout(this);

    QLabel *titleLabel = new QLabel("User History", this);
    QFont titleFont("Arial", 30, QFont::Bold);
    titleLabel->setFont(titleFont);
    titleLabel->setStyleSheet("color: orange;");
    layout->addWidget(titleLabel);

    buttonback = new QPushButton("Back", this);
    buttonback->setStyleSheet("QPushButton { background-color: #FFA500; color: black; font-size: 14px; padding: 6px; }");
    buttonback->setMaximumWidth(200);
    connect(buttonback, &QPushButton::clicked, this, &History::back_clicked);
    layout->addWidget(buttonback);

    // Setup database connection and model/view
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(username + "_games_history.db");

    if (!db.open()) {
        QMessageBox::critical(this, "Database Error", db.lastError().text());
        return;
    }

    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS games (id INTEGER PRIMARY KEY, player1 TEXT, player2 TEXT, winner TEXT, board_state TEXT)");

    setupModelAndView();
    setLayout(layout);
}

void History::addGame(const QString &player1, const QString &player2, const QString &winner, const QString &boardState) {
    QSqlQuery query;
    query.prepare("INSERT INTO games (player1, player2, winner, board_state) VALUES (?, ?, ?, ?)");
    query.addBindValue(player1);
    query.addBindValue(player2);
    query.addBindValue(winner);
    query.addBindValue(boardState);

    if (!query.exec()) {
        QMessageBox::critical(this, "Database Error", query.lastError().text());
    } else {
        model->select(); // Refresh the model to reflect the new data
    }
}

void History::setupModelAndView() {
    model = new QSqlTableModel(this, db);
    model->setTable("games");
    model->select();

    view = new QTableView(this);
    view->setModel(model);
    view->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); // Set header resize mode

    // Set background and text color for the table view
    view->setStyleSheet("QTableView { background-color: #333; color: white; }"
                        "QHeaderView::section { background-color: #444; color: white; }"
                        "QTableView::item { selection-background-color: #555; }");

    layout->addWidget(view);
}

void History::back_clicked() {
    emit back();
    close();
}

History::~History() {
    if (db.isOpen()) {
        db.close();
    }
}
