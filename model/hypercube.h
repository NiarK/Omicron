#ifndef HYPERCUBE_H
#define HYPERCUBE_H

// --- Include std --- //
#include <vector>

// incluion de boost. Il y a un bug entre Qt et Boost -> moc n'arrive pas a parser Boost, comme il n'a de tte façon pas besoin de le faire, on l'en empeche
#ifndef Q_MOC_RUN
    #include <boost/numeric/ublas/matrix.hpp>
#endif

typedef boost::numeric::ublas::matrix<int> Matrix;

/**
 * @brief The HyperCube class permet de créer la matrice d'adjacence d'un hypercube de dimension variable et de taille variable par dimension.
 */
class HyperCube : public Matrix
{
public:
    //HyperCube(unsigned int size, unsigned int dimension = 2, bool infinite = false);

    /**
     * @brief HyperCube, constructeur de la classe.
     * @param sizeByDimension est un vector contenant la taille de l'hypercube pour chaque dimension.
     * @param infinite est un boolean permettant de spécifier si l'hypercube doit reboucler sur lui m.eme ou non.
     */
    HyperCube(const std::vector<unsigned int> & sizeByDimension, bool infinite);

    ~HyperCube();

    /**
     * @brief getDimension permet de récuperer le nombre de dimension.
     * @return le nombre de dimension.
     */
    unsigned int getDimension() const;

    /**
     * @brief range permet de calculer la distance entre 2 noeuds.
     * @param vertex1 est un sommet de l'hypercube.
     * @param vertex2 est un sommet de l'hypercube.
     * @return la distance a parcourir d'un noeud à l'autre.
     */
    virtual unsigned int range(unsigned int vertex1, unsigned int vertex2) const;

    /**
     * @brief rangeByDimension permet de calculer la distance entre 2 noeuds.
     * @param vertex1 est un sommet de l'hypercube.
     * @param vertex2 est un sommet de l'hypercube.
     * @return un vector contenant la distance a parcourir pour chaque dimension pour aller d'un noeud à l'autre.
     */
    std::vector<unsigned int> rangeByDimension(unsigned int vertex1, unsigned int vertex2) const;

private:
    /**
     * @brief calculateVertexNumber calcule le nombre de noeuds dans le graphe.
     * @param sizeByDimension est un vector contenant la taille de l'hypercube pour chaque dimension.
     * @return Le nombre de noeuds dans le graphe.
     */
    static unsigned int calculateVertexNumber(const std::vector<unsigned int> & sizeByDimension);

    std::vector<unsigned int> _sizeByDimension;
    std::vector<unsigned int> _vertexByDimension;
    bool _infinite;
};


#endif // HYPERCUBE_H
