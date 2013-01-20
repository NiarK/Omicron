#ifndef BENCHMARKWIDGET_H
#define BENCHMARKWIDGET_H

// --- Qt --- //
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QProgressBar>
#include <QTabWidget>
#include <QTextEdit>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QIntValidator>

// --- Qt --- //
#include <QWidget>
#include <QLabel>

// --- Omicron --- //
#include "controller/benchmark.h"
#include "controller/boardcontroller.h"
#include "controller/cubecontroller.h"
#include "controller/tesseractcontroller.h"
#include "view/gameoption.h"

class BenchmarkWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BenchmarkWidget(const GameOption & option, QWidget *parent = 0);
    
signals:
    void terminated();
    
public slots:
    void emitTerminated();
    void changeRandomMinimumMovement(unsigned int min);
    void changeRandomMaximumMovement(unsigned int max);
    void changeRandomAverageMovement(float avg);

    void changeWiseMinimumMovement(unsigned int min);
    void changeWiseMaximumMovement(unsigned int max);
    void changeWiseAverageMovement(float avg);

    void updateSummaryRandom(unsigned int m);
    void updateSummaryWise(unsigned int m);

    void updateProgressBar(unsigned int n);
    void launchBenchmark();

    void enabledProperty();

private:
    const GameOption & _option;

    Benchmark * _benchmark;

    QPushButton * _btnRestart;
    QPushButton * _btnReturn;
    QLineEdit * _txtOccurenceNumber;

    QLabel * _lblRandomCounterMinimum;
    QLabel * _lblRandomCounterMaximum;
    QLabel * _lblRandomCounterAverage;

    QLabel * _lblWiseCounterMinimum;
    QLabel * _lblWiseCounterMaximum;
    QLabel * _lblWiseCounterAverage;

    QTextEdit * _txtSummary;

    QProgressBar * _progressBar;
    
};

#endif // BENCHMARKWIDGET_H
