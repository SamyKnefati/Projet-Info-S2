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
    int m_DistanceCable;
    std::vector< Sommet*> m_sommets;
    std::vector< Aretes*> m_arete;
    std::vector< const Aretes*>  m_kruskal;

public:
    Graphe(std:: string cheminFichierGraphe);
    ~Graphe();
    void afficher() const;
    std::vector<int> BFS(int numero_S0) const;
    void DFS(int numero_S0, int &chaine) const;
    bool getOriente() const;
    void kruskal() ;
    void tri();
    void Allegro(std::vector< const Aretes*>&  kruskal );
    //void ford_fulkerson(int depart, int arrivee);
    int getMarque(int num) const;
};

#endif
