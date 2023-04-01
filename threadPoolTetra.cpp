#include <iostream>
#include <math.h>
#include <vector>
#include <mutex>
#include <thread>
#include <condition_variable>

#include <queue>
#include <atomic>
#include <functional>
#include <algorithm>
#include <random>


using namespace std;

int k= 5;
vector<thread> th;
queue<function<void()>> tasks;


mutex m_thread;
mutex m;

void action ()
{
    // boucle attendant que la file d'attente des tâches s'ouvre.

    while(tasks.size() > 0)
    {
        function<void()> task = NULL;
        m_thread.lock();
        if (!tasks.empty())
        {
            task = tasks.front();

            tasks.pop(); // retrait de la tache dans la file d'attente
        }
        m_thread.unlock();
        if (task) {
            try{
                task();

            }catch (exception& e) {
                cout << "error"<< e.what() << endl;
                return;
            }
        }   // pour conserver le parallelisme, on execute la tache en dehors du mutex (si elle exite)

    }
}

void create_pool_thread ()
{
    for (int i = 0; i < k; i++)
    {
        th.push_back(thread(action));

    }
}


void add_task (Plateau p, coordonne position)
{

    for (int t = 0 ; t < p.cases.size(); t ++ )
    {

        auto val = [p, position, t] ()
        {

        // on fait une copie du vecteur de piece
            vector<PIECE> piece = p.cases;

            piece[t].estUtilise = true;

            //Shuffle sur les pieces
			auto rng = std::default_random_engine {};
            random_shuffle(piece.begin(), piece.end());
            //on fait une copie du plateau qui sera a remplir par le thread pour ne pas traiter a chaque fois le meme plateau

            Plateau newP = p;

            //on effextue la premier pose de chaque piece du jeu dans un plateau a la position (0,0) et on le parallelise
            newP.plateau[0][0] = piece[t];

            algo_backtracking_p(newP, position);

        };

        tasks.push(val); // ajout de la tache dans la file d'attente
    }
}

void tetra_threadpool_parallal() {
    int n;
    Plateau p = Plateau("5*5.txt");
    cout << " **** Bienvenue, TETRAVEX BACKTRACKING THREADPOOL PARALELLE**** " << endl << endl;

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


        cout << " Algo backtracking en cours... " << endl;


        coordonne pos;
        pos.x = 0;
        pos.y = 1;
        //backtracking(p, pos);

        t_init = clock();

        add_task(p, pos);

        create_pool_thread();

        for (int i = 0; i < k ; i++)
            {
                if(th[i].joinable()) {
                    th[i].join();
                }
            }
}
