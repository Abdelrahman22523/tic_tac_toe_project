// gameengine.h

#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <QObject>
#include <QDebug>
#include "performanceoptimizer.h" // Include the performance optimizer header

class GameEngine : public QObject
{
    Q_OBJECT
public:
    explicit GameEngine(QObject *parent = nullptr);
    ~GameEngine();

signals:

public slots:
    void startGame();
    // Add other necessary slots and functions

private:
    PerformanceOptimizer *optimizer; // Declare an instance of the performance optimizer
    // Add other private members as needed
};

#endif // GAMEENGINE_H
