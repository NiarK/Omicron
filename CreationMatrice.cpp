#include <iostream>

#define TAILLE 3

int main( int argc, const char* argv[] ){
    int i,j;
    int taille = TAILLE;
    int taillecarre = taille*taille;
    int mat[TAILLE*TAILLE][TAILLE*TAILLE] = {0};
    int mat1[TAILLE*TAILLE][TAILLE*TAILLE] = {0};
    //Creation de la matrice d'adjacence pour 8X8 avec bords
    for(i=0;i<(taillecarre);i++){
        if((i%taille)!=0){
            mat[i][i-1]=1;
        }
        if((i%taille)!=(taille-1)){
            mat[i][i+1]=1;
        }
        if(i>(taille-1)){
            mat[i][i-taille]=1;
        }
        if(i<(taillecarre - taille)){
            mat[i][i+taille]=1;
        }
    }
    //affichage de la matrice
    for(i=0;i<(taillecarre);i++){
        for(j=0;j<(taillecarre);j++){
            std::cout << " " << mat[i][j];
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;
    std::cout << std::endl;

    //Creation de la matrice d'adjacence pour 8X8 sans bords
    for(i=0;i<(taillecarre);i++){
        if((i%taille)!=0){
            mat1[i][i-1]=1;
        }
        else
            mat1[i][i-1+taille]=1;
        if((i%taille)!=(taille-1)){
            mat1[i][i+1]=1;
        }
        else
            mat1[i][i+1-taille]=1;
        if(i>(taille-1)){
            mat1[i][i-taille]=1;
        }
        else
            mat1[i][i-taille+taillecarre]=1;
        if(i<(taillecarre - taille)){
            mat1[i][i+taille]=1;
        }
        else
            mat1[i][i+taille-taillecarre]=1;
    }
    //affichage de la matrice
    for(i=0;i<(taillecarre);i++){
        for(j=0;j<(taillecarre);j++){
            std::cout << " " << mat1[i][j];
        }
        std::cout << std::endl;
    }

        std::cout << std::endl;
        std::cout << std::endl;
    int t=4;
    int mat2[8][8] = {0};
    for(i=0;i<(2*t);i++){
        if(i%t!=0)
            mat2[i][i-1]=1;
        else
            mat2[i][i+t-1]=1;
        if(i%t!=t-1)
            mat2[i][i+1]=1;
        else
            mat2[i][i-t+1]=1;
        if(i>(t-1)){
            mat2[i][i-t]=1;
        }
        if(i<t){
            mat2[i][i+t]=1;
        }
    }
    //affichage de la matrice
    for(i=0;i<(2*t);i++){
        for(j=0;j<(2*t);j++){
            std::cout << " " << mat2[i][j];
        }
        std::cout << std::endl;
    }
}
