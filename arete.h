#ifndef PROJET_INFO_S2_ARETE_H
#define PROJET_INFO_S2_ARETE_H


#include <iostream>
#include "Sommets.h"

class Aretes {

private:
    int m_capacite;
    int m_D;
    int m_A;
    int m_distance;
    bool m_utilise;
    int m_type;
    std::string m_nomArete;
    int m_flotTot;
    int m_flot;

public:

    Aretes (int D,int A ,int poids, std::string nomArete, int type, int distance, int flotTot, int flot);
    void afficherA() const;
    int GetCapacite() const;
    int Getm_D() const;
    int Getm_A() const;
    int GetmType() const;
    int Getdistance() const;
    std::string const GetName();
};


#endif
