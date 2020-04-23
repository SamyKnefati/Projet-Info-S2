#include "arete.h"

#include <iostream>
#include "arete.h"

Aretes::Aretes(int D, int A, int poids,std::string nomArete, int type, int distance, int flotTot, int flot) : m_D{D}, m_A{A}, m_capacite{poids}, m_utilise{false}, m_nomArete{nomArete},
m_type{type}, m_distance{distance},m_flotTot{flotTot},m_flot{flot} {}

void Aretes::afficherA() const {
std::string type_rue;
        if (m_type == 2){
            type_rue += " autre";
        }
        else if (m_type == 1 ){
            type_rue += " rue";
        }

    std::cout << m_nomArete << " : " << m_D << " ===> " << m_A << "" <<std::endl<<
    "    capacite : " << m_capacite <<" personnes "<<std::endl<<
    "    type:" << type_rue <<std::endl<<
    "    distance :"<<m_distance<< "m";
}


int Aretes::GetCapacite() const {

    return m_capacite;

}

int Aretes::Getm_D() const {
    return m_D;
}

int Aretes::Getm_A() const {
    return m_A;
}

std::string Aretes::GetName() const {

    return m_nomArete;


}

int Aretes::GetmType() const {
    return m_type;
}

int Aretes::Getdistance() const {

    return m_distance;

}

int Aretes::getFlotMax() const {
    return m_flotTot;
}

int Aretes::getFlot() const {
    return m_flot;
}

void Aretes::changeFlot(int quelFlot, int nouvelleVal) {
    if(quelFlot == 1){
        if (nouvelleVal > m_flotTot){
            std::cout << "vous allez surcharger l'arete veuillez recommencer avec une valeur inferieur au flot total ou vous pouvez modifier le flot total" << std::endl;
        }
        if(nouvelleVal <=  m_flotTot){
            m_flot = nouvelleVal;
            std::cout << "flot de :" << m_nomArete << "prend la nouvelle valeur : " << nouvelleVal << std::endl;
        }
    }

    if(quelFlot == 2){

        if(nouvelleVal < m_flot){
            std::cout << "la nouvelle valeur de flot total est inférieur au flot actuel, veuillez recommencer avec une valeur differente" << std::endl;
        }
        if(nouvelleVal >= m_flot) {
            m_flotTot = nouvelleVal;
            std::cout << "flot total de :" << m_nomArete << "prend la nouvelle valeur : " << nouvelleVal << std::endl;
        }
    }
}


