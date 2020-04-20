#ifndef PROJET_INFO_S2_GRAPHE_H
#define PROJET_INFO_S2_GRAPHE_H
#include <iostream>
#include <fstream>
#include <queue>
#include "Sommet.h"
#include "Arete.h"
#include <vector>
#include "algorithm"

class Graphe {
private:
    std::vector<Sommet*> m_sommets;
    std::vector<Arete*> m_aretes;
public:
    Graphe(const std:: string cheminFichierGraphe);
    ~Graphe();
    void afficher() const;
    void triPoidsAretes();
    void algoKruskal();
};

#endif //TP5_GRAPHE_H
