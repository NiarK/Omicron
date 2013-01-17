#ifndef BOARD_H
#define BOARD_H

// --- Include Omicron --- //
#include "controller/gamecontroller.h"

class BoardController : public GameController
{
public:
    BoardController(unsigned int width, unsigned int height);
    virtual ~BoardController();


    // --- Accessor --- //
    unsigned int getWidth();
    unsigned int getHeight();

protected:

private:
    /**
     * @brief movePacman Gère le mouvement du pacman
     */
    virtual void movePacman();
    /**
     * @brief moveGhost Gère le mouvement des ghosts
     */
    virtual void moveGhost();
    /**
     * @brief rangeMin Permet de calculer la distance entre la case et le gendarme le plus proche
     * @param value Contient la donnée pour sélectionner la case voulue par rapport au pacman (gauche : -1, droite : 1, haut : -w, bas : w)
     * @return distance minimale
     */
    virtual int rangeMin(int value);
    /**
     * @brief borderTest Test si la position est en bordure du plateau
     * @param pos Valeur de la position à tester
     * @return True si c'est un bord, false si ce n'en est pas un
     */
    virtual bool borderTest(int pos);
    /**
     * @brief range Permet d'obtenir la distance entre deux positions
     * @param pos1 Première position à tester
     * @param pos2 Seconde position à tester
     * @returnNombre de déplacement pour que la position 1 soit confondue avec la position 2
     */
    virtual int range(int pos1, int pos2);
    /**
     * @brief parityTest Test la "couleur" de la case de l'échequier
     * @param nb Position de la case à tester
     * @return True ou false en fonction de la couleur
     */
    virtual bool parityTest(int nb);
    /**
     * @brief calculateMovement Effectue le mouvement du ghost
     * @param nb Contient le numéro du ghost à déplacer
     */
    virtual void calculateMovement(unsigned int nb);
    /**
     * @brief reset remise à l'état initial du jeu
     */
    virtual void reset();
    /**
     * @brief randomPacman Permet de faire le déplacement aléatoire du pacman
     */
    virtual void randomPacman();
    std::vector<unsigned int> createSizeByDimensionVector(unsigned int width, unsigned int height);

    unsigned int _width;
    unsigned int _height;
    unsigned int _runner;
    bool _selected;
};

#endif // BOARD_H
