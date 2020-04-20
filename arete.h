#ifndef PROJET_INFO_S2_ARETE_H
#define PROJET_INFO_S2_ARETE_H


#include <iostream>
#include "Sommets.h"

class Aretes {

private:
    int m_poids;
    int m_D;
    int m_A;
    bool m_utilise;
    std::string m_nomArete;

public:

    Aretes (int D,int A ,int poids, std::string nomArete);
    void afficherA() const;
    int Getpoids() const;
    int Getm_D() const;
    int Getm_A() const;
};


#endif
