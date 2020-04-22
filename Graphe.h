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
    int m_capaciteChemin=0;
    int m_DistanceCable=0;
    std::vector< Sommet*> m_sommets;
    std::vector< Aretes*> m_arete;
    std::vector< const Aretes*>  m_KruskalCpacite;
    std::vector< const Aretes*>  m_KruskalDistance;
    std::vector<int> m_Dijkstra;

public:
    Graphe(std:: string cheminFichierGraphe);
    ~Graphe();
    void afficher() const;
    std::vector<int> BFS(int numero_S0) const;
    void DFS(int numero_S0, int &chaine) const;
    bool getOriente() const;
    void kruskalCapacite() ;
    void kruskalCommunication() ;
    std::vector<int> dijkstra(int s0);
    void Allegro(int a);
    int getMarque(int num) const;
    void testGeneral() const;
};

#endif
