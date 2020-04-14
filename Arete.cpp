#include "Arete.h"

Arete::Arete(int poids, Sommet sommet1, Sommet sommet2)
 : m_poids(poids), m_sommet1(sommet1), m_sommet2(sommet2){}

int Arete::getPoids() const {
    return m_poids;
}

int Arete::getNumSommet1() const {
    return m_sommet1.getNumero();
}

int Arete::getNumSommet2() const {
    return m_sommet2.getNumero();
}

void Arete::afficher() const {
    std::cout << "     Arete    : " << getNumSommet1() + 1 << " <-> " << getNumSommet2() + 1 << "   poids : " << getPoids();
}