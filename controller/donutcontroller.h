#ifndef DONUTCONTROLLER_H
#define DONUTCONTROLLER_H

// --- std --- //
#include <cmath>

// --- Omicron --- //
#include "controller/gamecontroller.h"

class DonutController : public GameController
{
public:
    DonutController();
    virtual ~DonutController();

    /**
     * @brief range Calcule la distance entre 2 sommets.
     * @param v1 sommet 1
     * @param v2 sommet 2
     * @return Distance entre sommet 1 et 2.
     */
    virtual unsigned int range(unsigned int v1, unsigned int v2);

    /**
     * @brief reset réinitialise le jeu.
     */
    virtual void reset();

private:

    /**
     * @brief diagonalTest test si la case passée en paramètre est dans la diagonale (sans case entre) du pacman
     * @param place numéro case à tester
     * @return vrai si c'est dans la case en diagonale
     */
    bool isInPacmanDiagonal(unsigned int vertex);

    /**
     * @brief pivot Retourne l'index du ghost qui est le plus indiqué pour calculez la position optimale des ghosts dans la map.
     * @return L'index d'un ghost.
     */
    unsigned int pivot();

    /**
     * @brief movePacman Gère le mouvement du pacman.
     */
    virtual void movePacman();

    /**
     * @brief moveGhost Gère les mouvement des ghosts.
     */
    virtual void moveGhost();

    unsigned int _width;
    unsigned int _height;

    /**
     * @brief _chase Si les ghosts ne chassent pas, ils doivent se mettre en position optimale.
     */
    bool _chase;

    /**
     * @brief _pivot Tableau contenant les positions optimales
     */
    std::vector<unsigned int> _optimumPosition;

    /**
     * @brief _ghostPlaced Nombre de ghosts placé en position optimale.
     */
    unsigned int _ghostPlaced;

    /**
     * @brief _ghostPositionTable Table de correspondance entre les ghosts et leur position optimale.
     */
    std::vector<unsigned int> _ghostPositionTable;

    /**
     * @brief _lastPlayed Index du dernier ghost ayant joué.
     */
    unsigned int _lastPlayed;
};

#endif // DONUTCONTROLLER_H
