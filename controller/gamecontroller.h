#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

// --- Include Qt --- //
#include <QTime>

// --- Include std --- //
#include <vector>
#include <stdexcept>
#include <cmath>

// --- Include Omicron --- //
#include "model/hypercube.h"

/*
enum class Actor
{
    PACMAN,
    GHOST
};
//*/

/**
 * @brief The GameController class est le controller abstrait qui gère la logic du jeu. Il faut en hériter pour implementer les fonction de mouvement des personnages.
 */
class GameController
{
public:
    /**
     * @brief GameController est le constructeur de la classe.
     * @param sizeByDimension est un vector contenant la taille de l'hypercube pour chaque dimension.
     * @param infinite est un boolean permettant de spécifier si l'hypercube doit reboucler sur lui m.eme ou non.
     * @param ghost correspond au nombre de ghost sur la map.
     */
    GameController(const std::vector<unsigned int> & sizeByDimension, bool infinite, unsigned int ghost);
    virtual ~GameController();

    /**
     * @brief getEdges permet de récuperer un vector contenant la liste des noeuds liés a un noeud donné.
     * @param vertex est le numero d'un noeud
     * @return un vector contenant la liste des noeuds liés a un noeud donné.
     */
    virtual std::vector<unsigned int>   getEdges(unsigned int vertex)   const;

    /**
     * @brief getVertexNumber permet de recuperer le nombre de noeuds contenu dans le graphe.
     * @return le nombre de noeuds contenu dans le graphe.
     */
    virtual unsigned int getVertexNumber() const;

    /**
     * @brief getPacman récupère la position du pacman.
     * @return La position du pacman.
     */
    unsigned int getPacman() const;

    /**
     * @brief getGhost recupère la position des ghosts.
     * @return un vector contenant la position des ghosts.
     */
    std::vector<unsigned int> getGhost() const;

    /**
     * @brief getMovementCounter recupère le nombre de coup joué par les ghosts depuis le debut.
     * @return le nombre de coup joué par les ghosts.
     */
    unsigned int getGhostMovementCounter() const;

    /**
     * @brief nextMove permet de jouer le prochain coup.
     */
    bool nextMove();

    /**
     * @brief pacmanIsCatched permet de savoir si le pacman est attrapé par un ghost.
     * @return un boolean qui indique si le pacman a perdu.
     */
    bool pacmanIsCatched();

    /**
     * @brief getAveragePacmanIATime calcule le temps moyen d'execution de l'algo du pacman.
     * @return le temps moyen d'execution de l'algo du pacman.
     */
    unsigned int getAveragePacmanIATime();

    /**
     * @brief getAveragePacmanIATime calcule le temps moyen d'execution de l'algo des ghosts.
     * @return le temps moyen d'execution de l'algo des ghosts.
     */
    unsigned int getAverageGhostIATime();

    /**
     * @brief checkPacmanMoved verifie si le pacman a bien bougé pendant ce tour.
     * @return vrai si le pacman bouge.
     */
    bool checkPacmanMoved();

    /**
     * @brief checkPacmanMoved verifie si un ghost a bien bougé pendant ce tour.
     * @return vrai si un ghost bouge.
     */
    bool checkGhostMoved();

    /**
     * @brief benchmark lance n fois l'application et fais des stats
     * @param n est le nombre de fois qu'il faut lancer l'application
     */
    void benchmark(unsigned int n);

    /**
     * @brief gameOver permet de savoir si le jeu est fini.
     * @return un boolean, vrai si le jeu est fini.
     */
    bool gameOver() const;

    /**
     * @brief reset réinitialise le jeu.
     */
    virtual void reset();

protected:
    /**
     * @brief getAdjacencyMatrix recupère un pointeur sur la matrice d'adjacence du graphe.
     * @return Un pointeur sur la matrice d'adjacence du graphe.
     */
    HyperCube * getAdjacencyMatrix();

    unsigned int _pacman;
    std::vector<unsigned int> _ghosts;

    HyperCube * _matrix;

private:
    /**
     * @brief movePacman fait bouger le pacman. Cette fonction doit implement l'IA du pacman.
     */
    virtual void movePacman() = 0;

    /**
     * @brief moveGhost fait bouger un ghost. Cette fonction doit implement l'IA des ghosts.
     */
    virtual void moveGhost() = 0;

    /**
     * @brief generatePosition génère aléatoirement une position dans le graphe qui n'est pas déjà prise.
     * @return une position libre.
     */
    unsigned int generatePosition();

    unsigned int _pacmanOld;
    std::vector<unsigned int> _ghostsOld;

    bool _pacmanMoved;
    unsigned int _movementCounter;
    std::vector<unsigned int> _timePacmanIA;
    std::vector<unsigned int> _timeGhostIA;
    QTime _time;

    bool _gameOver;

    //unsigned int _vertexNumber;
};

#endif // GAMECONTROLLER_H
