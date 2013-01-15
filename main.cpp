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
