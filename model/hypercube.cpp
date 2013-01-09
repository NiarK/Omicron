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
    Matrix(0,0)
{
    // --- Initialisation --- //
    // calcule le nombre de noeuds
    unsigned int vertex = HyperCube::calculateVertexNumber(sizeByDimension);

    this->resize(vertex,vertex);

    // Récupère le nombre de dimension
    unsigned int dimension = sizeByDimension.size();

    // Créer un tableau contenant le nombre de noeuds en jeu pour chaque dimension
    std::vector<unsigned int> vertexByDimension;
    vertexByDimension.push_back(1); // Dimension 0 -> 1 noeud
    for(unsigned int i = 0; i < dimension; ++i)
    {
        vertexByDimension.push_back( vertexByDimension[i] * sizeByDimension[i] );
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
            if( (int)( v % vertexByDimension[d+1] ) - (int)vertexByDimension[d] >= 0) // gere les effets de bords inferieurs : s'assure que l'arc ne va pas lié un noeud avec un autre d'une dimension inferieure
            {
                (*this)( v, v - vertexByDimension[d]) = 1; // ajout de l'arc inferieur
            }
            else if (infinite) // Si la map doit reboucler sur elle meme
            {
                (*this)( v, v + (vertexByDimension[d+1] - vertexByDimension[d]) ) = 1; // On ajoute l'arc entre les noeuds correspondant
            }

            if( v % vertexByDimension[d+1] + vertexByDimension[d] < vertexByDimension[d+1]) // gere les effets de bords superieurs : s'assure que l'arc ne va pas lié un noeud avec un autre d'une dimension supérieure
            {
                (*this)( v, v + vertexByDimension[d]) = 1; // ajout de l'arc superieur
            }
            else if (infinite) // Si la map doit rebouvcler sur elle meme
            {
                (*this)( v, v - (vertexByDimension[d+1] - vertexByDimension[d]) ) = 1; // On ajoute l'arc entre les noeuds correspondant
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

