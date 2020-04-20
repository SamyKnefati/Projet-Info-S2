#include "Sommets.h"



Sommet::Sommet(int num) : m_numero{num}, m_utilise{false}{}

void Sommet::addSuccesseur(const Sommet *succ) {
    m_successeurs.push_back(succ);
}
int Sommet::getNumero() const {
    return m_numero;
}

void Sommet::afficher() const {

    std::cout << "Sommets:" << m_numero<<"; ";

}

const std::vector<const Sommet *> &Sommet::getSuccesseur() const {
    return m_successeurs;
}

void Sommet::Setutiliser()
{
    m_utilise+=1;
}

int Sommet::Getutiliser()
{

    return m_utilise;

}