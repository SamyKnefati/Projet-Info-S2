#ifndef PROJET_INFO_S2_GRAPHE_H
#define PROJET_INFO_S2_GRAPHE_H

#include <iostream>
#include "Sommets.h"
#include "arete.h"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

class Graphe {

private:
    bool m_estOriente;
    int m_capaciteChemin;
    std::vector< Sommet*> m_sommets;
    std::vector< Aretes*> m_arete;
public:
    Graphe(std:: string cheminFichierGraphe);
    ~Graphe();
    void afficher() const;
    void kruskal() ;
    void tri();
    std::vector<int> BFS(int numero_S0) const;
    void Allegro(ALLEGRO_FONT *font);
};

#endif
