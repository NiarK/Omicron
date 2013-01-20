#include "benchmarkwidget.h"

BenchmarkWidget::BenchmarkWidget(const GameOption & option, QWidget *parent) :
    QWidget(parent),
    _option(option),
    _benchmark(0),
    _btnRestart(0),
    _btnReturn(0),
    _txtOccurenceNumber(0),
    _lblRandomCounterMinimum(0),
    _lblRandomCounterMaximum(0),
    _lblRandomCounterAverage(0),
    _lblWiseCounterMinimum(0),
    _lblWiseCounterMaximum(0),
    _lblWiseCounterAverage(0),
    _txtSummary(0),
    _progressBar(0)
{
    // Propriété du benchmark
    QIntValidator * validator = new QIntValidator(1,1000000,this);
    QLabel * lblOccurenceNumber = new QLabel("Nombre de partie : ", this);
    _txtOccurenceNumber = new QLineEdit(this);
    _txtOccurenceNumber->setText(QString::number(1000));
    _txtOccurenceNumber->setValidator(validator);
    _btnRestart = new QPushButton("Commencer", this);
    _btnReturn = new QPushButton("Retour", this);

    QHBoxLayout * lytProperty = new QHBoxLayout();
    lytProperty->addWidget(lblOccurenceNumber);
    lytProperty->addWidget(_txtOccurenceNumber);
    lytProperty->addStretch();
    lytProperty->addWidget(_btnRestart);
    lytProperty->addWidget(_btnReturn);
    // ! Propriété du benchmark

    // Tab
    // compteur de mouvement ia aleatoire
    QLabel * lblRandomSummary = new QLabel("IA aléatoire");
    QLabel * lblRandomMinimum = new QLabel("cout minimum : ");
    _lblRandomCounterMinimum = new QLabel("0");

    QLabel * lblRandomMaximum = new QLabel("maximum : ");
    _lblRandomCounterMaximum = new QLabel("0");

    QLabel * lblRandomAverage = new QLabel("moyenne : ");
    _lblRandomCounterAverage = new QLabel("0");

    QHBoxLayout * lytRandomMovementCounter = new QHBoxLayout();
    lytRandomMovementCounter->addWidget(lblRandomSummary);
    lytRandomMovementCounter->addStretch();
    lytRandomMovementCounter->addWidget(lblRandomMinimum);
    lytRandomMovementCounter->addWidget(_lblRandomCounterMinimum);
    lytRandomMovementCounter->addStretch();
    lytRandomMovementCounter->addWidget(lblRandomMaximum);
    lytRandomMovementCounter->addWidget(_lblRandomCounterMaximum);
    lytRandomMovementCounter->addStretch();
    lytRandomMovementCounter->addWidget(lblRandomAverage);
    lytRandomMovementCounter->addWidget(_lblRandomCounterAverage);
    //  ! compteur de mouvement ia aleatoire

    // compteur de mouvement ia intelligente
    QLabel * lblWiseSummary = new QLabel("IA sensé");
    QLabel * lblWiseMinimum = new QLabel("cout minimum : ");
    _lblWiseCounterMinimum = new QLabel("0");

    QLabel * lblWiseMaximum = new QLabel("maximum : ");
    _lblWiseCounterMaximum = new QLabel("0");

    QLabel * lblWiseAverage = new QLabel("moyenne : ");
    _lblWiseCounterAverage = new QLabel("0");

    QHBoxLayout * lytWiseMovementCounter = new QHBoxLayout();
    lytWiseMovementCounter->addWidget(lblWiseSummary);
    lytWiseMovementCounter->addStretch();
    lytWiseMovementCounter->addWidget(lblWiseMinimum);
    lytWiseMovementCounter->addWidget(_lblWiseCounterMinimum);
    lytWiseMovementCounter->addStretch();
    lytWiseMovementCounter->addWidget(lblWiseMaximum);
    lytWiseMovementCounter->addWidget(_lblWiseCounterMaximum);
    lytWiseMovementCounter->addStretch();
    lytWiseMovementCounter->addWidget(lblWiseAverage);
    lytWiseMovementCounter->addWidget(_lblWiseCounterAverage);
    //  ! compteur de mouvement ia intelligente


    _txtSummary = new QTextEdit(this);

    QVBoxLayout * lytSummary = new QVBoxLayout();
    lytSummary->addLayout(lytRandomMovementCounter);
    lytSummary->addLayout(lytWiseMovementCounter);
    lytSummary->addWidget(_txtSummary);

    QWidget * tabSummary = new QWidget(this);
    tabSummary->setLayout(lytSummary);

    //QTabWidget * tab = new QTabWidget(this);
    //tab->addTab(tabSummary, "Resumé");
    // ! tab

    // Bar de progression
    _progressBar = new QProgressBar(this);
    _progressBar->setRange(0, 100);
    // ! bar de progression

    QVBoxLayout * lytGbBenchmark = new QVBoxLayout();
    lytGbBenchmark->addLayout(lytProperty);
    //lytGbBenchmark->addWidget(tab);
    lytGbBenchmark->addWidget(tabSummary);
    lytGbBenchmark->addWidget(_progressBar);


    QGroupBox * gbBenchmark = new QGroupBox(this);
    gbBenchmark->setLayout(lytGbBenchmark);

    QHBoxLayout * layout = new QHBoxLayout(this);
    layout->addWidget(gbBenchmark);

    this->setLayout(layout);


    _benchmark = new Benchmark( _option );

    QObject::connect(_btnReturn, SIGNAL(clicked()), this, SLOT(emitTerminated()));
    QObject::connect(_btnRestart, SIGNAL(clicked()), this, SLOT(launchBenchmark()));

    QObject::connect(_benchmark, SIGNAL(minimumRandomMovementChanged(unsigned int)), this, SLOT(changeRandomMinimumMovement(unsigned int)));
    QObject::connect(_benchmark, SIGNAL(maximumRandomMovementChanged(unsigned int)), this, SLOT(changeRandomMaximumMovement(unsigned int)));
    QObject::connect(_benchmark, SIGNAL(averageRandomMovementChanged(float)), this, SLOT(changeRandomAverageMovement(float)));

    QObject::connect(_benchmark, SIGNAL(minimumWiseMovementChanged(unsigned int)), this, SLOT(changeWiseMinimumMovement(unsigned int)));
    QObject::connect(_benchmark, SIGNAL(maximumWiseMovementChanged(unsigned int)), this, SLOT(changeWiseMaximumMovement(unsigned int)));
    QObject::connect(_benchmark, SIGNAL(averageWiseMovementChanged(float)), this, SLOT(changeWiseAverageMovement(float)));

    QObject::connect(_benchmark, SIGNAL(currentCountNumberRandom(uint)), this, SLOT(updateSummaryRandom(uint)));
    QObject::connect(_benchmark, SIGNAL(currentCountNumberWise(uint)), this, SLOT(updateSummaryWise(uint)));

    QObject::connect(_benchmark, SIGNAL(progressionChanged(int)), _progressBar, SLOT(setValue(int)));

    QObject::connect(_benchmark, SIGNAL(finished()), this, SLOT(enabledProperty()));

    //QObject::connect(this, SIGNAL(terminated()), this, SLOT(launchBenchmark()));

}


void BenchmarkWidget::emitTerminated()
{
    emit terminated();
}

void BenchmarkWidget::launchBenchmark()
{
    _btnRestart->setEnabled(false);
    _btnReturn->setEnabled(false);
    _benchmark->run(_txtOccurenceNumber->text().toInt());
}



void BenchmarkWidget::changeRandomMinimumMovement(unsigned int min)
{
    _lblRandomCounterMinimum->setText(QString::number(min));
}

void BenchmarkWidget::changeRandomMaximumMovement(unsigned int max)
{
    _lblRandomCounterMaximum->setText(QString::number(max));
}

void BenchmarkWidget::changeRandomAverageMovement(float avg)
{
    _lblRandomCounterAverage->setText(QString::number(avg));
}



void BenchmarkWidget::changeWiseMinimumMovement(unsigned int min)
{
    _lblWiseCounterMinimum->setText(QString::number(min));
}

void BenchmarkWidget::changeWiseMaximumMovement(unsigned int max)
{
    _lblWiseCounterMaximum->setText(QString::number(max));
}

void BenchmarkWidget::changeWiseAverageMovement(float avg)
{
    _lblWiseCounterAverage->setText(QString::number(avg));
}



void BenchmarkWidget::updateSummaryRandom(unsigned int m)
{
    QString text("IA aléatoire \t\t Nombre de coups : ");
    text += QString::number(m);
    _txtSummary->append(text.toLatin1());
}

void BenchmarkWidget::updateSummaryWise(unsigned int m)
{
    QString text("IA avisé \t\t Nombre de coups : ");
    text += QString::number(m);
    _txtSummary->append(text);
}

void BenchmarkWidget::updateProgressBar(unsigned int n)
{
    _progressBar->setValue(n);
}

void BenchmarkWidget::enabledProperty()
{
    _btnRestart->setText("Recommencer");
    _btnRestart->setEnabled(true);
    _btnReturn->setEnabled(true);
}
