#include <iostream>
#include <thread>
#include <atomic>
#include <ctime>
#include <mutex>


using namespace std;
int choix;

bool arretG = false;
clock_t t_init, t_final;
float duree;
// Implementation du backtracking

bool algo_backtracking_p(Plateau p, coordonne position)
{
    // cout<< "Start of backtracking " << endl;

    if(p.condition_arret() == false)
    {

        cout << "--- Fin, Affichage de la solution --- " << endl;
        p.affichage_plateau();

        arretG = true;
        return true;
    }
    if (arretG == true) {
        t_final = clock();
        duree = (t_final - t_init) * 1e-6;

        cout << " duree d'execution du PUZZLE de taille : " << choix << "*" << choix << ": "<< duree << endl;
        exit(0);
        }

    for (int i = 0; i < p.cases.size(); i++)
    {

        // on verifie si la piece n'est pas deja utilise

        if(!p.cases[i].estUtilise)
        {
            // si ce n'est pas utilise on verifie si on peut la placer a cette position du plateau

            if(p.peutOnPlacerLaPiece(p.cases[i], position))
            {
                // si c'est le cas on la place et on la marque comme prise.
                p.plateau[position.x][position.y] = p.cases[i];

                // on la marque comme utilisee
                p.cases[i].estUtilise = true;

                if(algo_backtracking_p(p, p.positionSuivante()))
                {
                    return true;
                }

                // on la remet comme non utilisee pour remetre les pieces dans l'etat originale
                p.cases[i].estUtilise = false;
            }
        }
    }

    return false;
}

bool parallal_backtracking(Plateau p, coordonne position)
{
    // cout<< "Start of backtracking " << endl;


    for (int t = 0 ; t < p.cases.size(); t ++ )
    {

        auto action = [&] ()
        {

            // on fait une copie du vecteur de piece et ensuite un random
            vector<PIECE> piece = p.cases;
            
            piece[t].estUtilise = true;

            // on fait une copie du plateau qui sera a remplir par le thread pour ne pas traiter a chaque fois le meme plateau
            Plateau newP = p;

            // on effectue la premier pose de chaque piece du jeu dans un plateau et on le parallelise
            newP.plateau[0][0] = piece[t];

            algo_backtracking_p(newP, position);

        };

        thread th(action);
        th.join();
    }

    return true;
}


void tetra_parallal() {
    int n;
    Plateau p = Plateau("5*5.txt");
    cout << " **** Bienvenue, TETRAVEX BACKTRACKING PARALELLE**** " << endl << endl;

    cout << " Taille du plateau de jeu que vous souhaitez resoudre, entrez 5: (5*5), 6: (6*6), 7: (7*7), 8: (8*8) " << endl;
    cin>> choix;

        switch(choix){
            case 5:
                p = Plateau("5*5.txt");
                break;
            case 6:
                p = Plateau("6*6.txt");
                break;
            case 7:
                p = Plateau("7*7.txt");
                break;
            case 8:
                p = Plateau("8*8.txt");
                break;
        }

        cout << " -- Differentes pieces du Jeu --" << endl;
        p.affichage_des_cases();

        cout << " --* Initialisation du Plateau de Jeu *-- TAILLE : " << choix << "*" << choix << endl;
        p.initialisation_plateau();

        // nous commencons le parcours de la grille en haut en gauche (0,0)

        cout << " Algo backtracking en cours... " << endl;


        coordonne pos;
        pos.x = 0;
        pos.y = 1;
        //backtracking(p, pos);

        t_init = clock();

        parallal_backtracking(p,pos);




}
