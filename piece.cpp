#include <iostream>
#include <fstream>

// Structure de donne correspondant a une piece du jeu
struct PIECE
{
    int gauche = -1;
    int haut = -1;
    int droite = -1;
    int bas = -1;
    bool estUtilise = false;
};
typedef struct PIECE piece;

//end
