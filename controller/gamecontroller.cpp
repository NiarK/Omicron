#include "gamecontroller.h"

GameController::GameController(const std::vector<unsigned int> &sizeByDimension, bool infinite, unsigned int ghost) :
    _pacman(0),
    _ghosts(ghost, 0),
    _matrix(0),
    _pacmanOld(0),
    _ghostsOld(ghost, 0),
    _pacmanMoved(false),
    _movementCounter(0),
    _timePacmanIA(),
    _timeGhostIA(),
    _time(),
    _gameOver(false)
    //_vertexNumber(0)
{
    // Initialisation du random
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());

    _matrix = new HyperCube(sizeByDimension, infinite);

    this->reset();
    /*
    _pacman = this->generatePosition();
    for(unsigned int i = 0; i < ghost; ++i)
    {
        _ghosts.push_back(this->generatePosition());
        _ghostsOld.push_back(_ghosts.back());
    }
    //*/
    /*
    for(unsigned int y = 0; y < _matrix->size1(); ++y)
    {
        for(unsigned int x = 0; x < _matrix->size2(); ++x)
        {
            std::cout << (*_matrix)(y,x);
        }
        std::cout << std::endl;
    }
    //*/
}

GameController::~GameController()
{
    delete _matrix;
}


void GameController::reset()
{

    _pacman = this->generatePosition();
    _pacmanOld = _pacman;
    unsigned int ghost = _ghosts.size();
    for(unsigned int i = 0; i < ghost; ++i)
    {
        _ghosts[i] = this->generatePosition();
        _ghostsOld[i] =  _ghosts[i];
    }

    _pacmanMoved = false;
    _movementCounter = 0;

    _timePacmanIA.clear();
    _timeGhostIA.clear();

    _gameOver = false;
}

HyperCube *GameController::getAdjacencyMatrix()
{
    return _matrix;
}

std::vector<unsigned int> GameController::getEdges(unsigned int vertex) const
{
    if(vertex >= _matrix->size1())
    {
        throw std::bad_alloc();
    }

    unsigned int size = _matrix->size1();
    std::vector<unsigned int> edges;

    for( unsigned int i = 0; i < size; ++i )
    {
        if( (*_matrix)( vertex, i ) == 1 )
        {
            edges.push_back(i);
        }
    }

    return edges;
}

unsigned int GameController::getVertexNumber() const
{
    return _matrix->size1();

}

unsigned int GameController::generatePosition()
{
    // génération de la position aléatoire
    unsigned int high = this->getVertexNumber();
    //unsigned int low = 0;

    bool isSamePosition;
    unsigned int ghostNumber = _ghosts.size();

    unsigned int pos;

    do
    {
        isSamePosition = false;

        pos = qrand() % high;//((high + 1) - low) + low;

        if( pos == _pacman )
        {
            isSamePosition = true;
        }

        for( unsigned int i = 0; !isSamePosition && i < ghostNumber; ++i )
        {
            if( pos == _ghosts[i] )
            {
                isSamePosition = true;
            }
        }

    }while(isSamePosition);

    return pos;
}

unsigned int GameController::getPacman() const
{
    return _pacman;
}

std::vector<unsigned int> GameController::getGhost() const
{
    return _ghosts;
}


bool GameController::nextMove()
{
    //Actor a;
    bool isNothingWrong = false;

    if(!_pacmanMoved)
    {
        //_pacmanOld = _pacman;

        _time.restart();
        this->movePacman();
        _timePacmanIA.push_back(_time.elapsed());

        isNothingWrong = this->checkPacmanMoved();
        //a = Actor::PACMAN;
    }
    else
    {
        //_ghostsOld = _ghosts;

        _time.restart();
        this->moveGhost();
        _timeGhostIA.push_back(_time.elapsed());

        isNothingWrong = this->checkGhostMoved();

        ++_movementCounter;
        _gameOver = pacmanIsCatched();
        //a = Actor::GHOST;
    }

    _pacmanMoved = !_pacmanMoved;

    return isNothingWrong;
}

unsigned int GameController::getGhostMovementCounter() const
{
    return _movementCounter;
}

bool GameController::pacmanIsCatched()
{
    //TODO : ameliorer l'algo
    unsigned int ghostNumber = _ghosts.size();

    for(unsigned int i = 0; i < ghostNumber; ++i)
    {
        if( _ghosts[i] == _pacman )
        {
            return true;
        }
    }

    return false;
}


unsigned int GameController::getAveragePacmanIATime()
{
    unsigned int avg = 0;
    unsigned int sum = 0;
    unsigned int size = _timePacmanIA.size();

    if(size != 0)
    {
        for(unsigned int i = 0; i < size; ++i)
        {
            sum += _timePacmanIA[i];
        }

        avg = sum / size;
    }

    return avg;

}

unsigned int GameController::getAverageGhostIATime()
{
    unsigned int avg = 0;
    unsigned int sum = 0;
    unsigned int size = _timeGhostIA.size();

    if(size != 0)
    {
        for(unsigned int i = 0; i < size; ++i)
        {
            sum += _timeGhostIA[i];
        }

        avg = sum / size;
    }

    return avg;
}

bool GameController::checkPacmanMoved()
{
    bool movement = _pacman != _pacmanOld;

    _pacmanOld = _pacman;

    return movement;
}

bool GameController::checkGhostMoved()
{
    int movement = 0;
    unsigned int size = _ghosts.size();

    for( unsigned int i = 0; i < size; ++i)
    {
        if( _ghosts[i] == _ghostsOld[i] )
        {
            ++movement;
        }
    }

    _ghostsOld = _ghosts;

    return movement == 1;
}

void GameController::benchmark(unsigned int n)
{
    float avgMove = 0;
    for( unsigned int i = 0; i < n; ++i)
    {
        while( ! this->gameOver() )
        {
            this->nextMove();
        }

        avgMove += this->getGhostMovementCounter();

        this->reset();
    }

    avgMove /= n;

    std::cout << avgMove << std::endl;
}

bool GameController::gameOver() const
{
    return _gameOver;
}
