#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

// --- Include Qt --- //
#include <QTime>

// --- Include std --- //
#include <vector>
#include <stdexcept>

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
    unsigned int getMovementCounter() const;

    /**
     * @brief nextMove permet de jouer le prochain coup.
     */
    void nextMove();

protected:
    /**
     * @brief getAdjacencyMatrix recupère un pointeur sur la matrice d'adjacence du graphe.
     * @return Un pointeur sur la matrice d'adjacence du graphe.
     */
    HyperCube * getAdjacencyMatrix();

    unsigned int _pacman;
    std::vector<unsigned int> _ghosts;

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

    bool _pacmanMoved;
    unsigned int _movementCounter;

    HyperCube * _matrix;
    //unsigned int _vertexNumber;
};

#endif // GAMECONTROLLER_H
