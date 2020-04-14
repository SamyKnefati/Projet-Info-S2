#include "Sommet.h"

Sommet::Sommet(int num) : m_numero{num}{}

void Sommet::addSuccesseur(const Sommet *succ) {
    m_successeurs.push_back(succ);
}

int Sommet::getNumero() const {
    return m_numero;
}

void Sommet::afficher() const {
    std::cout << "     Sommet    " << m_numero + 1 << "   :   ";
    for(auto addrSommet: m_successeurs){
        std::cout << addrSommet->getNumero() + 1 << " ";
    }
}

const std::vector<const Sommet*> &Sommet::getSuccesseur() const {
    return m_successeurs;
}
