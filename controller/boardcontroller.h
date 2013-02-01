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
     * @brief calculateEsperance additionne les variables passées en paramètre et test la parité pour renvoyer l'espérance correcte
     * @param vertical distance en vertical
     * @param horizontal distance en horizontal
     * @param numGhost numéro du ghost qu'on test
     * @return l'espérance avec la parité prise en compte
     */
    unsigned int calculateEsperance(int vertical, int horizontal, int numGhost);
    /**
     * @brief abs calcule la valeur absolue
     * @param nb nombre à passer en absolu
     * @return nb en absolu
     */
    unsigned int abs(int nb);
    /**
     * @brief bestDiagonalGhost choisi le ghost le plus dans la diagonale
     * @return numéro du ghost le plus dans la diagonale
     */
    unsigned int bestDiagonalGhost();
    /**
     * @brief lookEsperance permet d'avoir les deux espérances par rapport à la position du pacman
     * @param ghostNumber numéro du fantom
     * @return un tableau avec les deux espérances
     */
    std::vector<int> lookEsperance(unsigned int ghostNumber);
    /**
     * @brief esperance sert à calculer l'espérance vers un lieu
     * @param place lieu vers lequel on veut calculer l'espérance
     * @param GhostNumber numéro du ghost qu'on test
     * @return renvoi l'espérance
     */
    unsigned int esperance(int place, unsigned int GhostNumber);
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
     * @brief createSizeByDimensionVector Créer un vector contenant la taille pour un hypercube de dimension 2 pour chaque dimension.
     * @param width Largeur de la map.
     * @param height Hauteur de la map.
     * @return Un vector de 2 cases.
     */
    std::vector<unsigned int> createSizeByDimensionVector(unsigned int width, unsigned int height);

    unsigned int _width;
    unsigned int _height;

    /**
     * @brief _runner Contient l'index du ghosts qui chasse le pacmane.
     */
    unsigned int _runner;

    /**
     * @brief _selected Un booléen permettant de savoir si le _runner a été selectionner.
     */
    bool _selected;
};

#endif // BOARD_H
