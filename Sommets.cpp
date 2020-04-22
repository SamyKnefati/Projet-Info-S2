#include "Sommets.h"



Sommet::Sommet(int num) : m_numero{num}, m_utilise{false}, m_marque{0}{}

void Sommet::addSuccesseur(const Sommet *succ) {
    m_successeurs.push_back(succ);
}
int Sommet::getNumero() const {
    return m_numero;
}

std::string Sommet::GetName() {
    return m_nomLieu;
}


void Sommet::afficher() const {

    std::cout << "Sommets:" << m_numero<<" : "<< m_nomLieu <<" : "<<"COORS" << m_x<<";"<<m_y<<";  ";

}

const std::vector<const Sommet *> &Sommet::getSuccesseur() const {
    return m_successeurs;
}

void Sommet::Setutiliser()
{
    m_utilise+=1;
}

void Sommet::RemiseZero()
{
    m_utilise=0;
}

int Sommet::Getutiliser()
{

    return m_utilise;

}

void Sommet::addName(std::string nomLieu) {
m_nomLieu = nomLieu;
}



void Sommet::addCoor(int x, int y) {
   m_x = x;
   m_y = y;
}

int Sommet::GetX()
{

    return m_x;

}

int Sommet::GetY()
{

    return m_y;

}

void Sommet::marque(int n) {
    m_marque += n;
}

const std::vector<std::pair<Sommet *const, int>> &Sommet::getSuccesseurs() const {
    return m_successeurS;
}

int Sommet::getId() const {
    return m_numero;
}

void Sommet::addSuccesseuS(Sommet *successeur, int poids) {
    m_successeurS.emplace_back(successeur, poids);
}
