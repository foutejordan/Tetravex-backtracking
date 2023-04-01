#include <iostream>
#include <ctime>


using namespace std;

bool backtracking(Plateau p, coordonne position)
{
    // cout<< "Start of backtracking " << endl;

    if(p.condition_arret() == false)
    {

        cout << "--- Fin, Affichage de la solution --- " << endl;
        p.affichage_plateau();
        return true;
    }

    for (int i =0; i < p.cases.size(); i++)
    {

        // on verifie si la piece n'est pas deja utilise

        if(!p.cases[i].estUtilise)
        {
            // si ce n'est pas utilise on verifie si on peut la placer a cette position de la grille

            if(p.peutOnPlacerLaPiece(p.cases[i], position))
            {
                // si c'est le cas on la place et on la marque comme prise et on continue.
                p.plateau[position.x][position.y] = p.cases[i];

                p.cases[i].estUtilise = true;

                if(backtracking(p, p.positionSuivante()))
                {
                    return true;
                }
                // on la retire comme utilise car situation bloquante, on fait un retour sur trace en commencant par la pose de cette piece
                p.cases[i].estUtilise = false;
            }
        }
    }

    return false;
}

void tetra_sequential() {
    int n;
    cout << " **** Bienvenue, TETRAVEX BACKTRACKING **** " << endl << endl;

    cout << " L'algorithme executera chaque taille de PUZZLE sequentiellement." << endl;

    vector<string> tab = {"5*5.txt", "6*6.txt", "7*7.txt", "8*8.txt"};

    for (int i = 0; i < tab.size() ; i++)
    {
        Plateau p = Plateau(tab[i]);
        cout << " -- Differentes pieces du Jeu --" << endl;
        p.affichage_des_cases();

        cout << " --* Initialisation du Plateau de Jeu *-- TAILLE : " << tab[i] << endl;
        p.initialisation_plateau();

        // nous commencons le parcours de la grille en haut en gauche (0,0)

        cout << " Algo backtracking en cours... " << endl;


        coordonne pos;
        pos.x = 0;
        pos.y = 0;
        clock_t t_init, t_final;
        float duree;
        t_init = clock();

        backtracking(p,pos);

        t_final = clock();
        duree = (t_final - t_init) * 1e-6;

       cout << " duree d'execution du PUZZLE de taille : " << tab[i] << ": "<< duree << endl;
    }
}
