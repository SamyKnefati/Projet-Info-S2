#ifndef PROJET_INFO_S2_SOMMETS_H
#define PROJET_INFO_S2_SOMMETS_H

#include <iostream>
#include <vector>

class Sommet {
private:
    int m_numero;
    int m_x;
    int m_y;
    int m_utilise;
    std::vector<const Sommet*> m_successeurs;
    std::string m_nomLieu;
    std::vector<std::pair<Sommet *const, int>> m_successeurS;

    int m_nbPersMcarre;
    int m_nbPersMcarreTot;
    int m_type;

public:
    int m_marque;
    Sommet(int num);
    int getNumero() const;
    void addSuccesseur(const Sommet* succ);
    void addSuccesseuS(Sommet *successeur, int poids);
    const std::vector<const Sommet*>& getSuccesseur() const ;
    void afficher() const;
    void Setutiliser();
    int Getutiliser();
    void RemiseZero();
    const std::vector<std::pair<Sommet *const, int>> &getSuccesseurs() const;
    void addName(std::string nomLieu);
    void addCoor(int x, int y);
    int GetY();
    int GetX();
    int getId() const;
    std::string GetName();
    void marque(int n);
    void addNbPersMcarre(int nbPersMcarre);
    void addNbPersMcarreTot(int nbPersMcarreTot);
    void changeNbPersMcarre(int quelNbPers, int nouvelleVal);
    void addType(int type);
    int GetType();
};

#endif
