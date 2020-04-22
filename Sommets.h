#ifndef PROJET_INFO_S2_SOMMETS_H
#define PROJET_INFO_S2_SOMMETS_H

#include <iostream>
#include <vector>
#include "arete.h"

class Sommet {
public:
    int m_numero;
    int m_x;
    int m_y;
    int m_utilise;
    std::vector<const Sommet*> m_successeurs;
    std::string m_nomLieu;
    int m_marque;

public:
    Sommet(int num);
    int getNumero() const;
    void addSuccesseur(const Sommet* succ);
    const std::vector<const Sommet*>& getSuccesseur() const ;
    void afficher() const;
    void Setutiliser();
    int Getutiliser();
    void RemiseZero();
    void addName(std::string nomLieu);
    void addCoor(int x, int y);
    int GetY();
    int GetX();
    std::string GetName();
    void marque(int n);

};

#endif
