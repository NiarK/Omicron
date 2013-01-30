#include "benchmark.h"

Benchmark::Benchmark(const GameOption &option, QObject * parent) :
    QObject(parent),
    _option(option),
    _game(0)
{
    //this->initializeGame();
}

void Benchmark::initializeGame()
{
    if(_game)
    {
        delete _game;
        _game = 0;
    }

    switch(_option.getField())
    {
    case Field::BOARD:
        _game = new BoardController(_option.getWidth(), _option.getHeight());
        break;
    case Field::CUBE:
        _game = new CubeController();
        break;
    case Field::TESSERACT:
        _game = new TesseractController();
        break;
    case Field::DONUT:
        _game = new DonutController();
        break;
    }
}

void Benchmark::run(unsigned int n)
{
    this->initializeGame();

    unsigned int currentMove = 0;
    unsigned int maxMove = 0;
    unsigned int minMove = 0;
    float avgMove = 0;

    _game->setPacmanAI(PacmanAI::RANDOM);

    for(unsigned int i = 0; i < n; ++i)
    {
        while( ! _game->gameOver() )
        {
            _game->nextMove();
        }

        currentMove = _game->getGhostMovementCounter();

        if( currentMove > maxMove )
        {
            maxMove = currentMove;
            //emit maximumRandomMovementChanged(maxMove);
        }
        if( currentMove < minMove || minMove == 0 )
        {
            minMove = currentMove;
            //emit minimumRandomMovementChanged(minMove);
        }

        emit currentCountNumberRandom(currentMove);

        avgMove += currentMove;
        //emit averageRandomMovementChanged(avgMove/(i+1));

        _game->reset();

        emit progressionChanged( (i * 100) / (n*2) );
    }

    avgMove /= n;
    emit minimumRandomMovementChanged(minMove);
    emit maximumRandomMovementChanged(maxMove);
    emit averageRandomMovementChanged(avgMove);

    maxMove = 0;
    minMove = 0;
    avgMove = 0;

    _game->setPacmanAI(PacmanAI::WISE);
    for(unsigned int i = 0; i < n; ++i)
    {
        while( ! _game->gameOver() )
        {
            _game->nextMove();
        }

        currentMove = _game->getGhostMovementCounter();

        if( currentMove > maxMove )
        {
            maxMove = currentMove;
            //emit maximumWiseMovementChanged(maxMove);
        }
        if( currentMove < minMove || minMove == 0 )
        {
            minMove = currentMove;
            //emit minimumWiseMovementChanged(minMove);
        }

        emit currentCountNumberWise(currentMove);

        avgMove += currentMove;
        //emit averageWiseMovementChanged(avgMove/(i+1));

        _game->reset();

        emit progressionChanged( ( (i+n) * 100 ) / (n*2) );
    }

    avgMove /= n;

    emit progressionChanged( ( 2 * n * 100 ) / (n*2) );

    emit minimumWiseMovementChanged(minMove);
    emit maximumWiseMovementChanged(maxMove);
    emit averageWiseMovementChanged(avgMove);

    emit finished();
}











