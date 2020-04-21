//
// Created by sam-d on 14/04/2020.
//

#include "Graphe.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <windows.h>

void afficherParcours(size_t s0, const std::vector<int>& predecesseur){
    for (size_t i=0; i < predecesseur.size(); i++ ){
        if(i != s0){
            if(predecesseur[i] != -1){ //-1 pas accessible depuis s0
                std::cout << i << " <---- ";
                size_t j = predecesseur[i];
                while(j != s0){
                    std::cout << j << " <---- ";
                    j = predecesseur[j];
                }
                std::cout << j << std::endl;
            }
        }
    }
}


int main ()
{
    al_init();
    al_init_image_addon();
    al_install_mouse();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_primitives_addon();
    ALLEGRO_FONT *font;

    size_t s0 = 0;
    Graphe g{"../Graphe_NO"};
    std::vector<int> arborescence;
    g.afficher();

    std::vector<const Aretes*> kruskal;
    kruskal = g.kruskal();


    ///BFS DFS
    int chaine = 0;
    std::cout << "BFS: Veuillez saisir le numero du sommet initial pour la recherche du plus court chemin : ";
    std::cin >> s0;
    arborescence = g.BFS(s0);
    std::cout << "Plus courts chemin depuis le sommet " << s0 << "(BFS) : " << std::endl;
    afficherParcours(s0, arborescence);
    ///parcours DFS
    std::cout << "DFS: Veuillez saisir le numero du sommet initial : ";
    std::cin >> s0;
    g.DFS(s0, chaine);
    g.Allegro(font, kruskal);
    return 0;
}