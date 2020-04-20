#include "arretes.h"

#include <iostream>
#include "arretes.h"

Arretes::Arretes(int D, int A, int poids) : m_D{D}, m_A{A}, m_poids{poids}, m_utilise{false} {}

void Arretes::afficherA() const {
    std::cout << "Arrete : " << m_D << "===>" << m_A << "        poids : " << m_poids;
}


int Arretes::Getpoids() const {

    return m_poids;

}

int Arretes::Getm_D() const {
    return m_D;
}

int Arretes::Getm_A() const {
    return m_A;
}