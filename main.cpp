//
// Created by sam-d on 14/04/2020.
//

#include <iostream>
#include "Graphe.h"
//#include <allegro5/allegro.h>
#include <windows.h>

int main ()
{
    std::cout << "test reussi"<<std::endl;
    size_t s0 = 0;
    Graphe g{"../Graphe_NO"};
    std::vector<int> arborescence;
    g.afficher();
    g.Tri();
   /* assert(al_init());


    ALLEGRO_DISPLAY*display= nullptr;

    display= al_create_display(450,450);
    bool quit= false;

    while(!quit)
    {
        Sleep(5);
        quit=true;


    }

    al_destroy_display(display);*/

    return 0;
}