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
    ///partie allegro initialisation
    al_init();
    al_init_image_addon();
    al_install_mouse();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_primitives_addon();


    /// initialisation du graphe et des valeurs pour notre graphe
    size_t s0 = 0;
    size_t a= 0;
    Graphe g{"../Graphe_NO"};
    std::vector<int> arborescence;
    std::vector<const Aretes*> kruskal;

    /// affichage basique
    g.afficher();


    int fin = 0;
    int chaine = 0;
    int menu = 0;
    while(fin!=1){

        std::cout<< "veuillez choisir une option : " << std::endl;
        std::cout<< "1) parcours BFS  "<< std::endl<<
                    "2) parcours DFS" <<std::endl <<
                    "3) algorithme de kruskal" << std::endl <<
                    "4) afficher la carte" <<std::endl <<
                    "5) Dijsktra" <<std::endl <<
                    "6) info ford-fulkerson" <<std::endl<<
                    "7) effectuer des modifications" <<std::endl<<
                    "8) quitter le simulateur " << std::endl;
        std::cin>>menu;
        switch(menu){
            case 1:
                ///parcours BFS
                std::cout << "BFS: Veuillez saisir le numero du sommet initial pour la recherche du plus court chemin : " <<std::endl;
                std::cin >> s0;
                arborescence = g.BFS(s0);
                std::cout << "Plus court chemin depuis le sommet "<< s0<< std::endl;
                afficherParcours(s0, arborescence);
                break;
            case 2:
                ///parcours DFS
                std::cout << "DFS: Veuillez saisir le numero du sommet initial : ";
                std::cin >> s0;
                g.DFS(s0, chaine);
                break;
            case 3:
                g.kruskalCapacite();
                g.kruskalCommunication();
                break;
            case 4:
                a=s0;
                g.Allegro(a);
                break;
            case 5:
                std::cout << "Dijstkra: Veuillez saisir le numero du sommet initial : ";
                std::cin >> s0;
                arborescence=g.dijkstra(s0);
                afficherParcours(s0,arborescence);
                break;
            case 6:
                g.ford_fulkerson();
                break;
            case 7:
                int changement;
                std::cout << "quels changements voulez vous effectuer : " << std::endl;
                std::cout << "1) changer un flot "<<std::endl<<
                             "2) changer le nombre de personnes sur un lieu"<<std::endl<<
                             "3) bloquer une rue" << std::endl;
                std::cin >> changement;

                switch (changement){
                    case 1:
                        g.changerFlotArr();
                        break;
                    case 2:
                        g.changerNbPersMcarreSommet();
                        break;
                    case 3:
                        g.bloquerArr();

                        break;
                    default:
                        break;
                }

                break;
            case 8:
                fin = 1;
                break;
            default:
                break;
        }
    }

    return 0;
}