#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <sstream>
#include <cstring>

#include "helpers.cpp"
#include "piece.cpp"
#include "coordinate.cpp"

using namespace std;

class Plateau
{

private:
    string fichier;
    int dim;
    int taille_grille;


public:
    vector<vector<piece>> plateau;
    vector<vector<piece>> plateauCopie;
    vector<piece> cases;

    Plateau();

    Plateau(string f)
    {
        this->fichier = f;
        piece carre;
        ifstream fichier(f, ios::in);
        string ligne;
        getline(fichier, ligne);
        char *n = strdup(ligne.c_str());
        this->taille_grille = atoi(n);
        this->dim = taille_grille * taille_grille;

        cout << " dimension : " << taille_grille << endl;
        for (int i = 1; i <= dim; i++)
        {

            getline(fichier, ligne);
            vector<int> val = tokenization(ligne);
            carre.gauche = val[0];
            carre.haut = val[1];
            carre.droite=val[2];
            carre.bas = val[3];
            this->cases.push_back(carre);

        }
        fichier.close();
    };

    // initialisation du plateau de jeu

    void initialisation_plateau()
    {
        piece carre;
        for (int i = 0; i < taille_grille; i++ )
        {
            vector<piece> ligne;

            for (int j = 0;  j < taille_grille; j++)
            {
                ligne.push_back(carre);
            }
            this->plateau.push_back(ligne);
        }
    };
    // end


    // condition d'arret du backtracking recursif, lorsque toute les pieces sont utilisees
    bool condition_arret()
    {
        for (int i = 0; i < this->cases.size(); i++)
        {
            piece val = cases[i];
            if (!val.estUtilise)
            {
                return true;
            }
        }
        return false;
    };

    bool arret() {
        return this->cases.empty();
    }
    // end

    // fonction pour verifier si on peut placer une piece a une position de la grille

    bool peutOnPlacerLaPiece(piece carre, coordonne co)
    {

        //si nous ne somme pas sur la premiere ligne du plateau
        if (co.x != 0)
        {

            if(this->plateau[co.x-1][co.y].bas != carre.haut)
            {
                return false;
            }
       }
       //si nous ne somme as sur la 1ere olonne du plateau
        if (co.y != 0)
        {
            if(this->plateau[co.x][co.y - 1].droite != carre.gauche)
            {
                return false;
            }
        }
        return true;

    };
    // end

    // fonction verifiant si une case de la grille est vide

    bool uneCaseDeLaGrilleEstVide(piece carre)
    {
        if(carre.gauche == -1 && carre.haut == -1 && carre.droite == -1 && carre.bas == -1)
        {
            return true;
        }
        else
        {
            return false;
        }    };

    // end

    // Apres avoir placer une piece, on doit mettre une autre piece a la prochaine case vide de la grille qu'on trouve
    coordonne positionSuivante()
    {

        coordonne pos;
        pos.x = 0;
        pos.y = 0;
        for (int i =0; i < this->plateau.size(); i++)
        {
            for (int j =0; j< this->plateau[i].size(); j++)
            {
                if(this->uneCaseDeLaGrilleEstVide(this->plateau[i][j]) )
                {
                    pos.x = i;
                    pos.y = j;
                    return pos;
                }
            }
        }
        return pos;

    };

    // end

    // Affichage des pieces/cases a placer dans la grille

    void affichage_des_cases()
    {
        for (int i = 0; i< this->dim; i++)
        {
            cout << this->cases[i].gauche << " " << this->cases[i].haut << " " << this->cases[i].droite << " " << this->cases[i].bas << endl;
        }
    };
    // end

    // Affichage du plateau de jeu

    void affichage_plateau()
    {
        if(this->plateau.size() > 0)
        {

            for (int i = 0; i < this->plateau.size(); i++ )
            {
                vector<piece> ligne = this->plateau[i];


                for (int j = 0; j < ligne.size(); j++)
                {
                    piece val = ligne[j];
                   cout << "   " << val.haut << "   ";

                }
                cout << endl;
                for (int j = 0; j < ligne.size(); j++)
                {
                    piece val = ligne[j];
                   cout << " " << val.gauche << "   " << val.droite << " ";

                }
                cout << endl;
                for (int j = 0; j < ligne.size(); j++)
                {
                    piece val = ligne[j];
                   cout << "   " << val.bas << "   ";

                }
                cout << endl;
                cout << endl;



            }


        }
        else
        {
            cout << " Plateau vide " << endl;
        }
    };

    void copyDuPlateau() {

        for(int i = 0; i < this->plateau.size(); i++) {

            for (int j = 0; j <  this->plateau[i].size(); j++) {
                this->plateauCopie[i][j] = this->plateau[i][j];
            }
        }
    }

    // end
};

