#ifndef BENCHMARK_H
#define BENCHMARK_H

// --- Qt --- //
#include <QObject>

// --- Omicron --- //
#include "controller/gamecontroller.h"
#include "controller/boardcontroller.h"
#include "controller/cubecontroller.h"
#include "controller/tesseractcontroller.h"
#include "view/option.h"
#include "view/gameoption.h"

class Benchmark : public QObject
{
    Q_OBJECT
public:
    explicit Benchmark(const GameOption & option, QObject *parent = 0);

    void initializeGame();

    void run(unsigned int n);
    
signals:
    void currentCountNumberRandom(unsigned int m);
    void currentCountNumberWise(unsigned int m);

    void averageWiseMovementChanged(float avg);
    void averageRandomMovementChanged(float avg);

    void minimumWiseMovementChanged(unsigned int min);
    void minimumRandomMovementChanged(unsigned int min);

    void maximumWiseMovementChanged(unsigned int max);
    void maximumRandomMovementChanged(unsigned int max);

    void progressionChanged(int n);
    void finished();

    
public slots:

private:
    const GameOption & _option;
    GameController * _game;
};

#endif // BENCHMARK_H
