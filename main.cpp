#include <iostream>

#include <ctime>
#include "plateau.cpp"
#include "Tetra_Sequential.cpp"
#include "Tetra_parallal.cpp"
#include "threadPoolTetra.cpp"



using namespace std;

int main()
{

    int choix = 0;
    cout << "----- JEU TETRAVEX --------" << endl << endl;

    cout << "Comment souhaitez vous resoudre le jeu ? 1: Sequentiellement, 2: Parallelement . 3: ThreadPool" << endl << endl;
    cin >> choix;
    if(choix == 1) {
        tetra_sequential();
    }else if(choix == 2){
        tetra_parallal();
    }else if(choix == 3){
        tetra_threadpool_parallal();
    }else{
         tetra_sequential();
    }

    return 0;
}
