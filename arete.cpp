#include "arete.h"

#include <iostream>
#include "arete.h"

Aretes::Aretes(int D, int A, int poids,std::string nomArete, int type) : m_D{D}, m_A{A}, m_capacite{poids}, m_utilise{false}, m_nomArete{nomArete},
m_type{type} {}

void Aretes::afficherA() const {
    std::cout << m_nomArete << " : " << m_D << "===>" << m_A << "        capacite : " << m_capacite<< "    type:"<<m_type;
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

std::string const Aretes::GetName() {

    return m_nomArete;


}

int Aretes::GetmType() const {
    return m_type;
}