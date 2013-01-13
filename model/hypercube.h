#ifndef HYPERCUBE_H
#define HYPERCUBE_H

// --- Include std --- //
#include <vector>

// incluion de boost. Il y a un bug entre Qt et Boost -> moc n'arrive pas a parser Boost, comme il n'a de tte façon pas besoin de le faire, on l'en empeche
#ifndef Q_MOC_RUN
    #include <boost/numeric/ublas/matrix.hpp>
#endif

typedef boost::numeric::ublas::matrix<int> Matrix;

class HyperCube : public Matrix
{
public:
    //HyperCube(unsigned int size, unsigned int dimension = 2, bool infinite = false);
    HyperCube(const std::vector<unsigned int> & sizeByDimension, bool infinite);
    ~HyperCube();

    unsigned int getDimension() const;

    virtual unsigned int range(unsigned int vertex1, unsigned int vertex2) const;
    unsigned int rangeByDimension(unsigned int vertex1, unsigned int vertex2) const;

private:
    static unsigned int calculateVertexNumber(const std::vector<unsigned int> & sizeByDimension);

    std::vector<unsigned int> _sizeByDimension;
    std::vector<unsigned int> _vertexByDimension;
    bool _infinite;
};


#endif // HYPERCUBE_H
