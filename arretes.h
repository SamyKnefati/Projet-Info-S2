#ifndef PROJET_INFO_S2_ARRETES_H
#define PROJET_INFO_S2_ARRETES_H


#include <iostream>
#include "Sommets.h"

class Arretes {

private:
    int m_poids;
    int m_D;
    int m_A;
    bool m_utilise;

public:

    Arretes (int D,int A ,int poids);
    void afficherA() const;
    int Getpoids() const;
    int Getm_D() const;
    int Getm_A() const;
};


#endif
