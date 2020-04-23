#include "Sommets.h"



Sommet::Sommet(int num) : m_numero{num}, m_utilise{0}, m_marque{0} {}

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

    std::cout << "Sommets:" << m_numero<<" : "<< m_nomLieu <<" : "<<"COORS : " << m_x<<"; " <<m_y<<";  "<< std::endl<<
    "----------------------------------------------------"<< std::endl;

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

void Sommet::addType(int type) {
    m_type = type;
}

int Sommet::GetType()
{
    return m_type;
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

void Sommet::addNbPersMcarre(int nbPersMcarre) {
    m_nbPersMcarre = nbPersMcarre;
}

void Sommet::addNbPersMcarreTot(int nbPersMcarreTot) {
 m_nbPersMcarreTot = nbPersMcarreTot;
}

void Sommet::changeNbPersMcarre(int quelNbPers, int nouvelleVal) {
    if(quelNbPers == 1){ ///personnes au metre carre presentes actuellement a changer
        if (nouvelleVal > m_nbPersMcarreTot){
            std::cout << "vous allez surcharger le lieux, veuillez recommencer avec une valeur inferieur au nombre de personnes total autorise ou vous pouvez modifier le cette valeur" << std::endl;
        }
        if(nouvelleVal <=  m_nbPersMcarreTot){
            m_nbPersMcarre = nouvelleVal;
            std::cout << "nombre de personnes par metre carre actuel de :" << m_nomLieu << "prend la nouvelle valeur : " << nouvelleVal << std::endl;
        }
    }

    if(quelNbPers == 2){ /// personnes au metre carre maximum autorise a changer

        if(nouvelleVal < m_nbPersMcarre){
            std::cout << "la nouvelle valeur autorise de personnes par metre carre est inferieur au nombre de personne par metre carre actuel, veuillez recommencer avec une valeur differente" << std::endl;
        }
        if(nouvelleVal >= m_nbPersMcarre) {
            m_nbPersMcarreTot = nouvelleVal;
            std::cout << "valeur autorise de personnes par metre carre de :" << m_nomLieu << "prend la nouvelle valeur : " << nouvelleVal << std::endl;
        }
    }
}
