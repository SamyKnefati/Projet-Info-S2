#include "arete.h"

#include <iostream>
#include "arete.h"

Aretes::Aretes(int D, int A, int poids) : m_D{D}, m_A{A}, m_poids{poids}, m_utilise{false} {}

void Aretes::afficherA() const {
    std::cout << "Arrete : " << m_D << "===>" << m_A << "        poids : " << m_poids;
}


int Aretes::Getpoids() const {

    return m_poids;

}

int Aretes::Getm_D() const {
    return m_D;
}

int Aretes::Getm_A() const {
    return m_A;
}