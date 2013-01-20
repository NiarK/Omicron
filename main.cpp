#include <iostream>

#include "view/mainwindow.h"
#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //QTextCodec::setCodecForTr(QTextCodec::codecForName("latin1"));

    MainWindow w;
    w.show();
    
    // --- test area --- //

    // --- --- --- --- //


    return a.exec();
}


//TODO: initialiser matrice ? v
// detructeur, appelé le parent ? je pense que oui
// exception quand il n'y a pas de mouvement (attention le pacman peut ne pas bouger)
// augmenter taille des cercles
// revoir algo du pacman sur le tesseract
// mettre getEdges dans hypercube ?

// rapport :
// - limite -> la map aurait put savoir si un ghost se trouvait sur une case, au lieu d'itéré sur chacun pour savoir ou ils sont.
