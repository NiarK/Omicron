#include <iostream>

#include "view/mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    
    // --- test area --- //

    // --- --- --- --- //


    return a.exec();
}


//TODO: initialiser matrice ? v
// detructeur, appelé le parent ? je pense que oui
// exception quand il n'y a pas de mouvement (attention le pacman peut ne pas bouger)
// maj des option en fct de la fenetre
// maj de la fenetre en fct des options
// revoir algo du pacman sur le tesseract
// mettre getEdges dans hypercube ?

// rapport :
// - limite -> la map aurait put savoir si un ghost se trouvait sur une case, au lieu d'itéré sur chacun pour savoir ou ils sont.
