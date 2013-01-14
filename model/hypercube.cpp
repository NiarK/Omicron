#include "hypercube.h"


/*HyperCube::HyperCube(unsigned int size, unsigned int dimension, bool infinite) :
    //Matrix(std::pow(size, dimension), std::pow(size, dimension))
    HyperCube(std::vector<unsigned int>(dimension, size) ,infinite)
{

    unsigned int nbVertex = this->size1();

    for( unsigned int v = 0; v < nbVertex; ++v) // on parcours tous les sommets (toutes les lignes de la matrice d'adjacence) pour y ajouter ces liaisons
    {
        for( unsigned int d = 0; d < dimension; ++d) // parcours les dimensions car il y a 2 arcs a ajouter par dimension
        {
            unsigned int nbVertexByDimension = std::pow(size, d);       // nombre de noeud impliqué dans la dimension en cours
            unsigned int nbVertexByDimensionSup = std::pow(size, d+1);  // nombre de noeuds impliqué dans la dimension en cours + 1 -> permet de tester la liaison entre 2 noeuds se fait bien dans la dimension en cours.

            if( (int)( v % nbVertexByDimensionSup ) - (int)nbVertexByDimension >= 0) // gere les effets de bords inferieurs : s'assure que l'arc ne va pas lié un noeud avec un autre d'une dimension inferieure
            {
                (*this)( v, v - nbVertexByDimension) = 1; // ajout de l'arc inferieur
            }
            else if (infinite)
            {
                (*this)( v, v + (nbVertexByDimensionSup - nbVertexByDimension) ) = 1;
            }

            if( v % nbVertexByDimensionSup + nbVertexByDimension < nbVertexByDimensionSup) // gere les effets de bords superieurs : s'assure que l'arc ne va pas lié un noeud avec un autre d'une dimension supérieure
            {
                (*this)( v, v + nbVertexByDimension) = 1; // ajout de l'arc superieur
            }
            else if (infinite)
            {
                (*this)( v, v - (nbVertexByDimensionSup - nbVertexByDimension) ) = 1;
            }
        }
    }

}*/

HyperCube::HyperCube(const std::vector<unsigned int> & sizeByDimension, bool infinite) :
    Matrix(0,0),
    _sizeByDimension(sizeByDimension),
    _vertexByDimension(),
    _infinite(infinite)
{
    // --- Initialisation --- //
    // calcule le nombre de noeuds
    unsigned int vertex = HyperCube::calculateVertexNumber(sizeByDimension);

    this->resize(vertex,vertex);

    // Récupère le nombre de dimension
    unsigned int dimension = sizeByDimension.size();

    // Créer un tableau contenant le nombre de noeuds en jeu pour chaque dimension
    _vertexByDimension.push_back(1); // Dimension 0 -> 1 noeud
    for(unsigned int i = 0; i < dimension; ++i)
    {
        _vertexByDimension.push_back( _vertexByDimension[i] * sizeByDimension[i] );
    }

    // --- Algorithme --- //
    for( unsigned int v = 0; v < vertex; ++v) // on parcours tous les sommets (toutes les lignes de la matrice d'adjacence) pour y ajouter ses liaisons
    {
        // Initialisation de la matrice à 0
        unsigned int size = this->size2();
        for(unsigned int i = 0; i < size; ++i)
        {
            (*this)(v,i) = 0;
        }

        for( unsigned int d = 0; d < dimension; ++d) // parcours les dimensions car il y a 2 arcs (max) a ajouter par dimension
        {
            if( (int)( v % _vertexByDimension[d+1] ) - (int)_vertexByDimension[d] >= 0) // gere les effets de bords inferieurs : s'assure que l'arc ne va pas lié un noeud avec un autre d'une dimension inferieure
            {
                (*this)( v, v - _vertexByDimension[d]) = 1; // ajout de l'arc inferieur
            }
            else if (infinite) // Si la map doit reboucler sur elle meme
            {
                (*this)( v, v + (_vertexByDimension[d+1] - _vertexByDimension[d]) ) = 1; // On ajoute l'arc entre les noeuds correspondant
            }

            if( v % _vertexByDimension[d+1] + _vertexByDimension[d] < _vertexByDimension[d+1]) // gere les effets de bords superieurs : s'assure que l'arc ne va pas lié un noeud avec un autre d'une dimension supérieure
            {
                (*this)( v, v + _vertexByDimension[d]) = 1; // ajout de l'arc superieur
            }
            else if (infinite) // Si la map doit rebouvcler sur elle meme
            {
                (*this)( v, v - (_vertexByDimension[d+1] - _vertexByDimension[d]) ) = 1; // On ajoute l'arc entre les noeuds correspondant
            }
        }
    }

    /*
    for(unsigned int y = 0; y < this->size1(); ++y)
    {
        for(unsigned int x = 0; x < this->size2(); ++x)
        {
            std::cout << (*this)(y,x);
        }
        std::cout << std::endl;
    }
    //*/
}

HyperCube::~HyperCube()
{

}


unsigned int HyperCube::calculateVertexNumber(const std::vector<unsigned int> & sizeByDimension)
{
    unsigned int size = sizeByDimension.size();
    unsigned int vertex = 1;

    for(unsigned int i = 0; i < size; ++i)
    {
        vertex *= sizeByDimension[i];
    }

    return vertex;
}

/**
 * @brief HyperCube::range permet de calculer la distance entre 2
 * @param vertex1
 * @param vertex2
 * @return
 */
unsigned int HyperCube::range(unsigned int vertex1, unsigned int vertex2) const
{
    unsigned int dimension = this->getDimension();
    unsigned int v1 = vertex1;
    unsigned int v2 = vertex2;
    unsigned int range = 0;
    int rangeAdded = 0;

    for(int d = dimension - 1; d >= 0; --d)
    {
        rangeAdded = v1 / _vertexByDimension[d] - v2 / _vertexByDimension[d];

        if(rangeAdded < 0)
        {
            rangeAdded *= -1;
        }

        range += rangeAdded;

        v1 %= _vertexByDimension[d];
        v2 %= _vertexByDimension[d];
    }

    return range;
}

std::vector<unsigned int> HyperCube::rangeByDimension(unsigned int vertex1, unsigned int vertex2) const
{
    //TODO some stuff
    unsigned int dimension = this->getDimension();
    unsigned int v1 = vertex1;
    unsigned int v2 = vertex2;
    std::vector<unsigned int> range;
    int rangeAdded = 0;

    for(int d = dimension - 1; d >= 0; --d)
    {
        rangeAdded = v1 / _vertexByDimension[d] - v2 / _vertexByDimension[d];

        if(rangeAdded < 0)
        {
            rangeAdded *= -1;
        }

        range.push_back(rangeAdded);

        v1 %= _vertexByDimension[d];
        v2 %= _vertexByDimension[d];
    }

    return range;
}

unsigned int HyperCube::getDimension() const
{
    return _sizeByDimension.size();
}
